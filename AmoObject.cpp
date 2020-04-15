#include "AmoObject.h"

AmoObject::AmoObject() 
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false; //k có lệnh di chuyển
	amo_type_ = None; // chưa bắn đạn
};

AmoObject::~AmoObject()
{

};


void AmoObject::HandleInputAction(SDL_Event events, SDL_Rect rect_obj)
{
	
}

void AmoObject::HandleMove(const int x_boder, const int y_boder)
{
	rect_.x += 20;
	if (rect_.x > x_boder)
	{
		is_move_ = false; //lệnh di chuyển bị hủy bỏ
	}
}

void AmoObject::HandleMoveRightToLeft()
{
	rect_.x -= 20;
	if (rect_.x < 0)
	{
		is_move_ = false;//lệnh di chuyển bị hủy bỏ
	}
}

