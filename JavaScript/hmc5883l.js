var wpi = require('wiring-pi');

wpi.setup('wpi');
var HMC5883L_ADDRESS = 0x1e;

var HCM5883L_REG_CONFIG_A = 0x00;
var HCM5883L_REG_CONFIG_B = 0x01;

var HMC5883L_REG_MODE =   0x02;
var HMC5883L_REG_MSB_X =  0x03;
var HMC5883L_REG_LSB_X =  0x04;
var HMC5883L_REG_MSB_Z =  0x05;
var HMC5883L_REG_LSB_Z =  0x06;
var HMC5883L_REG_MSB_Y =  0x07;
var HMC5883L_REG_LSB_Y =  0x08;
var HMC5883L_REG_STATUS = 0x09;
var HMC5883L_REG_ID_A =   0x0a;
var HMC5883L_REG_ID_B =   0x0b;
var HMC5883L_REG_ID_C =   0x0c;

var HMC5883L_MODE_CONTINUOUS = 0x00;
var HMC5883L_MODE_SINGLE = 0x01;

var fd = wpi.wiringPiI2CSetup(HMC5883L_ADDRESS);
wpi.wiringPiI2CWriteReg8(fd, HMC5883L_REG_MODE, HMC5883L_MODE_CONTINUOUS);

function toShort(value) {
  value = value & 0xffff;
  if ((value & (1<<15)) == 0) {
    return value;
  }
  return (value & ~(1<<15)) - (1<<15);
}

setInterval(function() {
  var msb = wpi.wiringPiI2CReadReg8(fd, HMC5883L_REG_MSB_X);
  var lsb = wpi.wiringPiI2CReadReg8(fd, HMC5883L_REG_LSB_X);
  var x = toShort(msb << 8 | lsb);

  msb = wpi.wiringPiI2CReadReg8(fd, HMC5883L_REG_MSB_Y);
  lsb = wpi.wiringPiI2CReadReg8(fd, HMC5883L_REG_LSB_Y);
  var y = toShort(msb << 8 | lsb);

  msb = wpi.wiringPiI2CReadReg8(fd, HMC5883L_REG_MSB_Z);
  lsb = wpi.wiringPiI2CReadReg8(fd, HMC5883L_REG_LSB_Z);
  var z = toShort(msb << 8 | lsb);
  console.log("x=" + x + ", y=" + y + ", z=" + z);
}, 1000);
