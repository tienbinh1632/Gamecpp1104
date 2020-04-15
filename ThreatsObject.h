#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>


#define threats_width 80
#define threats_height 33

class ThreatsObject : public BaseOBject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void HandleMove(const int& x_boder, const int& y_boder);
	void HandleInputAction(SDL_Event events);

	void setval_x(const int& x_val) { val_x = x_val; }
	void setval_y(const int& y_val) { val_y = y_val; }

	int getval_x() const { return val_x; }
	int getval_y() const { return val_y; }

	void set_amo_list(std::vector<AmoObject*> amo_list) { p_amo_list_ = amo_list; }
	std::vector<AmoObject*> Get_amo_list() const {return p_amo_list_; }

	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_litmit);

private:
	int val_x;
	int val_y;

	std::vector<AmoObject*> p_amo_list_;
};


#endif 