/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <wiringPi.h>
#include <stdlib.h>
#include "binary.h"

#define max(a,b) (((a) (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK) - SCLK
// pin 6 - Serial data out (DIN) - MOSI
// pin 5 - Data/Command select (D/C) - 22
// pin 4 - LCD chip select (CS) - 17
// pin 3 - LCD reset (RST) - 27
Adafruit_PCD8544 *pDisplay;

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

void testdrawline();
void testdrawrect(void);
void testfillroundrect(void);
void testdrawroundrect(void);
void testfilltriangle(void);
void testdrawtriangle(void);
void testfillrect(void);
void testdrawcircle(void);
void testdrawchar(void);
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h);

static const unsigned char logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

int main(int argc, char *argv[]) {

  // Initialize wiring Pi
  wiringPiSetupGpio();
  pDisplay = new Adafruit_PCD8544(22, 17, 27);
  pDisplay->begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  pDisplay->setContrast(50);

  pDisplay->display(); // show splashscreen
  delay(2000);
  pDisplay->clearDisplay();   // clears the screen and buffer

  // draw a single pixel
  pDisplay->drawPixel(10, 10, BLACK);
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  // draw many lines
  testdrawline();
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  // draw rectangles
  testdrawrect();
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  // draw multiple rectangles
  testfillrect();
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  // draw mulitple circles
  testdrawcircle();
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  // draw a circle, 10 pixel radius
  pDisplay->fillCircle(pDisplay->width()/2, pDisplay->height()/2, 10, BLACK);
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  testdrawroundrect();
  delay(2000);
  pDisplay->clearDisplay();

  testfillroundrect();
  delay(2000);
  pDisplay->clearDisplay();

  testdrawtriangle();
  delay(2000);
  pDisplay->clearDisplay();
   
  testfilltriangle();
  delay(2000);
  pDisplay->clearDisplay();

  // draw the first ~12 characters in the font
  testdrawchar();
  pDisplay->display();
  delay(2000);
  pDisplay->clearDisplay();

  // text display tests
  pDisplay->setTextSize(1);
  pDisplay->setTextColor(BLACK);
  pDisplay->setCursor(0,0);
  pDisplay->println("Hello, world!");
  pDisplay->setTextColor(WHITE, BLACK); // 'inverted' text
  pDisplay->println(3.141592);
  pDisplay->setTextSize(2);
  pDisplay->setTextColor(BLACK);
  pDisplay->print("0x"); pDisplay->println("DEADBEEF");
  pDisplay->display();
  delay(2000);

  // rotation example
  pDisplay->clearDisplay();
  pDisplay->setRotation(1);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
  pDisplay->setTextSize(1);
  pDisplay->setTextColor(BLACK);
  pDisplay->setCursor(0,0);
  pDisplay->println("Rotation");
  pDisplay->setTextSize(2);
  pDisplay->println("Example!");
  pDisplay->display();
  delay(2000);

  // revert back to no rotation
  pDisplay->setRotation(0);

  // miniature bitmap display
  pDisplay->clearDisplay();
  pDisplay->drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  pDisplay->display();

  // invert the display
  pDisplay->invertDisplay(true);
  delay(1000); 
  pDisplay->invertDisplay(false);
  delay(1000); 

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_WIDTH, LOGO16_GLCD_HEIGHT);
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  srandom(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random()%pDisplay->width();
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random()%5 + 1;
    
    /*
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
    */
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      pDisplay->drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, BLACK);
    }
    pDisplay->display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      pDisplay->drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, WHITE);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > pDisplay->height()) {
	icons[f][XPOS] = random()%pDisplay->width();
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random()%5 + 1;
      }
    }
   }
}


void testdrawchar(void) {
  pDisplay->setTextSize(1);
  pDisplay->setTextColor(BLACK);
  pDisplay->setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    pDisplay->write(i);
    //if ((i > 0) && (i % 14 == 0))
      //pDisplay->println();
  }    
  pDisplay->display();
}

void testdrawcircle(void) {
  for (int16_t i=0; i<pDisplay->height(); i+=2) {
    pDisplay->drawCircle(pDisplay->width()/2, pDisplay->height()/2, i, BLACK);
    pDisplay->display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<pDisplay->height()/2; i+=3) {
    // alternate colors
    pDisplay->fillRect(i, i, pDisplay->width()-i*2, pDisplay->height()-i*2, color%2);
    pDisplay->display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(pDisplay->width(),pDisplay->height())/2; i+=5) {
    pDisplay->drawTriangle(pDisplay->width()/2, pDisplay->height()/2-i,
                     pDisplay->width()/2-i, pDisplay->height()/2+i,
                     pDisplay->width()/2+i, pDisplay->height()/2+i, BLACK);
    pDisplay->display();
  }
}

void testfilltriangle(void) {
  uint8_t color = BLACK;
  for (int16_t i=min(pDisplay->width(),pDisplay->height())/2; i>0; i-=5) {
    pDisplay->fillTriangle(pDisplay->width()/2, pDisplay->height()/2-i,
                     pDisplay->width()/2-i, pDisplay->height()/2+i,
                     pDisplay->width()/2+i, pDisplay->height()/2+i, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    pDisplay->display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<pDisplay->height()/2-2; i+=2) {
    pDisplay->drawRoundRect(i, i, pDisplay->width()-2*i, pDisplay->height()-2*i, pDisplay->height()/4, BLACK);
    pDisplay->display();
  }
}

void testfillroundrect(void) {
  uint8_t color = BLACK;
  for (int16_t i=0; i<pDisplay->height()/2-2; i+=2) {
    pDisplay->fillRoundRect(i, i, pDisplay->width()-2*i, pDisplay->height()-2*i, pDisplay->height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    pDisplay->display();
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<pDisplay->height()/2; i+=2) {
    pDisplay->drawRect(i, i, pDisplay->width()-2*i, pDisplay->height()-2*i, BLACK);
    pDisplay->display();
  }
}

void testdrawline() {  
  for (int16_t i=0; i<pDisplay->width(); i+=4) {
    pDisplay->drawLine(0, 0, i, pDisplay->height()-1, BLACK);
    pDisplay->display();
  }
  for (int16_t i=0; i<pDisplay->height(); i+=4) {
    pDisplay->drawLine(0, 0, pDisplay->width()-1, i, BLACK);
    pDisplay->display();
  }
  delay(250);
  
  pDisplay->clearDisplay();
  for (int16_t i=0; i<pDisplay->width(); i+=4) {
    pDisplay->drawLine(0, pDisplay->height()-1, i, 0, BLACK);
    pDisplay->display();
  }
  for (int8_t i=pDisplay->height()-1; i>=0; i-=4) {
    pDisplay->drawLine(0, pDisplay->height()-1, pDisplay->width()-1, i, BLACK);
    pDisplay->display();
  }
  delay(250);
  
  pDisplay->clearDisplay();
  for (int16_t i=pDisplay->width()-1; i>=0; i-=4) {
    pDisplay->drawLine(pDisplay->width()-1, pDisplay->height()-1, i, 0, BLACK);
    pDisplay->display();
  }
  for (int16_t i=pDisplay->height()-1; i>=0; i-=4) {
    pDisplay->drawLine(pDisplay->width()-1, pDisplay->height()-1, 0, i, BLACK);
    pDisplay->display();
  }
  delay(250);

  pDisplay->clearDisplay();
  for (int16_t i=0; i<pDisplay->height(); i+=4) {
    pDisplay->drawLine(pDisplay->width()-1, 0, 0, i, BLACK);
    pDisplay->display();
  }
  for (int16_t i=0; i<pDisplay->width(); i+=4) {
    pDisplay->drawLine(pDisplay->width()-1, 0, i, pDisplay->height()-1, BLACK);
    pDisplay->display();
  }
  delay(250);
}
