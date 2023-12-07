# A simple Makefile for compiling small SDL projects

# set the compiler
CXX := clang

# architecture
ARC := -arch arm64

# set the compiler flags
CXXFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image
# -lSDL2 -lSDL2_image -lSDL2_net -lm
# add header files here
HDRS :=

# add source files here
SRCS := main.cpp ctrlgpio.cpp motor.cpp 

# generate names of object files
OBJS := $(SRCS:.cpp=.o)

# name of executable
EXEC := main

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CXX) $(ARC) -o $@ $(OBJS) $(CXXFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
#    $(CXX) -o $@ $(@:.o=.cpp) -c $(CXXFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean