#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFuncion.h"

class BaseOBject
{
public:
	BaseOBject(); //hàm khởi tạo
	~BaseOBject(); //hàm hủy
	void Show(SDL_Surface* des); //hàm hiện ảnh nhân vật lên màn hình
	bool loadimg(const char* file_name); //kiểm tra nếu có ảnh nhân vật thì thay ảnh vào hàm Show().

	void setRect(const int& x,const int& y) {rect_.x = x; rect_.y = y;}
	SDL_Rect GetRect() const {return rect_;}
	SDL_Surface* GetObject() { return p_object_; }
protected:
	SDL_Surface* p_object_; //nguồn có thể là main,threat...
	SDL_Rect rect_; //kick thước x,y,w,h
};
 


#endif // !BASE_OBJECT_H_