#include <stdio.h>
#include <wiringPi.h>

#define PIN (17)

static void callback() {
  printf("The interrupt was triggered");
}

int main(int argc, char *argv[]) {
  printf("Starting input test\n");
  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  pinMode(PIN, INPUT);
  pullUpDnControl(PIN, PUD_UP);
  wiringPiISR(PIN, INT_EDGE_RISING, callback);

  while(1) {
    delay(50000);
  }
}
