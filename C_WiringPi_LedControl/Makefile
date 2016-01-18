APP1=DemoMatrix
APP2=LCDemo7Segment
APP1_OBJS=LedControl.o DemoMatrix.o
APP2_OBJS=LedControl.o LCDemo7Segment.o

all: $(APP1) $(APP2)

$(APP1): $(APP1_OBJS)
	$(CXX) -o $(APP1) $(APP1_OBJS) -L/usr/local/lib -lwiringPi

$(APP2): $(APP2_OBJS)
	$(CXX) -o $(APP2) $(APP2_OBJS) -L/usr/local/lib -lwiringPi

.cpp.c:
	$(CXX) -c $< -o $@

clean:
	rm -f *.o $(APP1) $(APP2)