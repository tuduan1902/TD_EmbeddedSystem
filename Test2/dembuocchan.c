#include "I2Cdev.h"
#include "MPU6050.h"
#include <LiquidCrystal_I2C.h>

// Rxx is the output value from registers, ex: RGX, RAY
// (AX, AY, AZ) = (RAX, RAY, RAZ) / 16384
// (GX, GY, GZ) = (RGX, RGY, RGZ) / 131.0

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

LiquidCrystal_I2C lcd(0x27, 16, 2);

MPU6050 accelgyro;
int16_t ax, ay, az;

float threshhold = 0.15;
float xval[100] = {0};
float yval[100] = {0};
float zval[100] = {0};
float xavg;
float yavg;
float zavg;

int steps, flag = 0;
void setup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
   Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
   Fastwire::setup(400, true);
#endif

   Serial.begin(9600);

   lcd.begin();
   lcd.backlight();
   accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
 calibrate();
}

void loop() {
 int acc = 0;
 float totvect[100] = {0};
 float totave[100] = {0};
 float xaccl[100] = {0};
 float yaccl[100] = {0};
 float zaccl[100] = {0};

 for (int i = 0; i < 100; i++) {
  xaccl[i] = float(accelgyro.getAccelerationX() / 16384.0);
  delay(1);

  yaccl[i] = float(accelgyro.getAccelerationY() / 16384.0);
  delay(1);

  zaccl[i] = float(accelgyro.getAccelerationZ() / 16384.0);
  delay(1);

  totvect[i] = sqrt(((xaccl[i] - xavg) * (xaccl[i] - xavg)) + ((yaccl[i] - yavg) * (yaccl[i] - yavg)) + ((zval[i] - zavg) * (zval[i] - zavg)));
  totave[i] = (totvect[i] + totvect[i - 1]) / 2 ;
   
  delay(200);

  if (totave[i] > threshhold && flag == 0) {
   steps = steps + 1;
   flag = 1;

  } else if (totave[i] > threshhold && flag == 1) {

  }

  if (totave[i] < threshhold  && flag == 1) {
   flag = 0;
  }
   
  Serial.print(steps);
    Serial.print("\0");
    lcd.setCursor(0,0);
    lcd.print("So Buoc:");
    lcd.setCursor(0,1);
    lcd.print(steps);
 }

 delay(200);

}


void calibrate() {
 float sum = 0;
 float sum1 = 0;
 float sum2 = 0;
 for (int i = 0; i < 100; i++) {
  xval[i] = float(accelgyro.getAccelerationX() / 16384.0);
  sum = xval[i] + sum;
 }
 delay(100);
 xavg = sum / 100.0;

 for (int j = 0; j < 100; j++) {
  xval[j] = float(accelgyro.getAccelerationY() / 16384.0);

  sum1 = xval[j] + sum1;
 }
 yavg = sum1 / 100.0;
 delay(100);

 for (int i = 0; i < 100; i++) {
  zval[i] = float(accelgyro.getAccelerationZ() / 16384.0);

  sum2 = zval[i] + sum2;
 }
 zavg = sum2 / 100.0;
 delay(100);
}