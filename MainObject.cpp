#include "MainObject.h"


MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = Main_Width;
	rect_.h = Main_Height;
	x_val_ = 0;
	y_val_ = 0;

}

MainObject::~MainObject()
{
	;
}

//phải sử lý cả down và up vì nếu down thôi thì sẽ load liên tục chạy đến hết biên.khi up thì giá trị y_val=0;
void MainObject::HandleInputAction(SDL_Event events) 
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
		AmoObject* p_amo = new AmoObject; //khi chuột đc ấn thì sẽ tạo ra 1 viên đạn;
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(laser_Width, laser_Height); //cài đặt kick thước cho đạn kiểu laser
			p_amo->loadimg("laser.png"); //load hình ảnh cho kiểu đạn
			p_amo->set_amo_type(AmoObject::Laser);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			p_amo->SetWidthHeight(sphere_Width, sphere_Height); //cài đặt kick thước cho đạn kiểu laser
			p_amo->loadimg("sphere.png"); //load hình ảnh cho kiểu đạn
			p_amo->set_amo_type(AmoObject::Sphere);
		}

		//sau khi load hình ảnh kiểu đạn thì set vị trị xuất hiện
		//this->rect.xy là vị trí hiện tại của mainobject + thêm để xuất hiện ở nòng của main
		p_amo->setRect(this->rect_.x + 80, this->rect_.y + 22); 
		
		p_amo->set_is_move(true); //cho phép đạn di chuyển để để gọi hàm handlemove trong main.cpp

		p_list_amo_.push_back(p_amo); // đạn thành list nhiều viên
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
	else if (rect_.y + 200 +Main_Height> SCREEN_HEIGHT)
	{
		rect_.y = SCREEN_HEIGHT-200- Main_Height;
	}
}
