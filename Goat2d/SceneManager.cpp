#include"SceneManager.h"
using namespace Goat2d::framework;


void SceneManager::add_scene(int id, const gen_scene_fn& generator)
{
	scenes[id] = generator;
}
bool SceneManager::should_change()
{
	return current_scene->change();
}
void SceneManager::draw_current_scene()
{
	if(current_scene_id != -1)
		current_scene->render();
}
bool SceneManager::change_scene(int id_scene)
{
	if (scenes.find(id_scene) != scenes.end())
	{
		void* ret_val = const_cast<void*>(current_scene->get_return_value());
		delete current_scene;
		current_scene = scenes[id_scene](ret_val);
		current_scene_id = id_scene;
		return true;
	}

	//can't change to scene with such id
	return false;
}
void SceneManager::process_keyboard_events(SDL_Event& event)
{
	if (current_scene_id != -1)
		current_scene->process_keyboard_events(event);
}
void SceneManager::process_game_events()
{
	if (current_scene_id != -1)
		current_scene->process_game_events();
}