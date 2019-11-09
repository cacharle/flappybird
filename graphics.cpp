#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include "graphics.hpp"

#define WINDOW_TITLE "Title"
#define WINDOW_X 20
#define WINDOW_Y 20

#define BIRD_H 20
#define BIRD_W 20
#define BIRD_FALL 1
#define BIRD_JUMP 30

#define PIPE_W 30

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
	for (int i = 0; i < 640 + 100; i += 50)
	{
		PipePair ppair = generate_pipe_pair();
		ppair.first.x = i;
		ppair.second.x = i;
		pipes.push_back(ppair.first);
		pipes.push_back(ppair.second);
	}
	bird.h = BIRD_H;
	bird.w = BIRD_W;
	bird.x = 0;
	bird.y = pipes.front().h + 10;
}

void Graphics::run()
{
	while (running)
	{
		SDL_Delay(10);
		event_handler();
		update();
		if (is_gameover())
			running = false;
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

void Graphics::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	handle_pipes();
	draw_pipes();
	draw_bird();
	bird.y += BIRD_FALL;
	for (std::deque<SDL_Rect>::iterator it = pipes.begin(); it != pipes.end(); it++)
		it->x -= 1;
	SDL_RenderPresent(renderer);
}

void Graphics::draw_bird()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &bird);
}

void Graphics::draw_pipes()
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	for (SDL_Rect p : pipes)
		SDL_RenderFillRect(renderer, &p);
}

bool Graphics::is_gameover()
{
	for (SDL_Rect p : pipes)
		if (SDL_HasIntersection(&p, &bird) == SDL_TRUE)
			return true;
	if (bird.y + bird.w >= 480)
		return true;
	return false;
}

void Graphics::handle_pipes()
{
	if (pipes.front().x + pipes.front().w > 0)
		return ;
	pipes.pop_front();
	pipes.pop_front();
	PipePair pipe_pair = generate_pipe_pair();
	pipes.push_back(pipe_pair.first);
	pipes.push_back(pipe_pair.second);
}

#define PIPE_GAP 250

PipePair Graphics::generate_pipe_pair()
{
	PipePair ppair;

	ppair.first.h = rand() % 150 + 140;
	ppair.second.y = ppair.first.h + PIPE_GAP;

	ppair.first.x = 610;
	ppair.first.y = 0;
	ppair.first.w = PIPE_W;
	ppair.second.x = 610;
	ppair.second.w = PIPE_W;
	ppair.second.h = 480 - ppair.second.y;
	return ppair;
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
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
					case SDLK_SPACE:
						if (bird.y + bird.h > 0)
							bird.y -= BIRD_JUMP;
						break;
				}
				break;
		}
}

void Graphics::error_quit(std::string msg)
{
	// ~Graphics();
	std::cerr << "ERROR: " << msg << std::endl;
	exit(1);
}
