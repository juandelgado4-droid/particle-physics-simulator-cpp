CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

TARGET = physics_sim

SRCS = src/PhysicsWorld.cpp src/main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe

.PHONY: all clean
