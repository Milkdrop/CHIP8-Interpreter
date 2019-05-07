deps = CPU.cpp Display.cpp Sound.cpp main.cpp
main: $(deps)
	g++ -O2 $(deps) -o main -lSDL2 -lSDL2_image

