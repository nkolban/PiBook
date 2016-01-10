#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define MPU6050_ADDRESS (0x68)
#define MPU6050_REG_PWR_MGMT_1 (0x6b)
#define MPU6050_REG_DATA_START (0x3b)
#define A_SCALE (16384.0)
#define ANG_SCALE (131.0)

void checkRC(int rc, char *text) {
  if (rc < 0) {
    printf("Error: %s - %d\n");
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  printf("MPU6050 starting\n");
  // Setup Wiring Pi
  wiringPiSetup();

  // Open an I2C connection
  int fd = wiringPiI2CSetup(MPU6050_ADDRESS);
  checkRC(fd, "wiringPiI2CSetup");

  // Perform I2C work
  wiringPiI2CWriteReg8(fd, MPU6050_REG_PWR_MGMT_1, 0);

  while(1) {
    uint8_t msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START);
    uint8_t lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+1);
    short accelX = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+2);
    lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+3);
    short accelY = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+4);
    lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+5);
    short accelZ = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+6);
    lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+7);
    short temp = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+8);
    lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+9);
    short gyroX = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+10);
    lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+11);
    short gyroY = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+12);
    lsb = wiringPiI2CReadReg8(fd, MPU6050_REG_DATA_START+13);
    short gyroZ = msb << 8 | lsb;

    printf("accelX=%f, accelY=%f, accelZ=%f, gyroX=%f, gyroY=%f, gyroZ=%f\n", accelX/A_SCALE, accelY/A_SCALE, accelZ/A_SCALE, gyroX/ANG_SCALE, gyroY/ANG_SCALE, gyroZ/ANG_SCALE);
    sleep(1);
  }
}
