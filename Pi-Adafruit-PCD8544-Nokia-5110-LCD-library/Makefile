OBJS=Adafruit_PCD8544.o
PI_ROOT=/mnt/pi/root
PRE=arm-linux-gnueabihf-
CC=$(PRE)gcc
CXX=$(PRE)g++
INCLUDES=-I$(PI_ROOT)/usr/local/include -I/home/kolban/git/Adafruit-GFX-Library -I../..
LIBDIR=-L/home/kolban/git/Adafruit-GFX-Library -L$(PI_ROOT)/usr/local/lib
LIBS=-lwiringPi -lAdafruitGFX

all: $(OBJS)

.cpp.o:
	$(CXX) $(INCLUDES) -c $< -o $@

clean:
	rm -rf *.o