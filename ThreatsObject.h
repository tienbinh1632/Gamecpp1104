#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "BaseObject.h"

#define threats_width 80
#define threats_height 33

class ThreatsObject : public BaseOBject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void HandleMove(const int& x_boder, const int& y_boder);
	void HandleInputAction(SDL_Event events);

	void setval_x(const int& x_val) { val_x_ = x_val; }
	void setval_y(const int& y_val) { val_y_ = y_val; }

	int getval_x() const { return val_x_; }
	int getval_y() const { return val_y_; }


private:
	int val_x_;
	int val_y_;
};


#endif 