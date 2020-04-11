#include "CommonFuncion.h"

SDL_Surface* SDLCommonFuncion::LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);

		if (optimize_image)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xff, 0xff);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}

		return optimize_image;
	}
}

void SDLCommonFuncion::ApplySurface(SDL_Surface*src,SDL_Surface*des,int x,int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

void SDLCommonFuncion::ClearnUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}