/*
 * LedControl.h
 *
 *  Created on: Jan 2, 2016
 *      Author: kolban
 */

#ifndef LEDCONTROL_H_
#define LEDCONTROL_H_

#include <stdint.h>

/*
 * Segments to be switched on for characters and digits on
 * 7-Segment Displays
 */
const static uint8_t charTable []  = {
    0b01111110,0b00110000,0b01101101,0b01111001,0b00110011,0b01011011,0b01011111,0b01110000,
    0b01111111,0b01111011,0b01110111,0b00011111,0b00001101,0b00111101,0b01001111,0b01000111,
    0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
    0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
    0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
    0b00000000,0b00000000,0b00000000,0b00000000,0b10000000,0b00000001,0b10000000,0b00000000,
    0b01111110,0b00110000,0b01101101,0b01111001,0b00110011,0b01011011,0b01011111,0b01110000,
    0b01111111,0b01111011,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
    0b00000000,0b01110111,0b00011111,0b00001101,0b00111101,0b01001111,0b01000111,0b00000000,
    0b00110111,0b00000000,0b00000000,0b00000000,0b00001110,0b00000000,0b00000000,0b00000000,
    0b01100111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
    0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001000,
    0b00000000,0b01110111,0b00011111,0b00001101,0b00111101,0b01001111,0b01000111,0b00000000,
    0b00110111,0b00000000,0b00000000,0b00000000,0b00001110,0b00000000,0b00010101,0b00011101,
    0b01100111,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
    0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000
};

class LedControl {
    private :
        /* The array for shifting the data to the devices */
        uint8_t spidata[16];
        /* Send out a single command to the device */
        void spiTransfer(int addr, uint8_t opcode, uint8_t data);

        /* We keep track of the led-status for all 8 devices in this array */
        uint8_t status[64];
        /* Data is shifted out of this pin*/
        int SPI_MOSI;
        /* The clock is signaled on this pin */
        int SPI_CLK;
        /* This one is driven LOW for chip selectzion */
        int SPI_CS;
        /* The maximum number of devices we use */
        int maxDevices;

    public:
        /*
         * Create a new controler
         * Params :
         * dataPin    pin on the Arduino where data gets shifted out
         * clockPin   pin for the clock
         * csPin    pin for selecting the device
         * numDevices maximum number of devices that can be controled
         */
        LedControl(int csPin, int numDevices=1);

        /*
         * Gets the number of devices attached to this LedControl.
         * Returns :
         * int  the number of devices on this LedControl
         */
        int getDeviceCount();

        /*
         * Set the shutdown (power saving) mode for the device
         * Params :
         * addr The address of the display to control
         * status If true the device goes into power-down mode. Set to false
         *    for normal operation.
         */
        void shutdown(int addr, bool status);

        /*
         * Set the number of digits (or rows) to be displayed.
         * See datasheet for sideeffects of the scanlimit on the brightness
         * of the display.
         * Params :
         * addr address of the display to control
         * limit  number of digits to be displayed (1..8)
         */
        void setScanLimit(int addr, int limit);

        /*
         * Set the brightness of the display.
         * Params:
         * addr   the address of the display to control
         * intensity  the brightness of the display. (0..15)
         */
        void setIntensity(int addr, int intensity);

        /*
         * Switch all Leds on the display off.
         * Params:
         * addr address of the display to control
         */
        void clearDisplay(int addr);

        /*
         * Set the status of a single Led.
         * Params :
         * addr address of the display
         * row  the row of the Led (0..7)
         * col  the column of the Led (0..7)
         * state  If true the led is switched on,
         *    if false it is switched off
         */
        void setLed(int addr, int row, int col, bool state);

        /*
         * Set all 8 Led's in a row to a new state
         * Params:
         * addr address of the display
         * row  row which is to be set (0..7)
         * value  each bit set to 1 will light up the
         *    corresponding Led.
         */
        void setRow(int addr, int row, uint8_t value);

        /*
         * Set all 8 Led's in a column to a new state
         * Params:
         * addr address of the display
         * col  column which is to be set (0..7)
         * value  each bit set to 1 will light up the
         *    corresponding Led.
         */
        void setColumn(int addr, int col, uint8_t value);

        /*
         * Display a hexadecimal digit on a 7-Segment Display
         * Params:
         * addr address of the display
         * digit  the position of the digit on the display (0..7)
         * value  the value to be displayed. (0x00..0x0F)
         * dp sets the decimal point.
         */
        void setDigit(int addr, int digit, uint8_t value, bool dp);

        /*
         * Display a character on a 7-Segment display.
         * There are only a few characters that make sense here :
         *  '0','1','2','3','4','5','6','7','8','9','0',
         *  'A','b','c','d','E','F','H','L','P',
         *  '.','-','_',' '
         * Params:
         * addr address of the display
         * digit  the position of the character on the display (0..7)
         * value  the character to be displayed.
         * dp sets the decimal point.
         */
        void setChar(int addr, int digit, char value, bool dp);

        /*
         * Display a decimal number on a set of 7-Segment displays.
         * Params:
         * addr address of the display
         * num the number to display
         * numDecimals the number of digits after the decimal point to display
         */
        void setNumber(int addr, double num, int numDecimals);
};

#endif /* LEDCONTROL_H_ */
