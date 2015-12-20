#include <stdio.h>
#include <wiringPi.h>

#define TRIG (17)
#define ECHO (27)

int main(int argc, char *argv[]) {
  printf("Starting HC-SR04 test\n");
  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  int value = HIGH;

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

  delay(50);

  while(1) {
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    unsigned int echoStart = millis();
    while(digitalRead(ECHO) == LOW && millis()-echoStart < 1000) {
      // do nothing
    }
    if (millis()-echoStart < 1000) {
      // Mark start
      unsigned int start = micros();
      while(digitalRead(ECHO) == HIGH) {
         // do nothing
      }
      // Mark end
      unsigned int end = micros();
      unsigned int delta = end-start;

      double distance = 34029 * delta / 2000000.0;
      printf("Distance: %f\n", distance);
    }
    sleep(1000);
  } // End while(1)
}
