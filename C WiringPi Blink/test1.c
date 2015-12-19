#include <stdio.h>
#include <wiringPi.h>

#define PIN (17)

int main(int argc, char *argv[]) {
  printf("Starting blink test\n");
  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  int value = HIGH;

  pinMode(PIN, OUTPUT);

  while(1) {
    digitalWrite(PIN, value);
    delay(500);
    value= value==HIGH?LOW:HIGH;
  }
}
