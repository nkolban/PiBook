/*
 * hmc5883l.h
 *
 *  Created on: Dec 13, 2015
 *      Author: kolban
 */

#ifndef HMC5883L_H_
#define HMC5883L_H_

#define HMC5883L_ADDRESS (0x1e)

#define HCM5883L_REG_CONFIG_A (0x00)
#define HCM5883L_REG_CONFIG_B (0x01)
#define HMC5883L_REG_MODE     (0x02)
#define HMC5883L_REG_MSB_X    (0x03)
#define HMC5883L_REG_LSB_X    (0x04)
#define HMC5883L_REG_MSB_Z    (0x05)
#define HMC5883L_REG_LSB_Z    (0x06)
#define HMC5883L_REG_MSB_Y    (0x07)
#define HMC5883L_REG_LSB_Y    (0x08)
#define HMC5883L_REG_STATUS   (0x09)
#define HMC5883L_REG_ID_A     (0x0a)
#define HMC5883L_REG_ID_B     (0x0b)
#define HMC5883L_REG_ID_C     (0x0c)

#define HMC5883L_MODE_CONTINUOUS (0x00)
#define HMC5883L_MODE_SINGLE     (0x01)

#endif /* HMC5883L_H_ */
