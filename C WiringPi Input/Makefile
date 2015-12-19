APP=input1
OBJS=input.o

#----
PI_ROOT=/mnt/pi/root
PRE=arm-linux-gnueabihf-
CC=$(PRE)gcc

# The directory into which the final application will be copied
# during a 'make install'.
OUTPUT_DIR=/mnt/pi/home/src/builds
INCLUDES=-I$(PI_ROOT)/usr/local/include
LIBDIRSS=-L$(PI_ROOT)/usr/local/lib
LIBS=-lwiringPi

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LIBDIRSS) -o $(APP) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) -c $< -o $@
	
clean:
	rm -f $(APP) $(OBJS)

install: all
	cp $(APP) $(OUTPUT_DIR)