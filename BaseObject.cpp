#include "BaseObject.h"



BaseOBject::BaseOBject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;

}

BaseOBject::~BaseOBject()
{
	if (p_object_ != NULL)
		SDL_FreeSurface(p_object_);
}

bool  BaseOBject :: loadimg(const char* file_name) //kiểm tra và gán
{
	p_object_ = SDLCommonFuncion::LoadImage(file_name); //gán để thay vào hàm Show()
	if (p_object_==NULL)
	{
		return false;
	}
	return true; //ktra
}

void BaseOBject::Show(SDL_Surface* des)
{
	SDLCommonFuncion::ApplySurface(p_object_, des, rect_.x, rect_.y);
}