CC=g++
DEPS=./include/main.hpp
CFLAGS=-I./include -I/opt/homebrew/opt/cairo/include/cairo -L/opt/homebrew/Cellar/cairo/1.16.0_5/lib -lcairo -std=c++11

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

debug: main.o
	$(CC) -o caSim main.o $(CFLAGS)