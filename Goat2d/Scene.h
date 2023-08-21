#ifndef SCENE_H
#define SCENE_H
#include"Event.h"
#include"Texture.h"
#include"Rectangle.h"
#include"Line.h"
#include"Point.h"
#include"Vector.h"
#include"Font.h"
#include"Text.h"
#include"Color.h"
namespace Goat2d
{
namespace framework
{
	/*
		BaseScene is one of the core ideas. It contains events,
		provided by event manager. They express everything that happens in game,
		also they are used to check and process keyboard/mouse/joystick events.
		
		So when you start to write your game, you start writing some scene.
		Main menu,for example. It contains some textual data, buttons and
		events like clicking,e.t.c
	*/
	class BaseScene
	{
	private:
		SDL_Renderer* renderer; //pointer to window's renderer
	protected:
		EventManager event_manager;
		bool should_change = false; //if true than should switch to another scene

		void* return_value = nullptr;//data that can be passed to next scene
		int id = 0;
	public:
		BaseScene(int id, SDL_Renderer* renderer):id(id),renderer(renderer){}
		virtual ~BaseScene(){}

		
		virtual void render() = 0;

		EventManager& get_event_manager() { return event_manager; }
		bool change()const { return should_change; }
		void const* get_return_value()const { return return_value; }
		int get_id()const { return id; }


		//these functions are used by SceneManager
		//so you don't need to call them
		void process_keyboard_events(SDL_Event& _event)
		{
			for (auto& e : event_manager.get_keyboard_events())
				e->process(static_cast<void*>(&_event));
		}
		void process_game_events()
		{
			for (auto& e : event_manager.get_conditional_events())
				e->process();
			for (auto& e : event_manager.get_nonconditional_events())
				e->process();
		}
	protected:

		//create texture/rect/another primitive based on current renderer

		//this method is used by children to avoid working with private renderer pointer
		//because it's incapsulated and unable to be used by other classes
		
		//these function are dedicated to framework's user to simplify creation of game objects
		inline core::Texture* create_texture(const std::string& path)
		{
			return new core::Texture(path, renderer);
		}

		inline core::Rectangle* create_rect(const core::rect_data& parameters)
		{
			return new core::Rectangle(parameters,renderer);
		}
		inline core::Rectangle* create_outlined_rect(const core::rect_data& parameters,
													 const core::outline_rect_data& outline_params)
		{
			return new core::Rectangle(parameters, outline_params, renderer);
		}
		inline core::Line* create_white_line(const core::begin_end& points)
		{
			return new core::Line(points, renderer);
		}
		inline core::Line* create_colored_line(const core::begin_end& points, const core::Color& color)
		{
			return new core::Line(points, color, renderer);
		}
		inline core::Point* create_white_point(const core::Vector2i& point)
		{
			return new core::Point(point, renderer);
		}
		inline core::Point* create_colored_point(const core::Vector2i& point, const core::Color& color)
		{
			return new core::Point(point, color, renderer);
		}
		inline core::Text* create_white_text(const std::string& text,const core::Vector2i& pos, core::Font* font)
		{
			return new core::Text(*font, text, pos, renderer);
		}
		inline core::Text* create_colored_text(const std::string& text, const core::Vector2i& pos, const core::Color& color, core::Font* font)
		{
			return new core::Text(*font, text, pos, renderer, color);
		}

	};
};
};

#endif