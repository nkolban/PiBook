/*
 * BCM2835.h
 *
 *  Created on: Dec 30, 2015
 *      Author: kolban
 */

#ifndef BCM2835_H_
#define BCM2835_H_
#include <stdint.h>

#define BCM2835_BASE (0x3f000000)
#define GPIO_OFFSET (0x200000)

#define GPFSEL0 registerToAddress(GPIO_OFFSET, 0x00)
#define GPFSEL1 registerToAddress(GPIO_OFFSET, 0x04)
#define GPFSEL2 registerToAddress(GPIO_OFFSET, 0x08)
#define GPFSEL3 registerToAddress(GPIO_OFFSET, 0x0c)
#define GPFSEL4 registerToAddress(GPIO_OFFSET, 0x10)
#define GPFSEL5 registerToAddress(GPIO_OFFSET, 0x14)


enum {
  GPIO_FUNCTION_INPUT     = 0x0,
  GPIO_FUNCTION_OUTPUT    = 0x1,
  GPIO_FUNCTION_FUNCTION0 = 0x4,
  GPIO_FUNCTION_FUNCTION1 = 0x5,
  GPIO_FUNCTION_FUNCTION2 = 0x6,
  GPIO_FUNCTION_FUNCTION3 = 0x7,
  GPIO_FUNCTION_FUNCTION4 = 0x3,
  GPIO_FUNCTION_FUNCTION5 = 0x2
} GPIO_FUNCTION;

volatile uint8_t *registerToAddress(uint32_t base, uint32_t offset);
void init();

#endif /* BCM2835_H_ */
