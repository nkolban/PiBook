APP=client
OBJS=client.o

all: $(APP)

$(APP): $(OBJS)
	$(CC) -o $(APP) $(OBJS) -lmosquitto

.c.o:
	$(CC) -c $< -o $@
	
clean:
	rm -rf $(OBJS) $(APP)
