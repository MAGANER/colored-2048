#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include"Scene.h"
#include<unordered_map>
namespace Goat2d
{
namespace framework
{
	/*
		This class is base for GameWindow, since game window
		only gets the scenes and then pass it to scene manager
		to get current scene to process/draw.
	*/
	class SceneManager
	{
		std::unordered_map<int, BaseScene*> scenes;
		int current_scene_id = -1;
	public:
		SceneManager(){}
		~SceneManager(){}

		void add_scene(BaseScene* scene);
		void set_start_scene_id(int id) { current_scene_id = id; }
	protected:
		void process_keyboard_events(SDL_Event& event);
		void process_game_events();

		void draw_current_scene();


		bool should_change();
		bool change_scene(int id_scene);
	};
};
};

#endif