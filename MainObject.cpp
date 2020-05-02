#include "MainObject.h"


MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = Main_Width;//set kích thước ảnh
	rect_.h = Main_Height;//set kích thước ảnh
	x_val_ = 0;
	y_val_ = 0;

}

MainObject::~MainObject()
{
	;
}

//phải sử lý cả down và up vì nếu down thôi thì sẽ load liên tục chạy đến hết biên.khi up thì giá trị y_val=0;
void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* Bullet_sound[2])
{
	if (events.type == SDL_KEYDOWN) //bàn phím đc ấn xuống;
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: //mũi tên lên
			y_val_ -= Main_Height / 4; //dịch chuyển so với vị trí khởi tạo(= giá trị khởi tạo = 0) lên trên = chiều cao của Maiobject/4
			break;
		case SDLK_DOWN: //mũi tên xuống
			y_val_ += Main_Height / 4;
			break;
		case SDLK_RIGHT: //mũi sang phải
			x_val_ += Main_Width / 4;
			break;
		case SDLK_LEFT: //mũi sang trái
			x_val_ -= Main_Width / 4;
			break;
		default:
			break;
		}
	}

	else if (events.type==SDL_KEYUP) //bàn phím thả ra
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: //mũi tên lên
			y_val_ += Main_Height / 4; //lúc này y_val_ đã = y_val_ khi được down.chạy hết một vòng lặp while trong main sau đó chúng ta nhả ra.thì y_val_ sẽ đc trả lại giá trị = 0;để chạy tiếp một vòng lặp while() trong main;vi = 0 nên đứng im;
			break;
		case SDLK_DOWN: //mũi tên xuống
			y_val_ -= Main_Height / 4;
			break;
		case SDLK_RIGHT: //mũi sang phải
			x_val_ -= Main_Width / 4;
			break;
		case SDLK_LEFT: //mũi sang trái
			x_val_ += Main_Width / 4;
			break;
		default:
			break;
		}
	}

	else if (events.type == SDL_MOUSEBUTTONDOWN) //chuột ấn xuống
	{
		BulletObject* p_bullet = new BulletObject; //khi chuột đc ấn thì sẽ tạo ra 1 viên đạn;
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_bullet->SetWidthHeight(laser_Width, laser_Height); //cài đặt kick thước cho đạn kiểu laser
			p_bullet->loadimg("laser.png"); //load hình ảnh cho kiểu đạn
			p_bullet->set_bullet_type(BulletObject::Laser);
			Mix_PlayChannel(-1, Bullet_sound[0],0); //call sound for bullet laser is gun 1;change bulletsound = g_sound_bullet when call funcion HandlemoveInputAction
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_bullet->SetWidthHeight(sphere_Width, sphere_Height); //cài đặt kick thước cho đạn kiểu laser
			p_bullet->loadimg("sphere.png"); //load hình ảnh cho kiểu đạn
			p_bullet->set_bullet_type(BulletObject::Sphere);
			Mix_PlayChannel(-1, Bullet_sound[1], 0); //call sound for bullet laser is gun 2; //change bulletsound = g_sound_bullet when call funcion HandlemoveInputAction
		}

		//sau khi load hình ảnh kiểu đạn thì set vị trị xuất hiện
		//this->rect.xy là vị trí hiện tại của mainobject + thêm để xuất hiện ở nòng của main
		p_bullet->setRect(this->rect_.x + this->rect_.w*0.8, this->rect_.y + this->rect_.h*0.75);
		
		p_bullet->set_is_move(true); //cho phép đạn di chuyển để để gọi hàm handlemove trong main.cpp
		p_bullet->set_x_val(20);//speed bullet of main
		p_list_bullet_.push_back(p_bullet); // đạn thành list nhiều viên
	}

	else if (events.type == SDL_MOUSEBUTTONUP) //chuột  nhả ra
	{

	}

	else
	{

	}
}

void MainObject::HandleMove()
{
	rect_.x += x_val_;
	if (rect_.x < 0)
	{
		rect_.x = 0;
	}
	else if (rect_.x+ Main_Width> SCREEN_WIDTH)
	{
		rect_.x = SCREEN_WIDTH-Main_Width;
	}

	rect_.y += y_val_;
	if (rect_.y < 0)
	{
		rect_.y = 0;
	}
	else if (rect_.y + Under_limit +Main_Height> SCREEN_HEIGHT)//200 là độ cao giới hạn mặt đất
	{
		rect_.y = SCREEN_HEIGHT- Under_limit - Main_Height;
	}
}

void MainObject::MakeBullet(SDL_Surface* des)
{
	for (int i = 0; i < p_list_bullet_.size(); i++) //i là đạn thứ i,kiểm tra xe i có nhỏ hơn số đạn đc bắn ra
	{
		
		BulletObject* p_bullet = p_list_bullet_.at(i);//tạo con trỏ đạn thứ i
		if (p_bullet != NULL) //nếu có đạn (tức là con trỏ có vị trí để trỏ tới
		{
			if (p_bullet->get_is_move()) //gọi hàm kiểm tra xem có được phép di chuyển k
			{
				p_bullet->Show(des); //show bullet up des
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
		}
		else //đạn đi quá giới hạn hoặc chưa thao tác bấm chuột
		{
			if (p_bullet != NULL) //nếu đạn đi quá giới hạn
			{
				p_list_bullet_.erase(p_list_bullet_.begin() + i); //xóa đạn ra khỏi list
				
				delete p_bullet;
				p_bullet = NULL;

			}
		}
	}
}

void MainObject::RemoveBullet(const int& idx)
{
	
for (int i = 0; i < p_list_bullet_.size(); i++)
	{
		if (idx < p_list_bullet_.size())
		{
			BulletObject* p_bullet = p_list_bullet_.at(idx);
			p_list_bullet_.erase(p_list_bullet_.begin() + idx);

			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}