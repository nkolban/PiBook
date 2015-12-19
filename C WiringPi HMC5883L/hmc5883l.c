#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "hmc5883l.h"

#define PI 3.14159265

void checkRC(int rc, char *text) {
  if (rc < 0) {
    printf("Error: %s - %d\n", text, rc);
    exit(-1);
  }
}

int main(int argc, char *argv[]) {
  printf("HMC5883L starting\n");
  // Setup Wiring Pi
  wiringPiSetup();

  // Open an I2C connection
  int fd = wiringPiI2CSetup(HMC5883L_ADDRESS);
  checkRC(fd, "wiringPiI2CSetup");

  // Perform I2C work
  wiringPiI2CWriteReg8(fd, HMC5883L_REG_MODE, HMC5883L_MODE_CONTINUOUS);

  while(1) {
  uint8_t msb = wiringPiI2CReadReg8(fd, HMC5883L_REG_MSB_X);
  uint8_t lsb = wiringPiI2CReadReg8(fd, HMC5883L_REG_LSB_X);
  short x = msb << 8 | lsb;

  msb = wiringPiI2CReadReg8(fd, HMC5883L_REG_MSB_Y);
  lsb = wiringPiI2CReadReg8(fd, HMC5883L_REG_LSB_Y);
  short y = msb << 8 | lsb;

  msb = wiringPiI2CReadReg8(fd, HMC5883L_REG_MSB_Z);
  lsb = wiringPiI2CReadReg8(fd, HMC5883L_REG_LSB_Z);
  short z = msb << 8 | lsb;

  double angle = atan2((double) y, (double)x) * (180 / PI) + 180;

  printf("x=%d, y=%d, z=%d - angle=%f\n",x, y, z, angle);
  sleep(1);
  }

  return 0;
}
