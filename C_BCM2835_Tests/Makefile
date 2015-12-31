APP1=app1
OBJS=gpio.o main.o BCM2835.o

$(APP1): $(OBJS)
	$(CC) -o $(APP1) $(OBJS)

.c.o:
	$(CC) -g -c $< -o $@

clean:
	rm -f $(APP1) $(OBJS)