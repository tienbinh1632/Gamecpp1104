
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
	bool is_quit_ = false;
	if (Init() == false) //ktra có kick thước game hiển thị
		return 0; //k có thì out ctrinh
	g_bkground = SDLCommonFuncion::LoadImage("bk1.png"); //có kt màn hình load ảnh nền
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	

	MainObject human_object; //tạo nhân vật chính
	human_object.setRect(100, 200); //kick thước xuất hiện
	bool ret= human_object.loadimg("plane80x46.png"); // ret=true,p_object=plane80x46 
	if (!ret)
	{
		return false;
	}

	// human_object.Show(g_screen); //thay p_object ở trên vào hàm load trên nền màn hình nền
	

	while (!is_quit_) //hàm chạy liên tục.Nếu kick vào biểu tượng X ở trên thanh công cụ thì is_quit=true =>out program
	{
		while (SDL_PollEvent(&g_even)) //sau khi có nv rồi xử lý các bước di chuyển đạn bắn của nv thì xử lý trong vòng lặp while();
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit_ = true;
				break;
			}
			human_object.HandleInputAction(g_even);//load biến sau khi sử lý sự kiện để gọi đến hàm handlemove()
		}

		SDLCommonFuncion::ApplySurface(g_bkground, g_screen, 0, 0); //tải ảnh nền vào 
		human_object.Show(g_screen);//thay p_object ở trên vào hàm load trên nền màn hình nền
		human_object.HandleMove();

		for (int i = 0; i < human_object.GetAmoList().size(); i++) //i là đạn thứ i,kiểm tra xe i có nhỏ hơn số đạn đc bắn ra
		{
			std::vector<AmoObject*> amo_list = human_object.GetAmoList(); // tạo list đạn bằng số đạn bắn ra
			AmoObject* p_amo = amo_list.at(i);//tạo con trỏ đạn thứ i
			if (p_amo != NULL) //nếu có đạn (tức là con trỏ có vị trí để trỏ tới
			{
				p_amo->Show(g_screen); //show đạn lên màn hình
				p_amo->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
			}
			else //đạn đi quá giới hạn hoặc chưa thao tác bấm chuột
			{
				if (p_amo != NULL) //nếu đạn đi quá giới hạn
				{
					amo_list.erase(amo_list.begin() + i); //xóa đạn ra khỏi list
					human_object.SetAmoList(amo_list); //load lại list mới

					delete p_amo;
					p_amo = NULL;

				}
			}
		}



		if (SDL_Flip(g_screen) == -1)
			return 0;
	}

	SDLCommonFuncion::ClearnUp(); 
	SDL_Quit();

	return 1;
}
