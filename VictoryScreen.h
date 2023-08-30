#ifndef VICTORY_SCREEN_H
#define VICTORY_SCREEN_H
#include"Goat2d/Scene.h"
#include<vector>

class VictoryScreen :public Goat2d::framework::BaseScene
{
	Goat2d::core::Font* big_font = nullptr, * small_font;
	Goat2d::core::Text* label = nullptr, *gz=nullptr;

	std::vector<Goat2d::core::Text*>  press_start;

	void generate_press_start();
	void create_event_to_start_playing();
public:
	VictoryScreen(int id,
				SDL_Renderer* renderer,
				std::unordered_map<int, Goat2d::core::Font*>& fonts);

	~VictoryScreen();
	void render() override;
};
#endif