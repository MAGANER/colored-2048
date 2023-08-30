#include"DeathScreen.h"

DeathScreen::DeathScreen(int id, 
						 SDL_Renderer* renderer, 
						 std::unordered_map<int, Goat2d::core::Font*>& fonts,
						 int high_score)
				:BaseScene(id,renderer)
{
	this->high_score = high_score;
	big_font = fonts[70];
	small_font = fonts[36];

	label = create_colored_text("FAILED",
		Goat2d::core::Vector2i(130, 60),
		Goat2d::core::Color(255, 54, 43, 255), big_font);

	generate_high_score();
	generate_press_start();

	add_event_to_start_playing();
}
DeathScreen::~DeathScreen()
{
	if (label != nullptr)
		delete label;
}
void DeathScreen::render()
{
	label->draw(label->get_pos());

	for (auto& e : high_score_)
		e->draw(e->get_pos());

	for (auto& e : press_start)
		e->draw(e->get_pos());
}
void DeathScreen::generate_high_score()
{
	auto first_text = create_white_text("your high score is ",
		Goat2d::core::Vector2i(90, 180), small_font);

	auto score = create_colored_text(std::to_string(high_score),
		Goat2d::core::Vector2i(100 + first_text->get_size().x, 180),
		Goat2d::core::Color(100, 70, 200, 255), small_font);

	high_score_.push_back(first_text);
	high_score_.push_back(score);
}
void DeathScreen::generate_press_start()
{
	using namespace Goat2d::core;
	auto press = create_white_text("press ", Vector2i(80, 400), small_font);
	auto start_pos = 80 + press->get_size().x + 5;
	auto start = create_colored_text(" SPACE ", Vector2i(start_pos, 400), Color(255, 0, 0, 255), small_font);
	auto to_play = create_white_text(" to play", Vector2i(start_pos + start->get_size().x + 5, 400), small_font);

	press_start.push_back(press);
	press_start.push_back(start);
	press_start.push_back(to_play);
}
void DeathScreen::add_event_to_start_playing()
{
	auto check_space_pressed = [](const SDL_Event& e)
	{
		return Goat2d::framework::is_key_released(e, SDLK_SPACE);
	};
	auto start = [&](void* e)
	{
		set_next_id(0);
		should_change = true;
	};

	auto event = new Goat2d::framework::KeyboardEvent(check_space_pressed, start);
	event_manager.add_event(event);
}