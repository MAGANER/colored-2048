#include"Point.h"
using namespace Goat2d::core;

Point::Point(const Vector2i& pos, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	this->pos = pos;
}
Point::Point(const Vector2i& pos, const Color& color, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	this->pos = pos;
	this->color = color;
}


void Point::draw(const Vector2i& pos)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}
void Point::update_pos(const Vector2i& new_pos)
{
	pos = new_pos;
}