#ifndef DEATH_SCREEN_H
#define DEATH_SCREEN_H
#include"Goat2d/Scene.h"
#include<vector>
class DeathScreen :public Goat2d::framework::BaseScene
{
	int high_score;

	Goat2d::core::Font* big_font = nullptr, *small_font;
	Goat2d::core::Text* label = nullptr;

	std::vector<Goat2d::core::Text*> high_score_, press_start;

	void generate_high_score();
	void generate_press_start();
	
	void add_event_to_start_playing();
public:
	DeathScreen(int id, 
				SDL_Renderer* renderer, 
				std::unordered_map<int, Goat2d::core::Font*>& fonts,
				int high_score);
	~DeathScreen();
	void render() override;


};


#endif