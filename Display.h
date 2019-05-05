#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdio.h>
#include<string>

class Display
{
public:
	Display();
	~Display();
	void create(std::string _name, int _width, int _height);
	void update();
	SDL_Renderer* getRenderer();
private:
	SDL_Window* main_window;
	SDL_Renderer* main_renderer;
};

