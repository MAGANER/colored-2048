#ifndef TEST_SCENE_H
#define TEST_SCENE_H
#include"Scene.h"
#include<algorithm>
using namespace Goat2d::core;
using namespace Goat2d::framework;

class TestScene : public BaseScene
{
private:
	Rectangle* rect, *rect2;
	Line* line;
	Point* p;
	Font* font;
	Text* text;
public:
	TestScene(int id, SDL_Renderer* renderer) :BaseScene(id, renderer)
	{
		rect = create_rect(std::make_tuple(Vector2i(0, 0), Vector2i(20, 20), Color(55, 23, 165, 255)));
		rect2 = create_outlined_rect(std::make_tuple(Vector2i(50, 50), Vector2i(20, 20), Color(55, 23, 165, 255)),
			std::make_pair(10, Color(255, 0, 0, 255)));
		auto pred = [](const SDL_Event& e) -> bool
		{
			return is_key_released(e, SDLK_w);
		};
		auto action = [](void* state)
		{
			std::cout << "hey!";
		};

		auto say_hey = new KeyboardEvent(pred, action);
		event_manager.add_event(say_hey);


		auto check_moving_right = [](const SDL_Event& e)-> bool
		{
			return is_key_released(e, SDLK_d);
		};
		auto move_right = [&](void* state)
		{
			auto curr_pos = rect->get_pos();
			curr_pos.x += 5;
			rect->update_pos(curr_pos);
		};
		auto move_right_event = new KeyboardEvent(check_moving_right, move_right);
		event_manager.add_event(move_right_event);



		auto check_is_rect_far = [&](void* e) ->bool
		{
			return rect->get_pos().x > 20;
		};
		auto say_is_far = [&](void* state)->void
		{
			rect->set_color(Color(66, 44, 22, 255));
		};
		auto far_event = new SimpleEvent(check_is_rect_far, say_is_far, EventType::conditional);
		event_manager.add_event(far_event);


		auto check_should_move_left = [](const SDL_Event& e) -> bool
		{
			return is_key_released(e, SDLK_a);
		};
		auto move_left = [&](void* state)
		{
			auto curr_pos = rect2->get_pos();
			curr_pos.x -= 5;
			rect2->update_pos(curr_pos);
		};
		auto move_left_event = new KeyboardEvent(check_should_move_left, move_left,ZERO_STATE);
		event_manager.add_event(move_left_event);


		line = create_white_line(std::make_pair(Vector2i(10, 10), Vector2i(50, 50)));
		p = create_colored_point(Vector2i(100, 100), Color(255, 55, 55, 255));

		font = new Font("test.ttf", 64);
		text = create_white_text("hello, world!", Vector2i(200, 200), font);
	}
	~TestScene()
	{
		delete rect;
		delete rect2;
		delete line;
		delete p;
		delete font;
		delete text;
	}

	void render()
	{
		rect->draw(rect->get_pos());
		rect2->draw(rect2->get_pos());
		line->draw(line->get_pos());
		p->draw(p->get_pos());
		text->draw(text->get_pos());
	}
};
#endif