APP=curltest1
OBJS=curltest.o

#----
PI_ROOT=/mnt/pi/root
PRE=arm-linux-gnueabihf
CC=$(PRE)-gcc
LD=$(PRE)-ld

# The directory into which the final application will be copied
# during a 'make install'.
OUTPUT_DIR=/mnt/pi/home/src/builds
INCLUDES=-I$(PI_ROOT)/usr/local/include \
-I$(PI_ROOT)/usr/include/curl
LIBDIRS=-L$(PI_ROOT)/usr/local/lib \
-L$(PI_ROOT)/usr/lib/$(PRE)
LIBS=-lcurl

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LIBDIRS) \
	-Wl,-rpath-link $(PI_ROOT)/usr/lib/$(PRE) \
	-Wl,-rpath-link $(PI_ROOT)/lib/$(PRE) \
	-o $(APP) $(OBJS) $(LIBS) 

.c.o:
	$(CC) $(INCLUDES) -Wall -c $< -o $@
	
clean:
	rm -f $(APP) $(OBJS)

install: all
	cp $(APP) $(OUTPUT_DIR)