deps = CPU.cpp Display.cpp Sound.cpp main.cpp
main: $(deps)
	g++ -Wall -O2 $(deps) -o main -lSDL2

