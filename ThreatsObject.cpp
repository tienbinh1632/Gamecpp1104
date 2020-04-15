#include "ThreatsObject.h"



ThreatsObject::ThreatsObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = threats_width; //set kích thước ảnh
	rect_.h = threats_height; //set kích thước ảnh

	val_x = 0;
	val_y = 0;
}

ThreatsObject::~ThreatsObject()
{
	if (p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

//hàm đc nạp một p_amo để nạp đạn
void ThreatsObject::InitAmo(AmoObject* p_amo)
	{
		if (p_amo != NULL)
		{
			
			bool ret = p_amo->loadimg("sphere2.png"); //load ảnh đạn
			if (ret) 
			{
				p_amo->SetWidthHeight(sphere_Width, sphere_Height); //set kick thước đạn
				p_amo->set_amo_type(AmoObject::Sphere);//set kiểu đạn
				p_amo->setRect(rect_.x, rect_.y + rect_.h * 0.5);//set vị trí bắn đạn cho threats
				p_amo_list_.push_back(p_amo); //gán p_amo_list = một list các p_amo
			}
		}
	}

void ThreatsObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_litmit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move()) //nếu lệnh di chuyển ok
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else // nếu lệnh di chuyển not
			{
				p_amo->set_is_move(true); 
				//reset lại lệnh di chuyển thành oke và gọi hàm vị trí xuất hiện của đạn
				p_amo->setRect(rect_.x, rect_.y + rect_.h * 0.5);
			}
		}
	}
}

void ThreatsObject::HandleMove(const int& x_boder,const int& y_boder)
{
	rect_.x -= val_x; 
	//mỗi lần di chuyển threatsobject sẽ di chuyển sang bên trái màn hình 1 đoạn là x_val;
	//ta cần cho đầu vào của x_val khi gọi hàm di chuyển của threatsobject

	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y > SCREEN_HEIGHT-200) //0> screen_height là vị trí độ cao của threats xuất hiện
		{
			rand_y = (SCREEN_HEIGHT - 200) * 0, 3;
		}
		rect_.y = rand_y;
	}
}

void ThreatsObject::HandleInputAction(SDL_Event events)
{
	
}