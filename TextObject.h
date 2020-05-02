
#ifndef TEXTOBJECT_H_
#define TEXTOBJECT_H_
#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>
class TextObject:public BaseOBject
{
public:

	enum TextColor
	{
	Red_text = 0,
	White_Text = 1,
	
	};
	TextObject();
	~TextObject();

	void SetText(const std::string& text) { str_val_ = text; }
	void SetColorText(const int& type);
	void CreateGameText(TTF_Font* font, SDL_Surface* des);

private:
	std::string str_val_;
	SDL_Color text_color_;

};


#endif // !TEXTOBJECT_H_
