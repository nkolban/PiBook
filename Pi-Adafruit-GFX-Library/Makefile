APP=libAdafruitGFX.a
OBJS=Adafruit_GFX.o

#----
PI_ROOT=/mnt/pi/root
PRE=arm-linux-gnueabihf-
CC=$(PRE)gcc
CXX=$(PRE)g++


# The directory into which the final application will be copied
# during a 'make install'.
OUTPUT_DIR=/mnt/pi/home/src/builds
INCLUDES=-I$(PI_ROOT)/usr/local/include -I/home/kolban/pi/src/Workspace/Arduino-to-Pi

all: $(APP)

$(APP): $(OBJS)
	$(AR) crv $(APP) $(OBJS)


.c.o:
	$(CC) $(INCLUDES) -c $< -o $@

.cpp.o:
	$(CXX) $(INCLUDES) -c $< -o $@
		
clean:
	rm -f $(APP) $(OBJS)

install: all
	cp $(APP) $(OUTPUT_DIR)