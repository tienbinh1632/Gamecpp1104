
#include "CommonFuncion.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TextObject.h"



#undef main


bool Init() //hàm khởi tạo
{
	//thiết lập kick thước giao diện game
	if (SDL_Init(SDL_INIT_EVERYTHING == Ga_failed))
	{
		return false;
	}

	
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); 

	if (g_screen == NULL)
	{
		return false;
	}


	
	//read file way audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == Ga_failed)
		return false;

	g_sound_bullet[0] = Mix_LoadWAV("Gun+1.wav");
	g_sound_bullet[1] = Mix_LoadWAV("Gun+Shot2.wav");
	exp_sound_exp[0] = Mix_LoadWAV("Explosion+1.wav");

	if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || exp_sound_exp[0] == NULL)
	{
		return false;
	}

	//text
	if (TTF_Init() == Ga_failed)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("SSNB.TTF",SizeText); 
	if (g_font_text == NULL)
	{
		return false;
	}

	return true;
}

int main(int arc,char* argv[])
{
	bool is_run_screen = true;// variable screen move command
	int bkgn_x = 0; //moving speed of the screen;

	bool is_quit_ = false;
	if (!Init()) //ktra có kick thước game hiển thị
		return 0; //k có thì out ctrinh

	g_bkground = SDLCommonFuncion::LoadImage("bg4800.png"); //có kt màn hình load ảnh nền
	if (g_bkground == NULL)
	{
		return 0;
	}
	
	//make player power
	PlayerPower player_power;
	player_power.Init();

	//make text
	//mark game
	TextObject mark_game;
	mark_game.SetColorText(TextObject::Red_text);

	//time game
	TextObject time_game;
	time_game.SetColorText(TextObject::White_Text);


	
	//Main object
	MainObject plane_object; //create main
	plane_object.setRect(100, 200); //vị trí xuất hiện
	bool ret= plane_object.loadimg("plane_fly.png"); // ret=true,p_object=plane_fly 
	if (!ret)
	{
		return false;
	}
	// human_object.Show(g_screen); //thay p_object ở trên vào hàm load trên nền màn hình nền
	
	//Init explosion object
	ExplosionObject exp_main; //khởi tạo biến vụ nổ của main
	ret = exp_main.loadimg("exp_main.png");
	exp_main.setclip();
	if (!ret)
	{
		return 0;
	}


	//threatsobject
	//khởi tạo một biến rand_y để vị trí máy bay xuât hiện ở độ cao rand_y trong hàm setRect()
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - Under_limit)
	{
		rand_y = (SCREEN_HEIGHT - Under_limit) * 0.3;
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

			BulletObject* p_bullet = new BulletObject(); //khởi tạo đạn
			p_threat->InitBullet(p_bullet); //truyền đạn cho threat
		}
	}
	
	//biến quản lý mạng;hết mạng mới gameover;
	unsigned int die_number = 0;
	unsigned int mark_value = 0; //điểm main bắn đc threats;

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
			plane_object.HandleInputAction(g_even,g_sound_bullet);//load biến sau khi sử lý sự kiện để gọi đến hàm handlemove()
		}
		//apply background

		// continuity move screen
		//if (is_run_screen)
		//{
			//bkgn_x -= 2;
			//SDLCommonFuncion::ApplySurface(g_bkground, g_screen, bkgn_x, 0); //tải ảnh nền vào 
			//SDLCommonFuncion::ApplySurface(g_bkground, g_screen, bkgn_x + SCREEN_WIDTH, 0);
			//if (bkgn_x <= -SCREEN_WIDTH)
			//{
			//	bkgn_x = 0;
			//}
		//}
		
		//screen move once and then stop.
		if (is_run_screen)
		{
			bkgn_x -= 2;
			if (bkgn_x <= SCREEN_WIDTH - BKG_WIDTH)
			{
				is_run_screen = false;
			}
			else 
			{
				SDLCommonFuncion::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
			}
		}
		else //comman run screen = false
		{
			SDLCommonFuncion::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
		}
		//show player power
		player_power.Render(g_screen);

		//xử lý cho mainobject
		plane_object.HandleMove();
		plane_object.Show(g_screen);//thay p_object ở trên vào hàm load trên nền màn hình nền
		plane_object.MakeBullet(g_screen); //add g_screen to show bullet up screen;

		//xử lý cho threatobject
		for (int tt = 0; tt < NUM_Threat; tt++)
		{
			ThreatsObject* p_threat = p_threats + tt;
			if (p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT - Under_limit); //gọi hàm di chuyển cho threat
				p_threat->Show(g_screen); //load ảnh threat vào nền
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT, 40); //gọi hàm bắn đạn cho threat
				if (SDL_Flip(g_screen) == -1) //update screen;
					return 0;

				//checkcollision main and threats
				bool is_col = SDLCommonFuncion::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				if (is_col)
				{
					//collision > explosion>game over
					for (int ex = 0; ex < 4; ex++)
					{
						int x_pos = plane_object.GetRect().x+ plane_object.GetRect().w*0.5-exp_width*0.5; // vị trí hình ảnh nổ xuất hiện trên ảnh main
						int y_pos = plane_object.GetRect().y + plane_object.GetRect().h * 0.5 - exp_height * 0.5;// vị trí hình ảnh nổ xuất hiện trên ảnh main
							//tâm vụ nổ nằm xh ở tâm main

						exp_main.setframe(ex);
						exp_main.setRect(x_pos, y_pos);
						exp_main.ShowExplosion(g_screen);
						Mix_PlayChannel(-1, exp_sound_exp[0], 1);
						SDL_Delay(100);
						
						if (SDL_Flip(g_screen) == -1) //update screen;
							return 0;
					}
					die_number++;
					if (die_number <= 2)
					{
						SDL_Delay(1000);
						plane_object.setRect(100,200);
						player_power.Decrease();
						player_power.Render(g_screen);


						if (SDL_Flip(g_screen) == -1) //update screen;
							return 0;
					}
					else
					{
						if (MessageBox(NULL, L"Game Over!", L"Info", MB_OK) == IDOK)//game over because main collision with threat
						{
							delete[] p_threats;
							SDLCommonFuncion::ClearnUp();
							SDL_Quit();
							return 1;
						}
					}
				}

				//checkcollision bullet of main and threats;
				std::vector<BulletObject*> bullet_list = plane_object.GetBulletList();
				for (int im = 0; im < bullet_list.size(); im++)
				{
					BulletObject* p_bullet = bullet_list.at(im);
					if (p_bullet != NULL)
					{
						bool ret_col = SDLCommonFuncion::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
						if (ret_col) //if collision is true
						{
							mark_value ++;
							p_threat->ResetThreat(SCREEN_WIDTH + tt*400);
							plane_object.RemoveBullet(im);
						}
					}
				}

			}
		}
		//show mark value to screen
		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");

		strMark += val_str_mark;
		mark_game.SetText(strMark);
		mark_game.CreateGameText(g_font_text, g_screen);

		//show time for game
		std::string strTime("Time");
		Uint32  time_val = SDL_GetTicks() / 1000;
		std::string str_val = std::to_string(time_val);
		strTime += str_val;

		time_game.SetText(strTime);
		time_game.setRect(SCREEN_WIDTH - 200, 10);
		time_game.CreateGameText(g_font_text, g_screen);


		//update screen;
		if (SDL_Flip(g_screen) == -1)
			return 0;
	}
	delete[] p_threats;//delete con trỏ 
	//còn một con trỏ p_bullet đc tạo ra để truyền vào hàm  nạp đạn cho threat ta cần delete;xử lý trong ~ThreatsObject()
	SDLCommonFuncion::ClearnUp(); 
	SDL_Quit();

	return 1;
}
