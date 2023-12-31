#include"Goat2d/Definitors.hpp"
#ifdef USE_SDL_TTF

#ifndef TEXT_H
#define TEXT_H
#include"DrawableObject.h"
#include"Font.h"
#include"Color.h"
namespace Goat2d
{
namespace core
{
	/*
		overwrapper for Text. It works in the similar way with Texture class
	*/
	class Text: public DrawableObject
	{
	private:
		bool ok = true; //false, if something went wrong with text creation

		SDL_Texture* text_texture = nullptr;
		SDL_Rect* rect = nullptr;
		
		Font* font;
		Color color;
	public:
		Text(const Font& font,
			 const std::string& text,
			 const Vector2i& pos,
			 SDL_Renderer* renderer,
			 const Color& color=Color(255,255,255,255));
		~Text();

		void draw(const Vector2i& position) override;
		void update_pos(const Vector2i& new_pos) override;
		void set_color(const Color& color);

		bool is_ok()const { return ok; }

		Text* update_text(const std::string& text);
	};
};
};
#endif //TEXT_H
#endif //USE_SDL_TTF