#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include"SceneManager.h"
#include"SDL_ttf.h"
namespace Goat2d
{
namespace core
{
	/*
	* GameWindowSetting is structure that contains parameters,
	* that should be provided to GameWindow class to set its initial state
	*/
	struct GameWindowSetting
	{
		int SDL_subsystems; //SDL_INIT_VIDEO or SDL_INIT_VIDEO | SDL_INIT_AUDIO e.t.c
		std::string title;
		Color background_color;
		bool _print_error, _write_error;
		Vector2i win_pos, win_size;
		int FPS;

		GameWindowSetting():SDL_subsystems(SDL_INIT_VIDEO),
						    win_size(Vector2i(720,640)),
							title("Goat2d"),
							background_color(Color(0,0,0,255)),
							_print_error(true),
							_write_error(true),
							win_pos(Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)),
							FPS(30)
		{
			//create default game window settings
		}
		GameWindowSetting(const GameWindowSetting& setting):
						    SDL_subsystems(setting.SDL_subsystems),
						    win_size(setting.win_size),
							title(setting.title),
							background_color(setting.background_color),
							_print_error(setting._print_error),
							_write_error(setting._write_error),
							win_pos(setting.win_pos),
							FPS(setting.FPS)
		{
			//fully customized window setting by user based on another setting
		}
		GameWindowSetting(int SDL_subsystems,
						  const Vector2i& win_size):
						  title("Goat2d"),
						  SDL_subsystems(SDL_subsystems),
						  win_size(win_size),
						  background_color(Color(0, 0, 0, 255)),
						  _print_error(true),
						  _write_error(true),
						  win_pos(Vector2i(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)),
						  FPS(30)
		{
			//set only window size and required sdl subsystems
		}
		GameWindowSetting(int SDL_subsystems,
						  const Vector2i& win_size,
						  const Vector2i& win_pos,
						  const std::string& title,
						  const Color& background_color,
						  bool _print_error,
						  bool _write_error,
						  int FPS):
							SDL_subsystems(SDL_subsystems),
							win_size(win_size),
							title(title),
							background_color(background_color),
							_print_error(_print_error),
							_write_error(_write_error),
							win_pos(win_pos),
							FPS(FPS)
		{
			//fully customized setting by user
		}
		~GameWindowSetting(){}

	};

	/*
		GameWindow is class that is used to process game scene.
		So being derived from Scene manager it can add,change,process,draw .e.t.c
		each game scene.
		After the creation you should set scenes and check is everything ok to
		be sure the program won't crush.
	*/
	class GameWindow: public framework::SceneManager
	{
		//The window we'll be rendering to
		SDL_Window* window = nullptr;

		//The window renderer
		SDL_Renderer* renderer = nullptr;
		

		//clearing color
		Color background_color;

		bool ok = false; //if window is created sucessfully variable's value is true 
		bool quit = false; //set true to quit window
		
		bool print_error, write_error;//flags show should game window do this actions


		//special hard coded event : press X to close window
		framework::KeyboardEvent* quit_event = nullptr;

		Uint32  start; //time from starting SDL systems
		int  FPS;
	public:
		GameWindow(const GameWindowSetting& setting);
		~GameWindow();

		bool is_ok() const { return ok; }
		void run();

		SDL_Renderer* get_renderer() { return renderer; }//should be passed to the scene constructor
	private:
		void add_quit_event();
		void wait();

		void draw();
	};
};
};
#endif //GAME_WINDOW_H