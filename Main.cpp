
#include "CommonFuncion.h"
#include "MainObject.h"
#include "ThreatsObject.h"
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
	if (!Init()) //ktra có kick thước game hiển thị
		return 0; //k có thì out ctrinh
	g_bkground = SDLCommonFuncion::LoadImage("bk1.png"); //có kt màn hình load ảnh nền
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	
	//Nhân vật chính
	MainObject human_object; //tạo nhân vật chính
	human_object.setRect(100, 200); //vị trí xuất hiện
	bool ret= human_object.loadimg("plane_fly.png"); // ret=true,p_object=plane_fly 
	if (!ret)
	{
		return false;
	}
	// human_object.Show(g_screen); //thay p_object ở trên vào hàm load trên nền màn hình nền
	

	//threatsobject
	//khởi tạo một biến rand_y để vị trí máy bay xuât hiện ở độ cao rand_y trong hàm setRect()
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - 200)
	{
		rand_y = (SCREEN_HEIGHT - 200) * 0.3;
	}

	ThreatsObject* p_threats = new ThreatsObject[NUM_Threat];//khởi tạo một mảng gồm số threat = num_threat
	for (int t = 0; t < NUM_Threat; t++)
	{
		ThreatsObject* p_threat = p_threats + t; //tạo p_threat= p_threats +t
		if (p_threat)
		{
			ret = p_threat->loadimg("af1.png"); //load ảnh

			if (!ret)
			{
				return 0;
			}
			p_threat->setRect(SCREEN_WIDTH + t * 400, rand_y); //dùng rand_y
			p_threat->setval_x(10); //set giá trị x_val_ để threats di chuyển 1 lần đc 5 pixel rồi vào vòng lặp while gọi hàm handlemove

			AmoObject* p_amo = new AmoObject(); //khởi tạo đạn
			p_threat->InitAmo(p_amo); //truyền đạn cho threat
		}
	}
	


	//sau khi khởi tạo mainobject và threatsobject vào hàm while để xử lý các chuỗi chương trình
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

		//xử lý cho mainobject
		human_object.Show(g_screen);//thay p_object ở trên vào hàm load trên nền màn hình nền
		human_object.HandleMove();

		for (int i = 0; i < human_object.GetAmoList().size(); i++) //i là đạn thứ i,kiểm tra xe i có nhỏ hơn số đạn đc bắn ra
		{
			std::vector<AmoObject*> amo_list = human_object.GetAmoList(); // tạo list đạn bằng số đạn bắn ra
			AmoObject* p_amo = amo_list.at(i);//tạo con trỏ đạn thứ i
			if (p_amo != NULL) //nếu có đạn (tức là con trỏ có vị trí để trỏ tới
			{
				if (p_amo->get_is_move()) //gọi hàm kiểm tra xem có được phép di chuyển k
				{
					p_amo->Show(g_screen); //show đạn lên màn hình
					p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				}
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

		//xử lý cho threatobject
		for (int tt = 0; tt < NUM_Threat; tt++)
		{
			ThreatsObject* p_threat = p_threats + tt;
			if (p_threat)
			{
				p_threat->Show(g_screen); //load ảnh threat vào nền
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT - 200); //gọi hàm di chuyển cho threat
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT); //gọi hàm bắn đạn cho threat
			}
		}
		
		if (SDL_Flip(g_screen) == -1)
			return 0;
	}
	delete[] p_threats;//delete con trỏ 
	//còn một con trỏ p_amo đc tạo ra để truyền vào hàm  nạp đạn cho threat ta cần delete;xử lý trong ~ThreatsObject()

	SDLCommonFuncion::ClearnUp(); 
	SDL_Quit();

	return 1;
}
