# Makefile 
# CSCI 480
# Assignment 1
# makefile reformatted and rewritten for current assignment
# could be more dynamic in the future, but for now want to have easy readability to help us ensure how the project is working / compiling together


# we assume the pic directory locates one level above,
# change PIC_PATH if this is not the case
# PIC_PATH = $(abspath $(CURDIR)/../pic)
PIC_PATH = /usr/local/src/pic

# set up include paths -- places to look for header files
INCLUDE = -I$(PIC_PATH)
# include path for headers to search in
INCLUDE += -I include

# declare the cpp file base path
VPATH = src 
# declare the build directory
BUILDDIR = build
# include proper libraries etc
LIBRARIES = -L$(PIC_PATH) -framework OpenGL -framework GLUT -lpicio -ljpeg
# use the g++ 4.8 compiler instead of the defaul apple xcode cli tools installed version (4.2)
COMPILER = /usr/local/gcc/usr/local/bin/g++
# be sure to pass the proper flags to include c++11 support
COMPILERFLAGS = -O3 -std=c++11 $(INCLUDE)
# initialize the output program variable
PROGRAM = current





# lets define our cc-compile command to prevent repetitiveness 
define cc-command
	
	$(CC) $(COMPILERFLAGS) $< -o $@
	
endef


# declare the classes build command!
$(BUILDDIR)%.o: %.cpp
	$(cc-command) 	

# a simple test for the vpath -- working now!
test.o: classes/test.cpp
	g++ -c $^ -o $@

# compile the modules into our main function
all: test.o
	$(COMPILER) $(COMPILERFLAGS) -o $(PROGRAM) $(OBJECT) $(LIBRARIES)

# debug compiation -- takes slightly longer
debug: src/main.cpp 

	$(COMPILER) $(COMPILERFLAGS) -g -o $(PROGRAM) src/main.cpp src/modules/*.cpp $(LIBRARIES)

# clean up after ourselves
clean:
	-rm -rf *.o *~ .*~ $(PROGRAM)
	-rm -rf src/*.o src/*~
