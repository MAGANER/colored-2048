#include"VictoryScreen.h"

VictoryScreen::VictoryScreen(int id,
							 SDL_Renderer* renderer,
							 std::unordered_map<int, Goat2d::core::Font*>& fonts)
					:BaseScene(id,renderer)
{
	big_font = fonts[70];
	small_font = fonts[36];


	label = create_colored_text("VICTORY",
		Goat2d::core::Vector2i(130, 60),
		Goat2d::core::Color(255, 54, 43, 255), big_font);



	gz = create_white_text("your reached the top! ",
		Goat2d::core::Vector2i(80, 180), small_font);

	generate_press_start();
	create_event_to_start_playing();
}
VictoryScreen::~VictoryScreen()
{
	if (label != nullptr)
		delete label;
	if (gz != nullptr)
		delete gz;

}

void VictoryScreen::render()
{
	label->draw(label->get_pos());
	gz->draw(gz->get_pos());


	for (auto& e : press_start)
		e->draw(e->get_pos());
}
void VictoryScreen::generate_press_start()
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
void VictoryScreen::create_event_to_start_playing()
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