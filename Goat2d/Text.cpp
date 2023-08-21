#include"Text.h"
using namespace Goat2d::core;

Text::Text(const Font& font,
		   const std::string& text,
		   const Vector2i& pos,
		   SDL_Renderer* renderer,
		   const Color& color)
					:DrawableObject(renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(const_cast<TTF_Font*>(font.get_font()), 
												text.c_str(), color);
	if (surface == NULL)
	{
		print_error("Unable to render text surface! SDL_ttf Error:");
		write_error("Unable to render text surface! SDL_ttf Error:");
		ok = false;
	}
	else
	{
		text_texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (text_texture == NULL)
		{
			print_error("Unable to create texture from rendered text! SDL Error:");
			write_error("Unable to create texture from rendered text! SDL Error:");
		}
		else
		{
			SDL_QueryTexture(text_texture, NULL, NULL, &size.x, &size.y);

			rect = new SDL_Rect;
			rect->x = pos.x;
			rect->y = pos.y;
			rect->w = size.x;
			rect->h = size.y;

			this->pos = pos;

		}

		//Get rid of old surface
		SDL_FreeSurface(surface);
	}

}
Text::~Text()
{
	SDL_DestroyTexture(text_texture);

	if (rect != nullptr)
		delete rect;
}
void Text::draw(const Vector2i& position)
{
	rect->x = position.x;
	rect->y = position.y;
	SDL_RenderCopy(renderer, text_texture, NULL, rect);
}
void Text::update_pos(const Vector2i& new_pos)
{
	pos = new_pos;
}