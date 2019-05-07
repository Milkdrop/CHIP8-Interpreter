#include "Display.h"

Display::Display() {
}

Display::~Display() {
}

void Display::create(std::string _name, int _width, int _height) {
	bool success = 1;
	main_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
	if (main_window == NULL) {
		success = 0;
		fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
	} else {
		//Create renderer for window
		main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
		if (main_renderer == NULL) {
			fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Initialize renderer color
			SDL_SetRenderDrawColor(main_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
		}
	}

	if (!success) {
		fprintf(stderr, "Display was not created correctly! %s\n", SDL_GetError());
	}
}

void Display::update(short int screen[32][64], int width, int height, int PixelSize) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			SDL_Rect rct = { x * PixelSize, y * PixelSize, PixelSize, PixelSize};
			if (screen[y][x] == 0)
				SDL_SetRenderDrawColor(main_renderer, 0x00, 0x00, 0x00, 0x00);
			else
				SDL_SetRenderDrawColor(main_renderer, 0xff, 0xff, 0xff, 0xff);
			
			SDL_RenderFillRect(main_renderer, &rct);
		}
	}
	SDL_RenderPresent(main_renderer);
}

SDL_Renderer* Display::getRenderer()
{
	return main_renderer;
}

