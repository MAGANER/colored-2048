#include"Texture.h"
#ifdef USE_SDL_IMG
using namespace Goat2d::core;

Texture::Texture(const std::string& path, SDL_Renderer* renderer):
    DrawableObject(renderer)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        ok = false;
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL)
        {
            ok = false;
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        SDL_Point size;
        SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
        this->size.x = size.x;
        this->size.y = size.y;

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
        this->renderer = renderer;


        drawing_rect = new SDL_Rect;
        drawing_rect->x = 0;
        drawing_rect->y = 0;
        drawing_rect->w = this->size.x;
        drawing_rect->h = this->size.y;
    }
}
void Texture::draw(const Vector2i& position)
{
    drawing_rect->x = position.x;
    drawing_rect->y = position.y;
	SDL_RenderCopy(renderer, texture, NULL, drawing_rect);
}
Texture::~Texture()
{
    if (drawing_rect != nullptr)
        delete drawing_rect;

	SDL_DestroyTexture(texture);
}
#endif