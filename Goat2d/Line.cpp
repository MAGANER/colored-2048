#include"Line.h"
using namespace Goat2d::core;

Line::Line(const begin_end& points, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	pos = points.first;//start point
	end = points.second;
}
Line::Line(const begin_end& points, const Color& color, SDL_Renderer* renderer)
				:DrawableObject(renderer)
{
	this->color = color;
	pos = points.first;//start point
	end = points.second;
}
Line::~Line()
{
}

void Line::draw(const Vector2i& position)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, pos.x, pos.y, end.x, end.y);
}