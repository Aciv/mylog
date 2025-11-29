CXX = g++
CFLAGS = -std=c++20 -O2 -Wall -g 

TARGET = logTest
OBJS = ../buffer/*.cpp ../log/*.cpp ../*.cpp ../sender/*.cpp

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o ../bin/$(TARGET)  

clean:
	rm -r -fo ../bin/$(OBJS) $(TARGET)


