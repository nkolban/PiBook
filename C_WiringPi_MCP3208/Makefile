APP=mcp3208
OBJS=MCP3208.o

all: $(APP)

$(APP): $(OBJS)
	$(CC) -o $(APP) $(OBJS) -L/usr/local/lib -lwiringPi

.cpp.c:
	$(CC) -c $< -o $@
