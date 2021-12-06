#	Set all object files (pretty much all .cpp)
OBJ = src/main.cpp src/input.cpp src/in_joystick.cpp src/scripting.cpp

#	Set any dependencies
#DEPS = main.h

#	Any special libraries
LIBS = -pthread -lX11 -lGL -lGLU -lglut -g -Wall

#	Set any compiler flags
CFLAGS = -I/usr/include/python3.9 -I/usr/include/python3.9 -lpython3.9 -fPIE -Wno-unused-result -Wsign-compare -g -ffile-prefix-map=/build/python3.9-RNBry6/python3.9-3.9.2=. -specs=/usr/share/dpkg/no-pie-compile.specs -fstack-protector -Wformat -Werror=format-security -DNDEBUG -g -fwrapv -O3 -Wall -L/usr/lib/python3.9/config-3.9-x86_64-linux-gnu -L/usr/lib  -lcrypt -lpthread -ldl  -lutil -lm -lm 

CC = g++

#	Set the filename extension
EXTENSION = .cpp

#define a rule that applies to all files ending in the .o suffix, which says that the .o file depends upon the .c version of the file and all the .h files included in the DEPS macro.  Compile each object file
%.o: %$(EXTENSION) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#Combine them into the output file
#Set your desired exe output file name here
spacerailer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

#Cleanup
.PHONY: clean

clean:
	rm -f *.o *~ core *~ 
