#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"DrawableObject.h"
#include"Color.h"
#include<tuple>
#include<utility>
namespace Goat2d
{
namespace core
{
	//size, position and its filling color
	typedef std::tuple<Vector2i, Vector2i, Color> rect_data;

	//outline width and its color
	typedef std::pair<int, Color> outline_rect_data;

	/*
		This class is based on DrawableObject, but almost everything in core
		is just overwrapper for some low-level SDL features.
		So Rectangle is convenient class to draw/move/change color
		of low-level primitive.
	*/
	class Rectangle :public DrawableObject
	{
		SDL_Rect* fill_rect = nullptr; //contains position and size
		SDL_Rect* outline = nullptr; //outline colored rectangle

		Color* outline_color = nullptr; //rectangle can have no outline, so outline color is nullptr
		Color* color = nullptr; //color that fills entire rect
	public:

		//create regular rect filled with some color
		Rectangle(const rect_data& parameters,
				  SDL_Renderer* renderer);

		//create filled rect with outline
		Rectangle(const rect_data& parameters,
				  const outline_rect_data& outline_parameters,
				  SDL_Renderer* renderer);

		~Rectangle();

		void draw(const Vector2i& position)override;

		void set_color(const Color& color);
		void set_outline_color(const Color& color);


		void update_pos(const Vector2i& new_pos) override
		{
			pos = new_pos;

			//change position if it's not hollow rect
			if (fill_rect != nullptr)
			{
				fill_rect->x = new_pos.x;
				fill_rect->y = new_pos.y;
			}

			//change outline's position if it exists
			if (outline != nullptr)
			{
				outline->x = new_pos.x;
				outline->y = new_pos.y;
			}
		}
	};
};

};
#endif