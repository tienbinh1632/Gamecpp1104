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
	SDL_Rect offset; //khó giải thích.lề trái ở vị trí offset.x;sau khi kết thúc một vòng lặp while thì offset.x dịch chuyển sang trái 1 đoạn x=> lề trái reset vị trí mới là x;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

void SDLCommonFuncion::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}

bool SDLCommonFuncion:: CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	//khai báo biến biểu thị cho tọa độ góc của các object
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	//case 1 : size object1<size object2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}

void SDLCommonFuncion::ClearnUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}