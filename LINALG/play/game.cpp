#include "game.h"
#include <iostream>
#include "camera.h"

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
	r_ = { renderer_ };
	camera cam = { 90 };
	
	init_vectors();
	make_object();
	
	SDL_Event e;
	bool quit = false;

	bool render_top = false;
	bool render_front = false;
	bool render_side = false;
	while (!quit)
	{
		float move_x{ 0 }, move_y{ 0 }, move_z{ 0 }, pitch_x{0}, pitch_y{0};
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
				case SDLK_1: o.scale_from_origin(2, 2, 2); break;
				case SDLK_2: o.translate(2, 2, 2); break;
				case SDLK_3: o.scale_from_point(2, 2, 2); break;
				case SDLK_4: o.scale_from_point(0.5, 0.5, 0.5); break;
				case SDLK_5: render_top = !render_top; break;
				case SDLK_6: render_front = !render_front; break;
				case SDLK_7: render_side = !render_side; break;
				case SDLK_w: move_z += 1000; break;
				case SDLK_a: move_x -= 1000; break;
				case SDLK_s: move_z -= 1000; break;
				case SDLK_d: move_x += 1000; break;
				case SDLK_LSHIFT: move_y += 50; break;
				case SDLK_LCTRL: move_y -= 50; break;
				case SDLK_UP: pitch_y += 50; break;
				case SDLK_LEFT: pitch_x -= 50; break;
				case SDLK_RIGHT: pitch_x += 50; break;
				case SDLK_DOWN: pitch_y -= 50; break;
				}
			}
		}
		if (render_top)
			r_.render_top(o);
		if (render_front)
			r_.render_front(o);
		if (render_side)
			r_.render_side(o);
		auto render_points = cam.update(o, move_x, move_y, move_z, pitch_x, pitch_y);
		r_.render(render_points);
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

void Game::init_vectors()
{
	vectors_.emplace_back(vec3d{
		30,
		60,
		0
		});
	vectors_.emplace_back(vec3d{
		-20,
		30,
		0
		});
}

void Game::make_object()
{
	object o{};
	//Nose front
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {50,100,300} }),
			std::make_shared<point>(point{ {50,100,350} }),
						std::make_shared<point>(point{ {50,50,350} }),
			std::make_shared<point>(point{ {50,50,300} })

	}) });
	//Nose back
	o.add_plane({ std::make_shared<plane>(
	std::vector<std::shared_ptr<point>>{
	std::make_shared<point>(point{ {250,100,300} }),
		std::make_shared<point>(point{ {250,100,350} }),
					std::make_shared<point>(point{ {250,50,350} }),
		std::make_shared<point>(point{ {250,50,300} })

}) });
	//Nose top
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {50,100,300} }),
			std::make_shared<point>(point{ {250,100,300} }),
			std::make_shared<point>(point{ {250,100,350} }),
			std::make_shared<point>(point{ {50,100,350} })
	}) });
	//Nose bottom
	o.add_plane({ std::make_shared<plane>(
	std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {50,50,300} }),
			std::make_shared<point>(point{ {250,50,300} }),
			std::make_shared<point>(point{ {250,50,350} }),
			std::make_shared<point>(point{ {50,50,350} })
	}) });
	//Nose right
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {50,100,350} }),
						std::make_shared<point>(point{ {250,100,350} }),
			std::make_shared<point>(point{ {250,50,350} }),
			std::make_shared<point>(point{ {50,50,350} })

	}) });
	//Nose left
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {50,100,300} }),
			std::make_shared<point>(point{ {250,100,300} }),
						std::make_shared<point>(point{ {250,50,300} }),
			std::make_shared<point>(point{ {50,50,300} })

	}) });
	//Wing left
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {75,100,300} }),
			std::make_shared<point>(point{ {150,100,300} }),
			std::make_shared<point>(point{ {150,130,200} }),
			std::make_shared<point>(point{ {75,130,200} })
	}) });
	//Wing right
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {75,100,350} }),
			std::make_shared<point>(point{ {150,100,350} }),
			std::make_shared<point>(point{ {150,130,450} }),
			std::make_shared<point>(point{ {75,130,450} })
	}) });
	//Engine left
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {125,110,280} }),
			std::make_shared<point>(point{ {200,110,280} }),
			std::make_shared<point>(point{ {200,90,280} }),
			std::make_shared<point>(point{ {125,90,280} })
	}) });
	//Engine right
	o.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		std::make_shared<point>(point{ {125,110,370} }),
			std::make_shared<point>(point{ {200,110,370} }),
			std::make_shared<point>(point{ {200,90,370} }),
			std::make_shared<point>(point{ {125,90,370} })
	}) });
	o.link_planes();

	this->o = o;
	objects_.emplace_back(o);
}
