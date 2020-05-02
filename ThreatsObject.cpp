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
	if (p_bullet_list_.size() > 0)
	{
		for (int i = 0; i < p_bullet_list_.size(); i++)
		{
			BulletObject* p_bullet = p_bullet_list_.at(i);
			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
		p_bullet_list_.clear();
	}
}

//hàm đc nạp một p_bullet để nạp đạn
void ThreatsObject::InitBullet(BulletObject* p_bullet)
	{
		if (p_bullet != NULL)
		{
			
			bool ret = p_bullet->loadimg("sphere2.png"); //load ảnh đạn
			if (ret) 
			{
				p_bullet->SetWidthHeight(sphere_Width, sphere_Height); //set kick thước đạn
				p_bullet->set_bullet_type(BulletObject::Sphere);//set kiểu đạn
				p_bullet->setRect(rect_.x, rect_.y + rect_.h * 0.5);//set vị trí bắn đạn cho threats
				p_bullet_list_.push_back(p_bullet); //gán p_bullet_list = một list các p_bullet
			}
		}
	}

void ThreatsObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_litmit,const int& speedbullet)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet)
		{
			if (p_bullet->get_is_move()) //nếu lệnh di chuyển ok
			{
				p_bullet->Show(des);
				p_bullet->set_x_val(speedbullet);
				p_bullet->HandleMoveRightToLeft();
			}
			else // nếu lệnh di chuyển not
			{
				p_bullet->set_is_move(true); 
				//reset lại lệnh di chuyển thành oke và gọi hàm vị trí xuất hiện của đạn
				p_bullet->setRect(rect_.x, rect_.y + rect_.h * 0.5);
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
		if (rand_y > SCREEN_HEIGHT- Under_limit) //0> screen_height là vị trí độ cao của threats xuất hiện
		{
			rand_y = (SCREEN_HEIGHT - Under_limit) * 0, 3;
		}
		rect_.y = rand_y;
	}
}

void ThreatsObject::HandleInputAction(SDL_Event events)
{
	
}

void ThreatsObject::ResetThreat(const int& x_boder)
{
	rect_.x = x_boder;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - Under_limit) //0> screen_height là vị trí độ cao của threats xuất hiện
	{
		rand_y = (SCREEN_HEIGHT - Under_limit) * 0, 3;
	}
	rect_.y = rand_y;

	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet) //p_bullet1=NULL
		{
			ResetBullet(p_bullet);
		}
	}
}


void ThreatsObject::ResetBullet(BulletObject* p_bullet)
{
	p_bullet->setRect(rect_.x, rect_.y + rect_.h * 0.5);
}