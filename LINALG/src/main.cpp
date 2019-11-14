#include <iostream>
#include "SDL.h"
SDL_Window* window;
SDL_Renderer* renderer;
int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Unable to initialize SDL" << std::endl;
		return false;
	}
	if ((window = SDL_CreateWindow("Linalg", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL)) == nullptr)
	{
		std::cout << "Unable to initialize Window" << std::endl;
		return false;
	}
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
	{
		std::cout << "Unable to initialize renderer" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	
	SDL_Event e;
	while(true)
	{
		
		while(SDL_PollEvent(&e) != 0)
		{
			
		}
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);
	}
	return 0;
}
