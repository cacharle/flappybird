#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <string>
#include <deque>
#include <SDL2/SDL.h>

typedef std::pair<SDL_Rect, SDL_Rect> PipePair;

class Graphics
{
	public:
	Graphics();
	void run();
	~Graphics();

	private:
	SDL_Renderer *renderer;
	SDL_Window *window;
	bool running;
	SDL_Rect bird;
	std::deque<SDL_Rect> pipes;

	void update();
	void draw_bird();
	void draw_pipes();
	bool is_gameover();
	void handle_pipes();
	PipePair generate_pipe_pair();
	void event_handler();
	void error_quit(std::string msg);
};

#endif
