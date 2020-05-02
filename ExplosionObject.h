#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include"CommonFuncion.h"
#include"BaseObject.h"

const int exp_width =165;
const int exp_height=165;

class ExplosionObject:public BaseOBject
{
public:
	ExplosionObject();
	~ExplosionObject();

	void setclip(); //set vi trí hình ảnh vụ nổ
	void setframe(const int& frame) { frame_ = frame; }

	void ShowExplosion(SDL_Surface* des);
private:
	int frame_;
	SDL_Rect clip_[4]; // array vi tri xuat hien hinh ảnh nổ

};

#endif // !EXPLOSION_H_
