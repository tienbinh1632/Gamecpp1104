#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "BaseObject.h"

#define laser_Width 35
#define laser_Height 5
#define sphere_Width 10
#define sphere_Height 10

class AmoObject:public BaseOBject
{
public:
	enum Amo //các kiểu đạn
	{	None=0,
		Laser=1,
		Sphere=2
	};
	AmoObject();
	~AmoObject();

	void HandleInputAction(SDL_Event events, SDL_Rect rect_obj); //hàm sử lý sự kiện 
	void HandleMove(const int x_boder, const int y_boder); //hàm di chuyển của đạn

	void HandleMoveRightToLeft();
	unsigned int get_amo_type() const { return amo_type_; }
	void set_amo_type(const int& amo_type) { amo_type_ = amo_type; }

	bool get_is_move() const { return is_move_; }
	void set_is_move(bool is_move) {is_move_ = is_move;}

	void SetWidthHeight(const int& width, const int& height) { rect_.w = width, rect_.h = height; }
	//hàm cài đặt kick thước cho đạn.vì có hai loại đạn nên kick thước khác nhau.
	//Còn mianobject chỉ có một nên k có hàm set kick thước vì kick thước k thay đổi là = mainWidth và mainHeight bằng kick thước trong hàm khởi tạo
private:
	int x_val_;
	int y_val_;
	bool is_move_; //để kiểm tra xem có cho di chuyển k
	unsigned int amo_type_;
};




#endif // !AMO_OBJECT_H_
