APP=test1
OBJS=LedControl.o DemoMatrix.o

all: $(APP)

$(APP): $(OBJS)
	$(CXX) -o $(APP) $(OBJS) -L/usr/local/lib -lwiringPi

.cpp.c:
	$(CXX) -c $< -o $@