IFLAGS = -I./headers/

all: a object/main.o object/utils.o

a: object/main.o object/utils.o
	g++ object/main.o object/utils.o  -g

object/main.o: src/main.cpp
	g++ $(IFLAGS) $(CFLAGS) -c src/main.cpp -o object/main.o -g

object/utils.o: src/utils.cpp
	g++ $(IFLAGS) $(CFLAGS) -c src/utils.cpp -o object/utils.o -g 