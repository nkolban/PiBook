#include <stdio.h>
#include <wiringPi.h>

#define DIN  (5)  // MCP3208 Input
#define DOUT (6)  // MCP3208 Output
#define CS   (13) // MCP3208 CS
#define CLK  (19) // MCP3208 Clock

#define CLK_MICROS (100)

int clockCycle = 0;
void clock() {
  if (clockCycle == 0) {
    digitalWrite(CLK, LOW);
  } else {
    digitalWrite(CLK, HIGH);
  }
  delayMicroseconds(CLK_MICROS/2);
  clockCycle = !clockCycle;
}

int getValue() {
  // Start
  digitalWrite(CS, LOW);
  digitalWrite(DIN, HIGH);
  clock(); clock();

  digitalWrite(DIN, HIGH); // Single/Differential
  clock(); clock();

  digitalWrite(DIN, LOW); // D2
  clock(); clock();
  digitalWrite(DIN, LOW); // D1
  clock(); clock();
  digitalWrite(DIN, LOW); // D0
  clock(); clock();

  // Skip 2 clock cycles
  clock(); clock();
  clock(); clock();

  int i;
  int value = 0;
  for (i=0; i<12; i++) {
    clock();
    value = (value << 1) | digitalRead(DOUT);
    clock();
  }
  digitalWrite(CS, HIGH);
  return value;
}

int main(int argc, char *argv[]) {
  printf("Starting MCP3208 test\n");
  int rc = wiringPiSetupGpio();
  if (rc != 0) {
    printf("Failed to wiringPiSetupGpio()\n");
    return 0;
  }

  pinMode(DOUT, INPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  digitalWrite(CS, HIGH);
  digitalWrite(CLK, HIGH);

  while(1) {
    int value = getValue();
    printf("Value = %d\n", value);
    sleep(1);
  }
}
