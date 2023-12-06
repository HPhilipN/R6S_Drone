# A simple Makefile for compiling small SDL projects

# set the compiler
CXX := g++

# set the compiler flags
CXXFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm
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
 
showfont: showfont.c Makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

glfont: glfont.c Makefile
	$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)

# recipe for building object files
#$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
#    $(CXX) -o $@ $(@:.o=.cpp) -c $(CXXFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean