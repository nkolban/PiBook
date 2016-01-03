//We always have to include the library
#include <stdio.h>
#include <unistd.h>
#include "LedControl.h"

void writeArduinoOnMatrix();
void rows();
void columns();
void single();

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn
 pin 11 is connected to the CLK
 pin 10 is connected to LOAD
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100 * 1000;

int main(int argc, char *argv[]) {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
    */
   lc.shutdown(0,false);
   /* Set the brightness to a medium values */
   lc.setIntensity(0,8);
   /* and clear the display */
   lc.clearDisplay(0);
   while(1) {
     printf("Hi!\n");
     writeArduinoOnMatrix();
     rows();
     columns();
     single();
   }
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix.
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  uint8_t a[5]={0b01111110,0b10001000,0b10001000,0b10001000,0b01111110};
  uint8_t r[5]={0b00111110,0b00010000,0b00100000,0b00100000,0b00010000};
  uint8_t d[5]={0b00011100,0b00100010,0b00100010,0b00010010,0b11111110};
  uint8_t u[5]={0b00111100,0b00000010,0b00000010,0b00000100,0b00111110};
  uint8_t i[5]={0b00000000,0b00100010,0b10111110,0b00000010,0b00000000};
  uint8_t n[5]={0b00111110,0b00010000,0b00100000,0b00100000,0b00011110};
  uint8_t o[5]={0b00011100,0b00100010,0b00100010,0b00100010,0b00011100};

  /* now display them one by one with a small delay */
  lc.setRow(0,0,a[0]);
  lc.setRow(0,1,a[1]);
  lc.setRow(0,2,a[2]);
  lc.setRow(0,3,a[3]);
  lc.setRow(0,4,a[4]);
  sleep(1);
  lc.setRow(0,0,r[0]);
  lc.setRow(0,1,r[1]);
  lc.setRow(0,2,r[2]);
  lc.setRow(0,3,r[3]);
  lc.setRow(0,4,r[4]);
  sleep(1);
  lc.setRow(0,0,d[0]);
  lc.setRow(0,1,d[1]);
  lc.setRow(0,2,d[2]);
  lc.setRow(0,3,d[3]);
  lc.setRow(0,4,d[4]);
  sleep(1);
  lc.setRow(0,0,u[0]);
  lc.setRow(0,1,u[1]);
  lc.setRow(0,2,u[2]);
  lc.setRow(0,3,u[3]);
  lc.setRow(0,4,u[4]);
  sleep(1);
  lc.setRow(0,0,i[0]);
  lc.setRow(0,1,i[1]);
  lc.setRow(0,2,i[2]);
  lc.setRow(0,3,i[3]);
  lc.setRow(0,4,i[4]);
  sleep(1);
  lc.setRow(0,0,n[0]);
  lc.setRow(0,1,n[1]);
  lc.setRow(0,2,n[2]);
  lc.setRow(0,3,n[3]);
  lc.setRow(0,4,n[4]);
  sleep(1);
  lc.setRow(0,0,o[0]);
  lc.setRow(0,1,o[1]);
  lc.setRow(0,2,o[2]);
  lc.setRow(0,3,o[3]);
  lc.setRow(0,4,o[4]);
  sleep(1);
  lc.setRow(0,0,0);
  lc.setRow(0,1,0);
  lc.setRow(0,2,0);
  lc.setRow(0,3,0);
  lc.setRow(0,4,0);
  sleep(1);
}

/*
  This function lights up a some Leds in a row.
 The pattern will be repeated on every row.
 The pattern will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void rows() {
  for(int row=0;row<8;row++) {
    usleep(delaytime);
    lc.setRow(0,row,0b10100000);
    usleep(delaytime);
    lc.setRow(0,row,(uint8_t)0);
    for(int i=0;i<row;i++) {
      usleep(delaytime);
      lc.setRow(0,row,0b10100000);
      usleep(delaytime);
      lc.setRow(0,row,(uint8_t)0);
    }
  }
}

/*
  This function lights up a some Leds in a column.
 The pattern will be repeated on every column.
 The pattern will blink along with the column-number.
 column number 4 (index==3) will blink 4 times etc.
 */
void columns() {
  for(int col=0;col<8;col++) {
    usleep(delaytime);
    lc.setColumn(0,col,0b10100000);
    usleep(delaytime);
    lc.setColumn(0,col,(uint8_t)0);
    for(int i=0;i<col;i++) {
      usleep(delaytime);
      lc.setColumn(0,col,0b10100000);
      usleep(delaytime);
      lc.setColumn(0,col,(uint8_t)0);
    }
  }
}

/*
 This function will light up every Led on the matrix.
 The led will blink along with the row-number.
 row number 4 (index==3) will blink 4 times etc.
 */
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      usleep(delaytime);
      lc.setLed(0,row,col,true);
      usleep(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        usleep(delaytime);
        lc.setLed(0,row,col,true);
        usleep(delaytime);
      }
    }
  }
}

void loop() {

}
