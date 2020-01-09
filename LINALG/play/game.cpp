#include "game.h"
#include <iostream>

bool Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Unable to initialize SDL" << std::endl;
		return false;
	}
	if ((window_ = SDL_CreateWindow("Linalg", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, k_screen_width, k_screen_height, SDL_WINDOW_OPENGL)) == nullptr)
	{
		std::cout << "Unable to initialize Window" << std::endl;
		return false;
	}
	if ((renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
	{
		std::cout << "Unable to initialize renderer_" << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
	init_vectors();
	make_object();

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer_);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_1: o.scale_from_origin(2, 2); break;
				case SDLK_2: o.translate(2, 2); break;
				case SDLK_3: o.scale_from_point(2, 2); break;
				case SDLK_4: o.scale_from_point(0.5, 0.5); break;
				case SDLK_5: o.rotate_origin(0.5 * M_PI); break;
				}
			}
		}
		draw_grid();

		for (auto item : vectors_)
		{
			item.render(renderer_, k_screen_width, k_screen_height);
		}
		o.render(renderer_);


		SDL_RenderPresent(renderer_);
		SDL_Delay(1000 / 30);
	}
	if (renderer_ != nullptr) {
		SDL_DestroyRenderer(renderer_);
	}
	if (window_ != nullptr) {
		SDL_DestroyWindow(window_);
	}
	return true;
}

void Game::draw_grid()
{
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer_, 0, k_screen_height / 2, k_screen_width, k_screen_height / 2);
	SDL_RenderDrawLine(renderer_, k_screen_width / 2, 0, k_screen_width / 2, k_screen_height);
	for (int i = 10; i < k_screen_height; i += 10)
	{
		SDL_RenderDrawLine(renderer_, k_screen_width / 2 - 5, i, k_screen_width / 2 + 5, i);
	}
	for (int i = 10; i < k_screen_width; i += 10)
	{
		SDL_RenderDrawLine(renderer_, i, k_screen_height / 2 - 5, i, k_screen_height / 2 + 5);
	}
}

void Game::init_vectors()
{
	vectors_.emplace_back(vector{
		30,
		60,
		0
		});
	vectors_.emplace_back(vector{
		-20,
		30,
		0
		});
}

void Game::make_object()
{
	auto p1 = std::make_shared<point>(point{
		10,
		10,
		0,
		k_screen_width,
		k_screen_height
		});
	auto p2 = std::make_shared<point>(point{
		10,
		200,
		0,
		k_screen_width,
		k_screen_height
		});
	auto p3 = std::make_shared<point>(point{
		30,
		200,
		0,
		k_screen_width,
		k_screen_height
		});
	auto p4 = std::make_shared<point>(point{
		30,
		30,
		0,
		k_screen_width,
		k_screen_height
		});
	auto p5 = std::make_shared<point>(point{
		150,
		30,
		0,
		k_screen_width,
		k_screen_height
		});
	auto p6 = std::make_shared<point>(point{
		150,
		10,
		0,
		k_screen_width,
		k_screen_height
		});
	p1->connections.emplace_back(p2);
	p1->connections.emplace_back(p6);
	p2->connections.emplace_back(p1);
	p2->connections.emplace_back(p3);
	p3->connections.emplace_back(p2);
	p3->connections.emplace_back(p4);
	p4->connections.emplace_back(p3);
	p4->connections.emplace_back(p5);
	p5->connections.emplace_back(p4);
	p5->connections.emplace_back(p6);
	p6->connections.emplace_back(p5);
	p6->connections.emplace_back(p1);
	o.add_point(p1);
	o.add_point(p2);
	o.add_point(p3);
	o.add_point(p4);
	o.add_point(p5);
	o.add_point(p6);
}
