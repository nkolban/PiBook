APP=gpsclient
OBJS=gpsclient.o

#----
PRE=
CC=$(PRE)gcc

LIBS=-lgps

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LIBDIRS) -o $(APP) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) -g -c $< -o $@
	
clean:
	rm -f $(APP) $(OBJS)

install: all
	cp $(APP) $(OUTPUT_DIR)
