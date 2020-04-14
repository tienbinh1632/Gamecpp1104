#include "ThreatsObject.h"



ThreatsObject::ThreatsObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = threats_width; //set kích thước ảnh
	rect_.h = threats_height; //set kích thước ảnh

	val_x_ = 0;
	val_y_ = 0;
}

ThreatsObject::~ThreatsObject()
{
	
}

void ThreatsObject::HandleMove(const int& x_boder,const int& y_boder)
{
	rect_.x -= val_x_; 
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