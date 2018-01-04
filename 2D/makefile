CPPFLAGS=-O2 -Wall -std=c++11
LDFLAGS= -fopenmp
LIBS =

all: main.o mcmc.o
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) -o Sim main.o mcmc.o

main.o: src/main.cpp src/mcmc.hpp
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) -c src/main.cpp

mcmc.o: src/mcmc.cpp src/mcmc.hpp
	g++ $(CPPFLAGS) $(LDFLAGS) $(LIBS) -c src/mcmc.cpp

clean:
	rm -f *.o
