#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include"Goat2d/Scene.h"
#include<vector>
#include<random>
using namespace Goat2d::core;

class MainMenu : public Goat2d::framework::BaseScene
{
private:
	std::unordered_map<int, Goat2d::core::Font*> fonts;


	//label text
	std::vector<Text*> colored; //vector contains each character filled with different color
	Text *_2048          = nullptr, 	
		 *classic        = nullptr, 
		 *middle         = nullptr,
		 *is_it_playable = nullptr,
		 *press          = nullptr,
		 *start          = nullptr,
		 *to_play        = nullptr;
	

	enum class complexity_level:unsigned short
	{
		classic,
		middle,
		is_it_playable
	};
	complexity_level level = complexity_level::classic;
public:
	MainMenu(int id, SDL_Renderer* renderer, const std::unordered_map<int, Goat2d::core::Font*>& fonts);
	~MainMenu();

	void render() override;
private:
	void generate_title();
	void generate_press_start_title();

	unsigned short get_random_number();
	Color get_random_color();
	void update_current_level_color();

	void add_event_to_check_movement_down();
	void add_event_to_check_movement_up();
	void add_event_to_start_game();
};

#endif