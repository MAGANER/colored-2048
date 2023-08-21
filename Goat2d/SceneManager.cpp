#include"SceneManager.h"
using namespace Goat2d::framework;


void SceneManager::add_scene(BaseScene* scene)
{
	scenes[scene->get_id()] = scene;
}
bool SceneManager::should_change()
{
	return scenes[current_scene_id]->change();
}
void SceneManager::draw_current_scene()
{
	if(current_scene_id != -1)
		scenes[current_scene_id]->render();
}
bool SceneManager::change_scene(int id_scene)
{
	if (scenes.find(id_scene) != scenes.end())
	{
		current_scene_id = id_scene;
		return true;
	}

	//can't change to scene with such id
	return false;
}
void SceneManager::process_keyboard_events(SDL_Event& event)
{
	if (current_scene_id != -1)
	scenes[current_scene_id]->process_keyboard_events(event);
}
void SceneManager::process_game_events()
{
	if (current_scene_id != -1)
		scenes[current_scene_id]->process_game_events();
}