#include <wiringPi.h>
#include <wiringPiI2C.h>

#define who_am_i 117
#define temp_out_h 65
#define temp_out_l 66
#define sample_rate 25
#define config 26
#define gyro_config 27
#define accel_config 28
#define interrupt_en 56
#define power_management 107
#define Acc_X 59
#define Acc_Y 61
#define Acc_Z 63
#define Gyro_X 67
#define Gyro_Y 69
#define Gyro_Z 71

int mpu6050;

void init_mpu6050(int sr, int cf, int gyro_cf, int acc_cf, int pw_mgmt)
{
    wiringPiI2CWriteReg8(mpu6050, sample_rate,sr);
    wiringPiI2CWriteReg8(mpu6050, config, cf );
    wiringPiI2CWriteReg8(mpu6050, gyro_config, gyro_cf);
    wiringPiI2CWriteReg8(mpu6050, accel_config, acc_cf);
    wiringPiI2CWriteReg8(mpu6050, power_management, pw_mgmt);
}

int16_t read_value(unsigned char address)
{
    int16_t data;
    data = wiringPiI2CReadReg8(mpu6050,address)<<8 | wiringPiI2CReadReg8(mpu6050,address+1);
    return data;
}