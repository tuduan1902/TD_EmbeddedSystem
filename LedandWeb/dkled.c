#include <wiringPi.h>
#include <mysql.h>

void xuly_ngat(void){
    // cap nhat xung PWM

    // update database


}

int main(void)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *server = "localhost";
    char *user = "admin";
    char *password = "123456"; /* set me first */
    char *database = "ledControl";
    // setup thu vien wiringPi
    wiringPiSetup();

    // Khai bao IO, interrupt, softPWM

    while(1){
        // ket noi database
        conn = mysql_init(NULL);
        mysql_real_connect(conn,server,user,password,database,0,NULL,0); 
        // kiem tra cot isUpdated
        char sql[200];
        sprintf(sql, "select * from rgbValues");
        mysql_query(conn,sql);
        res = mysql_store_result(conn); 
        row = mysql_fetch_row(res); //row[0]-> red; row[1]->green
        // NOTES: row la bien dang chuoi ky tu
        if( atoi(row[4])==1){
            ...

        }

    }


    return 0;
}