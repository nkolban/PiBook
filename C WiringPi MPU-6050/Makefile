APP=mpu6050
OBJS=mpu6050.o

CC=gcc

INCLUDES=-I/usr/local/include
LIBDIRSS=-L/usr/local/lib
LIBS=-lwiringPi

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LIBDIRSS) -o $(APP) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) -c $< -o $@
	
clean:
	rm -f $(APP) $(OBJS)