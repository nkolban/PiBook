#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>

int main(int argc, char *argv[]) {
  printf("Starting LCD test\n");

  int rc = wiringPiSetupGpio();
  int handle = lcdInit(2, // rows
      16, // columns
      4,  // bits
      17, // rs
      27, // enable
      22, // d0
      5,  // d1
      6,  // d2
      13, // d3
      0,0,0,0); // d4-d7
  lcdClear(handle);
  lcdPuts(handle, "Hello World!");
  int i=0;
  while(1) {
    lcdPosition(handle, 0, 1);
    lcdPrintf(handle, "%d", i);
    i++;
  }
}
