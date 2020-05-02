
#include "PlayerPower.h"

PlayerPower::PlayerPower()
{

}

PlayerPower::~PlayerPower()
{

}


void PlayerPower::Addpos(const int& xpos)
{
	pos_list.push_back(xpos); 
}

void PlayerPower::Render(SDL_Surface* des)
{
	if (number_ == pos_list.size())
	{
		for (int i = 0; i < pos_list.size(); i++)
		{
			rect_.x = pos_list.at(i);
			Show(des);
		}
	}
}

void PlayerPower::Init()
{
	loadimg("play_power.png");
	number_ = 3;
	if (pos_list.size() > 0)
	{
		pos_list.clear();
	}

	Addpos(20); //set vị trí xuất hiện ảnh mạng ở vị trí 20
	Addpos(60);//set vị trí xuất hiện ảnh mạng ở vị trí 60
	Addpos(100);//set vị trí xuất hiện ảnh mạng ở vị trí 100
}

void PlayerPower::Decrease()
{
	number_--;
	pos_list.pop_back();
}