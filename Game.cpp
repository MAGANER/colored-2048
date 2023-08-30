#include"Game.h"

Game::Game(int id, 
		   SDL_Renderer* renderer, 
		   std::unordered_map<int, Font*>& fonts,
		   int complexity_level):
				BaseScene(id,renderer)
{
	this->complexity_level = complexity_level;
	this->font = fonts[70];
	small_font = fonts[60];
	

	this->field = new Matrix<el>(4, 4);

	init_background();
	init_colors();
	init_field();

	for (size_t i = 0; i < 3; i++)generate_random_block();


	create_left_movement_event();
	create_right_movement_event();
	create_up_movement_event();
	create_down_movement_event();
	create_check_losing_event();
}
Game::~Game()
{
	if (colors != nullptr)
		delete[] colors;
	if (field != nullptr)
		delete field;
}

void Game::render()
{
	for (auto& r : background)
		r->draw(r->get_pos());

	draw_blocks();
}
void Game::init_background()
{
	auto pos = Vector2i(2, 2);
	const auto size = Vector2i(123, 123);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			auto rect_data = std::make_tuple(pos, size, Color(104, 98, 106, 200));
			auto outline = std::make_pair(2, Color(20, 20, 20, 100));
			auto rect = create_outlined_rect(rect_data,outline);
			background.push_back(rect);
			pos.x += size.x+2;
		}
		pos.y += size.y+2;
		pos.x = 2;
	}
}
void Game::init_colors()
{

	colors = new Color * [3];
	colors[0] = new Color{ 213,119,240,255 };
	colors[1] = new Color{119,240,213,255};
	colors[2] = new Color{240,213,119,255};
}
void Game::init_field()
{
	for (size_t y = 0; y < 4; y++)
	{
		for (size_t x = 0; x < 4; x++)
		{
			field->set_element((void*)nullptr,x,y);
		}
	}
}

void Game::generate_random_block()
{
	auto pos = get_random_pos();
	auto col = get_random_color();
	field->set_element(make_pair(col, 2), pos.x, pos.y);
}

int Game::get_random_number(int a, int b)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(a, b);
	return dist(gen);
}
Vector2i Game::get_random_pos()
{
	auto empty_cells = get_empty_cells();
	if (empty_cells.empty()) return Vector2i(-1, -1);

	return empty_cells[get_random_number(0, empty_cells.size())];
}
std::vector<Vector2i> Game::get_empty_cells()
{
	std::vector<Vector2i> cells;
	for (size_t y = 0; y < 4; y++)
	{
		for (size_t x = 0; x < 4; x++)
		{
			auto cell = field->get_elem(x, y);
			if (holds_alternative<el>(cell))
			{
				auto e = get<0>(cell);
				if(holds_alternative<void*>(e))
					cells.push_back(Vector2i(x, y));
			}
		}
	}
	return cells;
}


void Game::draw_blocks()
{
	auto pos = Vector2i(2, 2);
	const auto size = Vector2i(123, 123);
	for (size_t y = 0; y < 4; y++)
	{
		for (size_t x = 0; x < 4; x++)
		{
			auto cell = get<el>(field->get_elem(x, y));
			if (holds_alternative<block>(cell))
			{
				auto b = get<block>(cell);
				auto color = b.first;
				auto rect_data = make_tuple(pos, size, b.first);
				auto rect = create_rect(rect_data);
				rect->draw(rect->get_pos());
				delete rect;

				auto t_pos = compute_text_pos(pos);
				auto t_text = to_string(b.second);
				if (t_text.size() == 2)t_pos.x -= 20;
				if (t_text.size() == 3)t_pos.x -= 40;
				if (t_text.size() == 4)t_pos.x -= 50;

				auto _font = t_text.size() == 4 ? small_font : this->font;
				auto t = create_colored_text(t_text, t_pos, Color(0, 0, 0, 255), _font);
				t->draw(t->get_pos());
				delete t;

			}
			pos.x += size.x + 2;	
		}
		pos.y += size.y + 2;
		pos.x = 2;
	}
}
Color Game::get_random_color()
{
	return *colors[get_random_number(0, complexity_level)];
}
void Game::iterate_over_matrix_4_times(const std::function<void(const Vector2i& pos)>& fn)
{
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				fn(Vector2i(x,y));
			}
		}
	}

	generate_random_block();
}
void Game::move_element(const Vector2i& pos, const Vector2i& dir,bool move_down)
{
	//worst method ever written

	if (pos.y == 3 and move_down)return;//fix problem with moving down


	auto curr = field->get_elem(pos.x, pos.y);
	auto next = field->get_elem(pos.x +dir.x, pos.y+dir.y);

	if (holds_alternative<el>(next))
	{
		if (holds_alternative<void*>(get<0>(next)))
		{
			auto curr_el = get<0>(curr);
			field->set_element(curr_el, pos.x + dir.x, pos.y + dir.y);
			field->set_element((void*)nullptr, pos.x, pos.y);
		}
		else
		{
			if (holds_alternative<el>(curr))
			{
				auto _curr_val = get<el>(curr);
				if (holds_alternative<block>(_curr_val))
				{
					auto curr_val = get<block>(_curr_val);
					if (holds_alternative<el>(next))
					{
						auto e = get<el>(next);
						if (holds_alternative<block>(e))
						{
							auto next_val = get<block>(get<el>(next));

							auto eq_color = compare_colors(&next_val.first, &curr_val.first);
							auto eq_numbers = curr_val.second == next_val.second;
							if (eq_color and eq_numbers)
							{
								next_val.second *= 2;
								field->set_element(next_val, pos.x + dir.x, pos.y + dir.y);
								field->set_element((void*)nullptr, pos.x, pos.y);
							}
						}
					}
				}
			}
		}
	}
}

void Game::create_left_movement_event()
{
	auto check_move_left = [](const SDL_Event& e) ->bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_a);
	};

	auto move_left = [&](void* e) ->void
	{
		iterate_over_matrix_4_times([&](const Vector2i& pos)
			{
				move_element(pos, Vector2i(-1, 0));
			});
	};

	auto event = new Goat2d::framework::KeyboardEvent(check_move_left, move_left);
	event_manager.add_event(event);
}
void Game::create_right_movement_event()
{
	auto check_move_right = [](const SDL_Event& e) ->bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_d);
	};

	auto move_right = [&](void* e) ->void
	{
		iterate_over_matrix_4_times([&](const Vector2i& pos)
			{
				move_element(pos, Vector2i(1, 0));
			});
	};

	auto event = new Goat2d::framework::KeyboardEvent(check_move_right, move_right);
	event_manager.add_event(event);
}
void Game::create_up_movement_event()
{
	auto check_move_up = [](const SDL_Event& e) ->bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_w);
	};

	auto move_up = [&](void* e) ->void
	{
		iterate_over_matrix_4_times([&](const Vector2i& pos)
			{
				move_element(pos, Vector2i(0, -1));
			});
	};

	auto event = new Goat2d::framework::KeyboardEvent(check_move_up, move_up);
	event_manager.add_event(event);
}
void Game::create_down_movement_event()
{
	auto check_move_down = [](const SDL_Event& e) ->bool
	{
		return Goat2d::framework::is_key_released(e, SDLK_s);
	};

	auto move_down = [&](void* e) ->void
	{
		iterate_over_matrix_4_times([&](const Vector2i& pos)
			{
				move_element(pos, Vector2i(0, 1),true);
			});
	};

	auto event = new Goat2d::framework::KeyboardEvent(check_move_down, move_down);
	event_manager.add_event(event);
}
Vector2i Game::compute_text_pos(const Vector2i& pos)
{
	return Goat2d::core::Vector2i(15 + pos.x + DIFF,
		-5 + pos.y + DIFF);
}
void Game::create_check_losing_event()
{
	auto check_losing = [&](void* e)
	{
		return get_empty_cells().empty();
	};
	auto change_scene = [&](void* e)
	{
		set_next_id(2);
		should_change = true;
		auto hs = get_high_score();
		return_value = static_cast<void*>((int*)&hs);
	};

	auto event = new Goat2d::framework::SimpleEvent(check_losing,
													change_scene, 
													Goat2d::framework::EventType::conditional);
	event_manager.add_event(event);
}
int Game::get_high_score()
{
	vector<int> points;
	for (size_t y = 0; y < 4; y++)
	{
		for (size_t x = 0; x < 4; x++)
		{
			auto _el = field->get_elem(x, y);
			if (holds_alternative<el>(_el))
			{
				auto _block = get<el>(_el);
				if (holds_alternative<block>(_block))
				{
					points.push_back(get<block>(_block).second);
				}
			}
		}
	}

	return *max_element(points.begin(), points.end());
}