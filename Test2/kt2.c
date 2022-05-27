#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h> //-lwiringPi -lm
#include <stdint.h>
#include <stdio.h>
#include <mysql.h>

// config resigter address
#define sample_rate 25 
#define config 26
#define gryo_config 27
#define acc_config 28
#define interrupt 56
#define pwr_managment 107
// read value meaure on reg
#define Acc_x 59
#define Acc_y 61
#define Acc_z 63

int mpu;
uint16_t high, low, data = 0x0000;

void Init_6050(void){
    // Reg 25->28 , 56, 107
    wiringPiI2CWriteReg8(mpu, sample_rate,0x28); //200Hz
    wiringPiI2CWriteReg8(mpu, config,0x03); // <=44kHz DLPF
    wiringPiI2CWriteReg8(mpu, gryo_config,0x08); // gyro FS: +-500 deg/s
    wiringPiI2CWriteReg8(mpu, acc_config,0x10); // acc FS: +-8g
    wiringPiI2CWriteReg8(mpu, interrupt,1); // mở interrupt của data ready
    wiringPiI2CWriteReg8(mpu, pwr_managment,0x01); // chọn nguồn xung Gyro X
}

uint16_t Read_MPU(unsigned char reg_address){
    high = wiringPiI2CReadReg8(mpu, reg_address);
    low = wiringPiI2CReadReg8(mpu, reg_address+1);
    data += (high<<8);
    if(data>0xffff) data= -(65535-data);
    return data;
}
int main(void){ 
	MYSQL *conn;

    char *server = "192.168.1.22";
    char *user = "admin";
    char *password = "123456"; /* set me first */
    char *database = "mpu6050";
    mpu = wiringPiI2CSetup(0x68);// setup I2C/

    Init_6050(); // Thiết lập chế độ đo

    while(1){
		// ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
        // Đo gia tốc theo trục x,y,z
        float Ax = (float)Read_MPU(Acc_x)/4069.0;
        float Ay = (float)Read_MPU(Acc_y)/4069.0;
        float Az = (float)Read_MPU(Acc_z)/4069.0;

        // tính Roll(góc quay quanh trục x) 
        float roll = atan2(Ax,sqrt(pow(Ay,2) + pow(Az,2)))*180/M_PI;

        // tính Pitch(góc quay quanh trục y)
        float pitch = atan2(Ay,sqrt(pow(Ax,2) + pow(Az,2)))*180/M_PI;

        // tính Yaw(góc quay quanh trục z)
        float yaw = atan2(Az,sqrt(pow(Ax,2) + pow(Ay,2)))*180/M_PI;
		
		// kiem tra cot isUpdated
        char sql[200];
        sprintf(sql, "update mpu_value set Ax = %0.3f, Ay = %0.3f, Az = %0.3f where id = 1;",roll, pitch, yaw);
		mysql_query(conn,sql);
		mysql_close(conn);
        printf("\n \tX= %0.3f g \tY= %0.3f g \tZ= %0.3f g \n", roll, pitch, yaw);
        data = 0;
		
        
		
        delay(1000);

    }
    return 0;
}