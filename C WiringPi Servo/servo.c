#include <stdio.h>
#include <wiringPi.h>

#define PIN (18)

int main(int argc, char *argv[]) {
  printf("Starting servo test\n");
  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  pinMode(PIN, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(3840);
  pwmSetRange(100);

  while(1) {
    int i;
    for (i=3; i<12; i++) {
      pwmWrite(PIN, i);
      delay(1000);
    }
    for (i=11; i>2; i--) {
      pwmWrite(PIN, i);
      delay(1000);
    }
  }
}
