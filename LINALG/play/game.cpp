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
	make_ship_object();
	cam.set_lookat(ship_.get_middle_point().vector);
	SDL_Event e;
	bool quit = false;

	bool cam_up = false;
	bool cam_down = false;
	bool cam_z_p = false;
	bool cam_x_p = false;
	bool cam_z_n = false;
	bool cam_x_n = false;
	bool ship_speed_up = false;
	bool ship_slow_down = false;
	bool guide_line = false;

	bool game_over = false;
	bool won_game = false;
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
				vec3d d{};
				switch (e.key.keysym.sym)
				{
				case SDLK_w: ship_speed_up = true; break;
				case SDLK_a: d = ship_.get_right(); ship_.move_object(d); break;
				case SDLK_s: ship_slow_down = true; break;
				case SDLK_d: d = ship_.get_right(); d *= -1; ship_.move_object(d); break;
				case SDLK_LSHIFT: d = ship_.get_up(); d *= -1; ship_.move_object(d); break;
				case SDLK_LCTRL: d = ship_.get_up(); ship_.move_object(d); break;
				case SDLK_PAGEUP: cam_up = true;  break;
				case SDLK_PAGEDOWN: cam_down = true;  break;
				case SDLK_UP: cam_x_n = true;  break;
				case SDLK_LEFT: cam_z_n = true;  break;
				case SDLK_DOWN: cam_x_p = true;  break;
				case SDLK_RIGHT: cam_z_p = true;  break;
				case SDLK_i: ship_.pitch(10); break;
				case SDLK_k: ship_.pitch(-10); break;
				case SDLK_j: ship_.roll(10); break;
				case SDLK_l: ship_.roll(-10); break;
				case SDLK_COMMA: ship_.yaw(10); break;
				case SDLK_PERIOD: ship_.yaw(-10); break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				vec3d d{};
				switch (e.key.keysym.sym)
				{
				case SDLK_w: ship_speed_up = false; break;
				case SDLK_a: d = ship_.get_right(); ship_.move_object(d); break;
				case SDLK_s: ship_slow_down = false; break;
				case SDLK_d: d = ship_.get_right(); d *= -1; ship_.move_object(d); break;
				case SDLK_LSHIFT: d = ship_.get_up(); d *= -1; ship_.move_object(d); break;
				case SDLK_LCTRL: d = ship_.get_up(); ship_.move_object(d); break;
				case SDLK_PAGEUP: cam_up = false;  break;
				case SDLK_PAGEDOWN: cam_down = false;  break;
				case SDLK_UP: cam_x_n = false;  break;
				case SDLK_LEFT: cam_z_n = false;  break;
				case SDLK_DOWN: cam_x_p = false;  break;
				case SDLK_RIGHT: cam_z_p = false;  break;
				case SDLK_SPACE: shoot(); break;
				case SDLK_g: guide_line = !guide_line; break;
				}
			}
		}
		if (cam_up) { cam.moveY(5); }
		if (cam_down) { cam.moveY(-5); }
		if (cam_x_p) { cam.moveX(5); }
		if (cam_x_n) { cam.moveX(-5); }
		if (cam_z_p) { cam.moveZ(5); }
		if (cam_z_n) { cam.moveZ(-5); }
		if (ship_speed_up) { ship_.speed_up(); }
		if (ship_slow_down) { ship_.slow_down(); }
		for (auto& b : bullets)
		{
			b->update();
			if (cube_.collision_check(*b.get()))
			{
				quit = true; won_game = true; game_over = true;
			}
		}
		if (cube_.collision_check(ship_))
		{
			quit = true; won_game = false; game_over = true;
		}
		std::vector<object> o_s;
		o_s = objects_;
		if (guide_line) {
			auto gl = ship_.give_guide_line();
			o_s.emplace_back(*gl.get());
		}
		auto render_obj = cam.update(ship_, o_s);
		for (auto obj : render_obj)
		{
			r_.render(obj);
		}
		cube_.update();
		ship_.update();
		SDL_RenderPresent(renderer_);
		SDL_Delay(1000 / 30);
	}
	if (game_over) {
		if (won_game) {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Goed gedaan!",
				"Je hebt de kwade planeet verslagen! Goed zo!",
				window_);
		}
		else {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
				"Oeps!",
				"Je bent tegen de planeet aangebotst en hebt verloren!",
				window_);
		}
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

void Game::make_ship_object()
{
	ship o{};
	auto point_front = std::make_shared<point>(point{ {50,100,300} });
	auto point_back = std::make_shared<point>(point{ {250,100,300} });

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
		point_front,
			point_back,
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

	this->ship_ = o;
	ship_.set_front(point_front);
	ship_.set_back(point_back);
	ship_.set_position(ship_.get_middle_point().vector);
	objects_.emplace_back(o);

	cube cube{};
	auto top_left = std::make_shared<point>(point{ {1000,100,1000} });
	auto top_right = std::make_shared<point>(point{ {1100,100,1000} });
	auto top_front_left = std::make_shared<point>(point{ {1000,100,1100} });
	auto top_front_right = std::make_shared<point>(point{ {1100,100,1100} });
	auto bottom_left = std::make_shared<point>(point{ {1000,0,1000} });
	auto bottom_right = std::make_shared<point>(point{ {1100,0,1000} });
	auto bottom_front_left = std::make_shared<point>(point{ {1000,0,1100} });
	auto bottom_front_right = std::make_shared<point>(point{ {1100,0,1100} });
	cube.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		bottom_left,
			bottom_right,
			top_right,
			top_left
	}) });
	cube.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		top_left,
			top_right,
			top_front_right,
			top_front_left
	}) });
	cube.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		top_left,
			top_front_left,
			bottom_front_left,
			bottom_left
	}) });
	cube.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		bottom_left,
			bottom_right,
			bottom_front_right,
			bottom_front_left
	}) });
	cube.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		top_right,
			top_front_right,
			bottom_front_right,
			bottom_right
	}) });
	cube.add_plane({ std::make_shared<plane>(
		std::vector<std::shared_ptr<point>>{
		top_front_left,
			top_front_right,
			bottom_front_right,
			bottom_front_left
	}) });
	cube.link_planes();
	cube_ = cube;
	objects_.emplace_back(cube);
}

void Game::shoot()
{
	auto b = std::shared_ptr<bullet>(ship_.shoot());
	objects_.emplace_back(*b.get());
	bullets.emplace_back(b);
}
