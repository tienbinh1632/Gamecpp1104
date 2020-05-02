#include "BulletObject.h"

BulletObject::BulletObject() 
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_Bullet = false; //k có lệnh di chuyển
	bullet_type_ = None; // chưa bắn đạn
};

BulletObject::~BulletObject()
{

};


void BulletObject::HandleInputAction(SDL_Event events, SDL_Rect rect_obj)
{
	
}

void BulletObject::HandleMove(const int x_boder, const int y_boder)
{
	rect_.x += x_val_;
	if (rect_.x > x_boder)
	{
		is_Bullet = false; //lệnh di chuyển bị hủy bỏ
	}
}

void BulletObject::HandleMoveRightToLeft()
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		is_Bullet = false;//lệnh di chuyển bị hủy bỏ
	}
}

