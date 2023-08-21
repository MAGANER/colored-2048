#ifndef LINE_H
#define LINE_H
#include"DrawableObject.h"
#include"Color.h"
#include<utility>
namespace Goat2d
{
namespace core
{
	//first value is beginning point
	//second value is end point
	typedef std::pair<Vector2i, Vector2i> begin_end;

	/*
		Line class is overwrapper for SDL ability to render lines
	*/
	class Line :public DrawableObject
	{
		Vector2i end; //DrawableObject's pos field is beginning point
		Color color = Color(255, 255, 255, 255);
	public:
		Line(const begin_end& points,SDL_Renderer* renderer);
		Line(const begin_end& points,const Color& color, SDL_Renderer* renderer);
		~Line();

		void draw(const Vector2i& position) override;

		//don't use this function because you need to change 2 points
		void update_pos(const Vector2i& new_pos) override { return; }

		void update_pos(const Vector2i& new_pos_begin, const Vector2i& new_pos_end)
		{
			pos = new_pos_begin;
			end = new_pos_end;
		}
	};
};
};

#endif //LINE_H