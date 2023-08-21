#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H
#include"SDL_image.h"
#include"Vector.h"
namespace Goat2d
{
namespace core
{
	/*
		Base class for every object that can be drawn: textures, primitives.
	*/
	class DrawableObject
	{
	protected:
		//this pointer has an address of renderer that was initialised in GameWindow class
		//so you shouldn't init/delete it, just use it for SDL functions, where it's required
		SDL_Renderer* renderer = nullptr; //use it to draw

		DrawableObject(SDL_Renderer* renderer):renderer(renderer){}
		~DrawableObject(){}

		Vector2i size, pos;
	public:
		virtual void draw(const Vector2i& position) = 0;//draw at certain pos
		//TODO:: add method to draw object without passed position

		Vector2i const& get_size()const { return size; }
		Vector2i const& get_pos()const { return pos; }


		//this method is virtual because it probably changes SDL_Rect or something similar
		virtual void update_pos(const Vector2i& new_pos) = 0;
	};
};
};
#endif