CC=g++
DEPS=./include/main.hpp
CFLAGS=-I./include -I/opt/homebrew/opt/cairo/include/cairo -L/opt/homebrew/Cellar/cairo/1.16.0_5/lib -lcairo -std=c++11

bin/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

debug: bin/main.o
	$(CC) -o bin/caSim bin/main.o $(CFLAGS)