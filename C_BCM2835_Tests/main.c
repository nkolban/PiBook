#include <stdio.h>
#include "pibase.h"

int main(int argc, char *argv[]) {
  printf("Starting\n");
  init();
  int pin;
  for (pin=0; pin<30; pin++) {
    int function = getFunction(pin);

    printf("pin: %d - function=0x%x, meaning=%s\n", pin, function, functionToString(function));
  }
  //getFunction(17);
}
