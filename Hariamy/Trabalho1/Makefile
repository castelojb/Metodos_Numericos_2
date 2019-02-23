SRC = src/
HEAD = header/

all: ExibeMenu.o programa
ExibeMenu.o: $(SRC)ExibeMenu.cpp $(HEAD)ExibeMenu.h 
	g++ -w -g -c $(SRC)ExibeMenu.cpp

main.o: $(SRC)main.cpp $(HEAD)ExibeMenu.h 
	g++ -w -g -c $(SRC)main.cpp
	
programa: main.o ExibeMenu.o
	g++ ExibeMenu.o main.o -o programa -O2 -L -lm -lpthread -lX11 -lGL -lGLU -lGLEW -lglut -Wno-write-strings
	
clean: 
	rm *.o
	rm programa