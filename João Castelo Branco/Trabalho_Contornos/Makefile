GL=/usr/include/GL/
LIBS        = -O2 -L -lm -lpthread -lX11 -lGL -lGLU -lGLEW -lglut -Wno-write-strings
LFLAGS  = $(GL) -O2 -L -lm -lpthread -lX11 -lGL -lGLU -lGLEW -lglut -Wno-write-strings
all: Main.o Main


Main.o: Main.cpp $(GL)glew.h $(GL)glut.h $(GL)freeglut.h 
	g++ -c -g Main.cpp 

Main:   Main.o 
	g++ -o Main Main.o $(LIBS)

	
clean: 
	rm *.o
	rm Main
