#include"GameWindow.h"
using namespace Goat2d::core;

GameWindow::GameWindow(const GameWindowSetting& setting)
{
	print_error = setting._print_error;
	write_error = setting._write_error;

	if (SDL_Init(setting.SDL_subsystems) < 0)
	{
		if(print_error)::print_error("SDL could not initialize! SDL_Error:");
		if (write_error)::write_error("SDL could not initialize! SDL_Error:");
	}
	else
	{
		//Create window
		window = SDL_CreateWindow(setting.title.c_str(),
								  setting.win_pos.x, 
								  setting.win_pos.y,
								  setting.win_size.x,
								  setting.win_size.y,
								  SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			if(print_error)::print_error("failed to create window! SDL_Error:");
			if (write_error)::write_error("failed to create window! SDL_Error:");
		}
		else
		{
			///My little note on correct_init 
			///CppCheck says there are several problems connected to this variable,
			/// but we change it to false/true because there are several init functions calls
			/// so we if one doesn't work then everything else won't work too, so ignore
			/// this CppCheck's note.
			/// P.S. I think there can be some more elegant way to init all required 
			
			//set it to false if any subsystem is not loaded correctly
			bool correct_init = true;

	#ifdef USE_SDL_IMG
			//init img library
			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				if (print_error)::print_error("SDL_image could not initialize! SDL_image Error:");
				if (write_error)::write_error("SDL_image could not initialize! SDL_image Error:");

				correct_init = false;
			}
	#endif //USE_SDL_IMG

	#ifdef USE_SDL_TTF
			//init ttf library
			if (TTF_Init() == -1)
			{
				if (print_error)::print_error("SDL_ttf could not initialize! SDL_ttf Error:");
				if (write_error)::write_error("SDL_ttf could not initialize! SDL_ttf Error:");
				correct_init = false;
			}
	#endif //USE_SDL_TTF

			//init renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				if (print_error)::print_error("Renderer could not be created! SDL Error:");
				if (write_error)::write_error("Renderer could not be created! SDL Error:");
				correct_init = false;
			}

			if(correct_init)
			{				
				//Update the surface
				SDL_UpdateWindowSurface(window);

				ok = true;//everything worked fine
				add_quit_event();//create event to check should window be closed


				start = SDL_GetTicks();//used by frame rate limiter
				FPS = setting.FPS;
				background_color = setting.background_color;
			}
		}
	}
}
GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

#ifdef USE_SDL_TTF
	TTF_Quit();
#endif
#ifdef USE_SDL_IMG
	IMG_Quit();
#endif

	if (quit_event != nullptr)
		delete quit_event;
}
void GameWindow::run()
{
	//main game cycle

	//check and process keyboard events
	//process event of scene
	//draw and wait a bit to set FPS limit

	SDL_Event e;
	while (!quit)
	{
		if (should_change())
		{
			auto next_scene_id = get_next_id();
			if (!change_scene(next_scene_id))
			{
				std::cout << "can't change scene!";
			}
		}

		if (SDL_WaitEvent(&e) != 0)
		{
			quit_event->process(static_cast<void*>(&e));
			process_keyboard_events(e);
		}
		process_game_events();

		draw();
		wait();
	}
}
void GameWindow::add_quit_event()
{
	//default event to process quit button pressing

	auto pred = [](const SDL_Event& e) -> bool
	{
		//if user press X on window, then it's time to quit window
		return e.type == SDL_QUIT;
	};
	auto fn = [&](void* state) -> void
	{
		//if pred returns true, then we change quit variable's value to true
		if (state != ZERO_STATE)
		{
			bool* val = static_cast<bool*>(state);
			*val = true;
		}
	};

	//bind predicat, function and state together to get event
	quit_event = new framework::KeyboardEvent(pred, fn, static_cast<void*>(&this->quit));
}
void GameWindow::wait()
{
	//set fps framerate
	if (1000 / FPS > SDL_GetTicks() - start) 
	{
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}
}
void GameWindow::draw()
{
	SDL_SetRenderDrawColor(renderer, background_color.r,
									 background_color.g,
									 background_color.b,
									 background_color.a);
	SDL_RenderClear(renderer);
	draw_current_scene();
	SDL_RenderPresent(renderer);
}