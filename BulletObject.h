#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
#include "BaseObject.h"

#define laser_Width 35
#define laser_Height 5
#define sphere_Width 10
#define sphere_Height 10

class BulletObject :public BaseOBject
{
public:
	enum Bullet //các kiểu đạn
	{
		None = 0,
		Laser = 1,
		Sphere = 2
	};
	BulletObject();
	~BulletObject();

	void HandleInputAction(SDL_Event events, SDL_Rect rect_obj); //hàm sử lý sự kiện 
	void HandleMove(const int x_boder, const int y_boder); //hàm di chuyển của đạn

	void HandleMoveRightToLeft();
	unsigned int get_bullet_type() const { return bullet_type_; }
	void set_bullet_type(const int& bullet_type) { bullet_type_ = bullet_type; }

	bool get_is_move() const { return is_Bullet; }
	void set_is_move(bool is_move) { is_Bullet = is_move; }

	void SetWidthHeight(const int& width, const int& height) { rect_.w = width, rect_.h = height; }
	//hàm cài đặt kick thước cho đạn.vì có hai loại đạn nên kick thước khác nhau.
	//Còn mianobject chỉ có một nên k có hàm set kick thước vì kick thước k thay đổi là = mainWidth và mainHeight bằng kick thước trong hàm khởi tạo
	void set_x_val(const int& xval) { x_val_ = xval; }
	void set_y_val(const int& yval) { y_val_ = yval; }

	int get_xval() const { return x_val_; }
	int get_yval() const { return y_val_; }
private:
	int x_val_; //speed bullet
	int y_val_; //chưa dùng
	bool is_Bullet; //để kiểm tra xem có cho di chuyển k
	unsigned int bullet_type_; //kiểu đạn 
};




#endif // !BULLET_OBJECT_H_
