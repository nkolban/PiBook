#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include "pibase.h"
#include "BCM2835.h"

/**
 * Given a pin, retrieve the function code for that pin.
 */
int getFunction(int pin) {
  assert(pin >=0 && pin < 54);
  int bank = pin / 10;
  volatile uint8_t *registerAddress;
  switch(bank) {
  case 0:
    registerAddress = GPFSEL0;
    break;
  case 1:
    registerAddress = GPFSEL1;
    break;
  case 2:
    registerAddress = GPFSEL2;
    break;
  case 3:
    registerAddress = GPFSEL3;
    break;
  case 4:
    registerAddress = GPFSEL4;
    break;
  case 5:
    registerAddress = GPFSEL5;
    break;
  }

  uint32_t value = *(volatile uint32_t *)(registerAddress);
  value = (value >> (3*(pin%10))) & 0x7;
  //printf("value: %x\n", value);
  return value;
}

void setPinFunction(int pin, int function) {

}

/**
 * Given a GPIO function, return a string representation of what that function means.
 */
char *functionToString(int function) {
  switch(function) {
  case GPIO_FUNCTION_INPUT:
    return "Input";
  case GPIO_FUNCTION_OUTPUT:
    return "Output";
  case GPIO_FUNCTION_FUNCTION0:
    return "Function 0";
  case GPIO_FUNCTION_FUNCTION1:
    return "Function 1";
  case GPIO_FUNCTION_FUNCTION2:
    return "Function 2";
  case GPIO_FUNCTION_FUNCTION3:
    return "Function 3";
  case GPIO_FUNCTION_FUNCTION4:
    return "Function 4";
  case GPIO_FUNCTION_FUNCTION5:
    return "Function 5";
  default:
    return "Unknown";
  }
}
