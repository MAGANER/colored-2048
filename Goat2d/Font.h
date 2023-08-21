#ifndef FONT_H
#define FONT_H
#include"SDL_ttf.h"
#include"ErrorLogger.h"
#include<string>
namespace Goat2d
{
namespace core
{
	/*
		Safe overwrapper for SDL_ttf font
	*/
	class Font
	{
		TTF_Font* font = nullptr;
		bool ok = true;
	public:
		Font(const std::string& path, int font_size)
		{
			font = TTF_OpenFont(path.c_str(), font_size);
			if (font == NULL)
			{
				print_error("Failed to load lazy font! SDL_ttf Error:");
				write_error("Failed to load lazy font! SDL_ttf Error:");
				ok = false;
			}
		}
		~Font()
		{
			TTF_CloseFont(font);
		}

		TTF_Font const* get_font()const { return font; }
		bool is_ok()const { return ok; }
	};
};
};

#endif //FONT_H