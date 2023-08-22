#include"Rectangle.h"
using namespace Goat2d::core;

Rectangle::Rectangle(const rect_data& parameters,
					 SDL_Renderer* renderer) :DrawableObject(renderer)
{
	fill_rect = new SDL_Rect;

	this->pos = std::get<0>(parameters);
	this->size = std::get<1>(parameters);

	this->color = new Color;
	auto color = std::get<2>(parameters);
	copy_color(this->color, &color);

	fill_rect->x = pos.x;
	fill_rect->y = pos.y;
	fill_rect->w = size.x;
	fill_rect->h = size.y;
}
Rectangle::Rectangle(const rect_data& parameters,
					 const outline_rect_data& outline_parameters,
					 SDL_Renderer* renderer) :DrawableObject(renderer)
{
	fill_rect = new SDL_Rect;

	this->pos = std::get<0>(parameters);
	this->size = std::get<1>(parameters);
	
	this->color = new Color;
	auto color = std::get<2>(parameters);
	copy_color(this->color, &color);

	fill_rect->x = pos.x;
	fill_rect->y = pos.y;
	fill_rect->w = size.x;
	fill_rect->h = size.y;

	outline = new SDL_Rect;
	outline->w = this->size.x+outline_parameters.first * 2;
	outline->h = this->size.y+outline_parameters.first * 2;
	outline->x = pos.x-(outline_parameters.first);
	outline->y = pos.y-(outline_parameters.first);


	outline_color = new Color;
	color = outline_parameters.second;
	copy_color(outline_color, &color);


}

Rectangle::~Rectangle()
{
	if (fill_rect != nullptr)
		delete fill_rect;
	if (outline_color != nullptr)
		delete outline_color;
	if (outline != nullptr)
		delete outline;
	if (color != nullptr)
		delete color;
}

void Rectangle::draw(const Vector2i& position)
{
	if (color != nullptr)
	{
		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
		SDL_RenderFillRect(renderer, fill_rect);
	}

	if (outline_color != nullptr)
	{
		SDL_SetRenderDrawColor(renderer, outline_color->r, outline_color->g, outline_color->b, outline_color->a);
		SDL_RenderDrawRect(renderer, outline);
	}
}
void Rectangle::set_color(const Color& color)
{
	if (this->color != nullptr)
	{
		copy_color(this->color, &const_cast<Color&>(color));
	}
}
void Rectangle::set_outline_color(const Color& color)
{
	if (this->outline_color != nullptr)
	{
		copy_color(this->outline_color, &const_cast<Color&>(color));
	}
}