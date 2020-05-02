#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_
#include "BaseObject.h"
#include "BulletObject.h"
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

	void set_bullet_list(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; }
	std::vector<BulletObject*> Get_bullet_list() const {return p_bullet_list_; }

	void InitBullet(BulletObject* p_bullet);
	void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_litmit, const int& speedbullet);

	void ResetThreat(const int& x_boder);
	void ResetBullet(BulletObject* p_bullet);

private:
	int val_x;
	int val_y;

	std::vector<BulletObject*> p_bullet_list_;
};


#endif 