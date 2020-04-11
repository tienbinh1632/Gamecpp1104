
#include "CommonFuncion.h"
#include "MainObject.h"
#undef main

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING == -1))
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); //thiết lập kick thước giao diện game

	if (g_screen == NULL)
	{
		return false;
	}
	return true;
}

int main(int arc,char* argv[])
{
	bool is_quit = false;
	if (Init() == false) //ktra có kick thước game hiển thị
		return 0; //k có thì out ctrinh
	g_bkground = SDLCommonFuncion::LoadImage("bk1.png"); //có kt màn hình load ảnh nền
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	SDLCommonFuncion::ApplySurface(g_bkground, g_screen, 0, 0); //tải ảnh nền vào 

	MainObject human_object; //tạo nhân vật chính
	human_object.setRect(300, 420); //kick thước xuất hiện
	bool ret= human_object.loadimg("plane80x46.png"); // ret=true,p_object=plane80x46 
	if (!ret)
	{
		return false;
	}

	human_object.Show(g_screen); //thay p_object ở trên vào hàm load trên nền màn hình nền

	while (!is_quit) //hàm chạy liên tục.Nếu kick vào biểu tượng X ở trên thanh công cụ thì is_quit=true =>out program
	{
		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
		}
		if (SDL_Flip(g_screen) == -1)
			return 0;
	}

	SDLCommonFuncion::ClearnUp(); 
	SDL_Quit();

	return 1;
}
