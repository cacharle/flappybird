#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"

#define WINDOW_TITLE "Title"
#define WINDOW_X 20
#define WINDOW_Y 20

Graphics::Graphics()
{
	window = NULL;
	renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_quit("init");
	window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, 640, 480, 0);
	if (window == NULL)
		error_quit("window init");
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
		error_quit("renderer init");
	running = true;
}

void Graphics::run()
{
	while (running)
	{
		event_handler();
		// update(state);
		SDL_Delay(10);
	}
}

Graphics::~Graphics()
{
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if (window != NULL)
		SDL_DestroyWindow(window);
	if (SDL_WasInit(SDL_INIT_VIDEO))
		SDL_Quit();
}

void Graphics::event_handler()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
		switch (e.type)
		{
			case SDL_QUIT:
				running = false;
				break;
		}
}

void Graphics::error_quit(std::string msg)
{
	// ~Graphics();
	std::cerr << "ERROR: " << msg << std::endl;
	exit(1);
}
