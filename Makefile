.PHONY: all
all: bonfire_nes.exe

bonfire_nes.exe: main.o
	clang++ main.o -o bonfire_nes.exe

main.o: main.cpp
	clang++ -c main.cpp -o main.o

.PHONY: run
run:
	./bonfire_nes.exe