#ifndef POINT_H
#define POINT_H
#include"DrawableObject.h"
#include"Color.h"
namespace Goat2d
{
namespace core
{
	/*
		Simple overwrapper over basic point that can be renderer with SDL
	*/
	class Point :public DrawableObject
	{
		Color color = Color(255, 255, 255, 255);
	public:
		Point(const Vector2i& pos, SDL_Renderer* renderer);
		Point(const Vector2i& pos, const Color& color, SDL_Renderer* renderer);

		void draw(const Vector2i& position)override;
		void update_pos(const Vector2i& new_pos)override;
	};
};
};
#endif