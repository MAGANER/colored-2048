#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include"Scene.h"
#include<unordered_map>
namespace Goat2d
{
namespace framework
{
	typedef std::function<BaseScene* (void* prev_scene_ret_val)> gen_scene_fn;

	/*
		This class is base for GameWindow, since game window
		only gets the scenes and then pass it to scene manager
		to get current scene to process/draw.
	*/
	class SceneManager
	{
		std::unordered_map<int, gen_scene_fn> scenes;
		int current_scene_id = -1;

		BaseScene* current_scene = nullptr;
	public:
		SceneManager(){}
		~SceneManager(){}

		void add_scene(int id,const gen_scene_fn& generator);
		void set_start_scene_id(int id) 
		{ 
			current_scene_id = id; 
			current_scene = scenes[id](ZERO_STATE);//create start scene
		}
	protected:
		void process_keyboard_events(SDL_Event& event);
		void process_game_events();

		void draw_current_scene();

		int get_next_id() { return current_scene->get_next_id(); }
		bool should_change();
		bool change_scene(int id_scene);
	};
};
};

#endif