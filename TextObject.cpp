
#include "TextObject.h"

TextObject::TextObject()
{
	rect_.x = 520;
	rect_.y = 50;
	text_color_.r = 255;
	text_color_.g = 255;
	text_color_.b = 255;
}

TextObject::~TextObject()
{

}

void TextObject::SetColorText(const int& type)
{
	if (type == Red_text)
	{
		SDL_Color color_red = { 255,0,0 };
		text_color_ = color_red;
	}

	else if (type == White_Text)
	{
		SDL_Color color_white = { 255,255,255 };
		text_color_ = color_white;
	}
	else
	{
		SDL_Color color_black = { 0,0,0 };
		text_color_ = color_black;
	}
}
void TextObject::CreateGameText(TTF_Font* font, SDL_Surface* des)
{
	//change text to surface then add to screen because duy nhất surface mới có thể add lên des(truyền vào là g_screen);
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}