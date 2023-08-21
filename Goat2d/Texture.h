#ifndef TEXTURE_H
#define TEXTURE_H
#include"DrawableObject.h"
#include"ErrorLogger.h"
namespace Goat2d
{
namespace core 
{
	/*
	 This class is used to load graphical images
	 and use them in game.
	*/
	class Texture: public DrawableObject
	{
		SDL_Texture* texture = nullptr;//pixel data
		SDL_Rect* drawing_rect = nullptr;//size, pos

		bool ok = true; //if it's true, than everything loaded correctly
	public:
		Texture(const std::string& path,SDL_Renderer* renderer);
		~Texture();

		void draw(const Vector2i& position)override;
		bool is_ok()const { return ok; }

		void update_pos(const Vector2i& new_pos)override
		{
			pos = new_pos;

			drawing_rect->x = new_pos.x;
			drawing_rect->y = new_pos.y;
		}
	};
	

};
};
#endif