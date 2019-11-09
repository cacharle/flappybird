#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <string>
#include <SDL2/SDL.h>

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

	void event_handler();
	void error_quit(std::string msg);
};

#endif
