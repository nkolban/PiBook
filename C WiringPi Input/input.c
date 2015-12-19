#include <stdio.h>
#include <wiringPi.h>

#define PIN (17)

int main(int argc, char *argv[]) {
  printf("Starting input test\n");
  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  pinMode(PIN, INPUT);
  pullUpDnControl(PIN, PUD_UP);

  while(1) {
    int value = digitalRead(PIN);
    printf("Value is %d\n", value);
    delay(500);
  }
}
