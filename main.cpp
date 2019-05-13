#include <stdio.h>
#include <SDL2/SDL.h>
#include "Display.h"
#include "CPU.h"
#include "Sound.h"
#include <time.h>

int main(int argc, char** argv) {
	if (argc <= 1) {
		printf("Please also provide the rom file to run!\n");
		printf("%s", argv[0]);
		printf(" ROM.ch8\n");
		return 0;
	}

	if (SDL_Init (SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "SDL failed to initialize: %s", SDL_GetError());
		return 1;
	}
	
	CPU* cpu = new CPU;
	Display* disp = new Display("CHIP8", 640, 320);
	Sound snd;
	
	SDL_Event ev;
	bool quit = 0;

	printf("Trying to open file %s...\n", argv[1]);
	FILE* fin = fopen(argv[1], "rb");
	if (fin == NULL) {
		printf("Error opening file %s\n", argv[1]);
		return 1;
	}
	unsigned char buff[8192];
	int ROMSize = fread(buff, 1, 8192, fin);
	fclose(fin);

	if (ROMSize == 0) {
		printf("Couldn't Open ROM File: %s\n", argv[1]);
		return 0;
	}

	cpu->LoadInMemory(0x200, buff, ROMSize);

	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);

	unsigned long lastdraw = 0;

	while (!quit) {
		short int PressedKey = -1;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				quit = 1;
			}
		}

		if (keyboard[SDL_SCANCODE_0])
			PressedKey = 0;
		else if (keyboard[SDL_SCANCODE_1])
			PressedKey = 1;
		else if (keyboard[SDL_SCANCODE_2])
			PressedKey = 2;
		else if (keyboard[SDL_SCANCODE_3])
			PressedKey = 3;
		else if (keyboard[SDL_SCANCODE_4])
			PressedKey = 4;
		else if (keyboard[SDL_SCANCODE_5])
			PressedKey = 5;
		else if (keyboard[SDL_SCANCODE_6])
			PressedKey = 6;
		else if (keyboard[SDL_SCANCODE_7])
			PressedKey = 7;
		else if (keyboard[SDL_SCANCODE_8])
			PressedKey = 8;
		else if (keyboard[SDL_SCANCODE_9])
			PressedKey = 9;
		else if (keyboard[SDL_SCANCODE_A])
			PressedKey = 0xA;
		else if (keyboard[SDL_SCANCODE_B])
			PressedKey = 0xB;
		else if (keyboard[SDL_SCANCODE_C])
			PressedKey = 0xC;
		else if (keyboard[SDL_SCANCODE_D])
			PressedKey = 0xD;
		else if (keyboard[SDL_SCANCODE_E])
			PressedKey = 0xE;
		else if (keyboard[SDL_SCANCODE_F])
			PressedKey = 0xF;
		else if (keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL]) {
			if (keyboard[SDL_SCANCODE_R]) {
				free(cpu);
				cpu = new CPU;
				cpu->LoadInMemory(0x200, buff, ROMSize);
			}
		}

		cpu->Step(PressedKey);
		
		if (cpu->AudioData.PlaySquare) {
			snd.Play(1, 400, cpu->AudioData.PlaySquareDuration);
		}

		unsigned long currentclock = (unsigned long) clock();
		if (currentclock < lastdraw)
			lastdraw = 0;

		if ((currentclock - lastdraw) * 60 >= 1000000) {
			disp->update(cpu->screen, 64, 32, 10);
			lastdraw = currentclock;
		}
	}

	return 0;
}