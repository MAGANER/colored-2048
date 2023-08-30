#include"Goat2d/GameWindow.h"
#include"MainMenu.h"
#include"Game.h"


bool load_fonts(std::unordered_map<int, Goat2d::core::Font*>& fonts);
int SDL_main(int argc, char* args[])
{
	Goat2d::core::GameWindowSetting setting(SDL_INIT_VIDEO, 
										    Goat2d::core::Vector2i(502, 502));
	setting.title = "2048";

	Goat2d::core::GameWindow window(setting);

	std::unordered_map<int, Goat2d::core::Font*> fonts;
	if (!load_fonts(fonts))
		return -1;


	auto generate_main_menu = [&](void* ret_val) -> Goat2d::framework::BaseScene*
	{
		return new MainMenu(0, window.get_renderer(), fonts);
	};
	window.add_scene(0,generate_main_menu);

	auto generate_game_scene = [&](void* ret_val) ->Goat2d::framework::BaseScene*
	{
		auto complexity = *static_cast<int*>(ret_val);
		return new Game(1, window.get_renderer(), fonts,complexity);
	};
	window.add_scene(1, generate_game_scene);

	window.set_start_scene_id(0);

	if (window.is_ok())
		window.run();
	else
		return -1;

	return 0;
}
bool load_fonts(std::unordered_map<int, Goat2d::core::Font*>& fonts)
{
	fonts[48] = new Goat2d::core::Font("font.ttf", 48);
	if (!fonts[48]->is_ok())
		return false;

	fonts[36] = new Goat2d::core::Font("font.ttf", 36);
	if (!fonts[36]->is_ok())
		return false;

	fonts[70] = new Goat2d::core::Font("font.ttf", 70);
	if (!fonts[70]->is_ok())
		return false;

	return true;
}