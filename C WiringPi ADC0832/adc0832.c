#include <stdio.h>
#include <wiringPi.h>

#define CLK 17
#define DIO 27
#define CS 22

int getValue() {
  pinMode(CLK, OUTPUT);
  pinMode(CS,  OUTPUT);
  pinMode(DIO, OUTPUT);

  digitalWrite(CLK, LOW);
  digitalWrite(CS,  LOW);

  digitalWrite(DIO, HIGH); // Start bit
  delay(10);
  digitalWrite(CLK, HIGH);
  delay(10);
  digitalWrite(CLK, LOW);
  delay(10);

  digitalWrite(DIO, HIGH); // SGL
  digitalWrite(CLK, HIGH);
  delay(10);
  digitalWrite(CLK, LOW);
  delay(10);

  digitalWrite(DIO, LOW); // Choose channel 0
  digitalWrite(CLK, HIGH);
  delay(10);
  pinMode(DIO, INPUT);
  digitalWrite(CLK, LOW);
  delay(10);

  digitalWrite(CLK, HIGH); // Skip a clock
  delay(10);
  digitalWrite(CLK, LOW);
  delay(10);

  // Read the value
  int value = 0;
  int i;
  for (i=0; i<8; i++) {
    digitalWrite(CLK, HIGH);
    int bit = digitalRead(DIO);
    value = value << 1 | bit;
    delay(10);
    digitalWrite(CLK, LOW);
    delay(10);
  }
  digitalWrite(CS, HIGH);
  return value;
}

int main(int argc, char *argv[]) {
  printf("Starting ADC test\n");


  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }
  while(1) {
    int value = getValue();
    printf("value=%d\n", value);
    sleep(2);
  }
}
