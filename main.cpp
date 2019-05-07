#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Display.h"
#include "CPU.h"
#include <time.h>

bool Init();
void RenderScreen(Display *_disp, CPU *cpu);

int main(int argc, char** argv) {
	Init();
	CPU* cpu = new CPU;
	Display* disp = new Display;
	disp->create("CHIP8", 640, 320);
	SDL_Event ev;
	bool quit = 0;

	if (argc <= 1) {
		printf("Please also provide the rom file to run!\n");
		printf("%s", argv[0]);
		printf(" ROM.ch8\n");
		return 0;
	}

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

	double LastDraw = 0;
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

		double currentclock = clock() / (double) CLOCKS_PER_SEC;

		if (currentclock - LastDraw >= (double)1 / 60) {
			disp->update(cpu->screen, 64, 32, 10);
			LastDraw = currentclock;
		}
	}

	return 0;
}

bool Init() {
	bool success = 1;
	if (SDL_Init(SDL_INIT_EVERYTHING)<0) {
		success = 0;
		fprintf(stderr, "SDL failed to init! %s", SDL_GetError());
	}
	return success;
}

void RenderScreen(Display *_disp, CPU *cpu) {
	for (int y = 0; y < 32; y++) {
		for (int x = 0; x < 64; x++) {
			SDL_Rect rct = { x * 10, y * 10, 10, 10 };
			if (cpu->screen[y][x] == 1)
				SDL_SetRenderDrawColor(_disp->getRenderer(), 0xff, 0xff, 0xff, 0xff);
			else
				SDL_SetRenderDrawColor(_disp->getRenderer(), 0x00, 0x00, 0x00, 0x00);
			
			SDL_RenderFillRect(_disp->getRenderer(), &rct);
		}
	}
}