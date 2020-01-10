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
	r_ = { renderer_ };
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
				case SDLK_1: o.scale_from_origin(2, 2, 2); break;
				case SDLK_2: o.translate(2, 2, 2); break;
				case SDLK_3: o.scale_from_point(2, 2, 2); break;
				case SDLK_4: o.scale_from_point(0.5, 0.5, 0.5); break;
				}
			}
		}
		r_.render(o,false,false,false);
		
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

	auto p1 = std::make_shared<point>(point{{50,100,250}});
	
	auto p2 = std::make_shared<point>(point{ {50,100,300} });
	
	auto p3 = std::make_shared<point>(point{ {250,0,200} });
	auto p4 = std::make_shared<point>(point{ {250,0,350} });
	auto p5 = std::make_shared<point>(point{ {300,0,50} });
	auto p6 = std::make_shared<point>(point{ {300,0,500} });
	auto p7 = std::make_shared<point>(point{ {350,0,50} });
	auto p8 = std::make_shared<point>(point{ {350,0,500} });
	auto p9 = std::make_shared<point>(point{ {370,0,170} });
	auto p10 = std::make_shared<point>(point{ {370,0,190} });
	auto p11 = std::make_shared<point>(point{ {430,0,170} });
	auto p12 = std::make_shared<point>(point{ {430,0,190} });
	auto p13 = std::make_shared<point>(point{ {380,0,210} });
	auto p14 = std::make_shared<point>(point{ {400,0,250} });
	auto p15 = std::make_shared<point>(point{ {400,0,300} });
	auto p16 = std::make_shared<point>(point{ {380,0,340} });
	auto p17 = std::make_shared<point>(point{ {370,0,360} });
	auto p18 = std::make_shared<point>(point{ {370,0,380} });
	auto p19 = std::make_shared<point>(point{ {430,0,360} });
	auto p20 = std::make_shared<point>(point{ {430,0,380} });

	p1->link(p2);
	p1->link(p3);	
	p2->link(p4);
	p3->link(p5);
	p4->link(p6);
	p5->link(p7);
	p6->link(p8);
	p7->link(p9);
	p8->link(p18);
	p9->link(p11);
	p9->link(p10);
	p10->link(p12);
	p11->link(p12);
	p13->link(p10);
	p13->link(p14);
	p14->link(p15);
	p15->link(p16);
	p16->link(p17);
	p17->link(p19);
	p17->link(p18);
	p18->link(p20);
	p19->link(p20);
	auto p = std::make_shared<plane>();
	p->add_points(std::vector<std::shared_ptr<point>>{
		p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20
	});
	o.add_plane(p);
	this->o = o;
	objects_.emplace_back(o);
}
