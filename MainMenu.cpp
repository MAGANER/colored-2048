#include"MainMenu.h"

MainMenu::MainMenu(int id, SDL_Renderer* renderer, const std::unordered_map<int, Goat2d::core::Font*>& fonts)
	:BaseScene(id, renderer)
{
	this->fonts = fonts;

	generate_title();
	generate_press_start_title();

	classic = create_white_text("classic", Vector2i(160, 120), this->fonts[36]);
	middle = create_white_text("middle", Vector2i(170, 150), this->fonts[36]);
	is_it_playable = create_white_text("is it playable", Vector2i(120, 180), this->fonts[36]);
	update_current_level_color();

	add_event_to_check_movement_down();
	add_event_to_check_movement_up();
	add_event_to_start_game();
}
MainMenu::~MainMenu()
{
	if (_2048 != nullptr)
		delete _2048;
	if (classic != nullptr)
		delete classic;
	if (middle != nullptr)
		delete middle;
	if (is_it_playable != nullptr)
		delete is_it_playable;
	if (press != nullptr)
		delete press;
	if (start != nullptr)
		delete start;
	if (to_play != nullptr)
		delete to_play;
}

void MainMenu::render()
{
	for (auto& e : colored)
		e->draw(e->get_pos());

	_2048->draw(_2048->get_pos());

	classic->draw(classic->get_pos());
	middle->draw(middle->get_pos());
	is_it_playable->draw(is_it_playable->get_pos());

	press->draw(press->get_pos());
	start->draw(start->get_pos());
	to_play->draw(to_play->get_pos());
}
void MainMenu::generate_title()
{
	std::string colored = "COLORED";
	
	//create different text textures. All of them have different sizes
	for (auto& e : colored)
	{
		std::string ch; ch += e;
		auto character = create_colored_text(ch, Vector2i(0, 0),get_random_color(), this->fonts[48]);
		this->colored.push_back(character);
	}

	//aritmethicaly average value of some progression is sum of all elements that is divided
	//by total number of the progression's elements
	size_t total_width = 0;
	for (auto& e : this->colored)
	{
		total_width += e->get_size().x;
	}
	size_t average_width = total_width / this->colored.size();


	//set their position
	auto start_pos = Vector2i(100, 10);
	for (size_t i = 0; i < this->colored.size(); i++)
	{
		if (i != 0)
		{
			start_pos.x += average_width;
		}
		this->colored[i]->update_pos(start_pos);
	}

	//set 2048 title righter from the last character
	auto pos = (*(--this->colored.end()))->get_pos();
	pos.x += average_width+10;
	_2048 = create_white_text("2048", pos, this->fonts[48]);
}
void MainMenu::generate_press_start_title()
{
	press = create_white_text("press ", Vector2i(80, 400), this->fonts[36]);
	auto start_pos = 80 + press->get_size().x + 5;
	start = create_colored_text(" SPACE ", Vector2i(start_pos, 400),Color(255,0,0,255), this->fonts[36]);
	to_play = create_white_text(" to play", Vector2i(start_pos + start->get_size().x + 5, 400), this->fonts[36]);
}
unsigned short MainMenu::get_random_number()
{
	//std stuff
	std::random_device rd;   
	std::mt19937 gen(rd());  
	std::uniform_int_distribution<> dist(0, 255); 
	return static_cast<unsigned short>(dist(gen));
}
Color MainMenu::get_random_color()
{
	auto r = get_random_number();
	auto g = get_random_number();
	auto b = get_random_number();

	//prevent creation of white color
	if (r == g == b == 255)
	{
		r = 35;
		g = 0;
	}
	return Color(r, g, b, 255);
}
void MainMenu::update_current_level_color()
{
	if (level == complexity_level::classic)
	{
		classic->set_color(get_random_color());
		middle->set_color(Color(255, 255, 255, 255));
		is_it_playable->set_color(Color(255, 255, 255, 255));
	}
	else if (level == complexity_level::middle)
	{
		classic->set_color(Color(255, 255, 255, 255));
		middle->set_color(get_random_color());
		is_it_playable->set_color(Color(255, 255, 255, 255));
	}
	else if (level == complexity_level::is_it_playable)
	{
		classic->set_color(Color(255, 255, 255, 255));
		middle->set_color(Color(255, 255, 255, 255));
		is_it_playable->set_color(get_random_color());
	}
}
void MainMenu::add_event_to_check_movement_down()
{
	auto check_move_down = [](const SDL_Event& e) ->bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_DOWN) or
			Goat2d::framework::is_key_released(e, SDLK_s);
	};
	auto move_down = [&](void* e)->void
	{
		if (level == complexity_level::classic)
			level = complexity_level::middle;
		else if (level == complexity_level::middle)
			level = complexity_level::is_it_playable;
		else if (level == complexity_level::is_it_playable)
			level = complexity_level::classic;

		update_current_level_color();
	};

	auto moving_down_event = new Goat2d::framework::KeyboardEvent(check_move_down, move_down);
	event_manager.add_event(moving_down_event);
}
void MainMenu::add_event_to_check_movement_up()
{
	auto check_move_up = [](const SDL_Event& e) ->bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_UP) or
			Goat2d::framework::is_key_released(e, SDLK_w);
	};

	auto move_up = [&](void* e)->void
	{
		if (level == complexity_level::classic)
			level = complexity_level::is_it_playable;
		else if (level == complexity_level::middle)
			level = complexity_level::classic;
		else if (level == complexity_level::is_it_playable)
			level = complexity_level::middle;

		update_current_level_color();
	};
	
	auto moving_up_event = new Goat2d::framework::KeyboardEvent(check_move_up, move_up);
	event_manager.add_event(moving_up_event);
}
void MainMenu::add_event_to_start_game()
{
	auto check_space = [](const SDL_Event& e) -> bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_SPACE);
	};
	auto start_game = [&](void* e)->void
	{
		set_next_id(1);
		should_change = true;
		return_value = static_cast<void*>((int*)&level);
	};
	auto start_event = new Goat2d::framework::KeyboardEvent(check_space, start_game);
	event_manager.add_event(start_event);
}