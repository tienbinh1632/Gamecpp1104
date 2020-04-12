
#ifndef MAIN_OBJECT_H_H
#define  MAIN_OBJECT_H_H
#include "CommonFuncion.h"
#include "BaseObject.h"
#include <vector>
#include "AmoObject.h"

#define Main_Width 80
#define Main_Height 46

class MainObject: public BaseOBject
{
public:
	MainObject();
	~MainObject();


	void HandleInputAction(SDL_Event events); //hàm sử lý sự kiện bàn phím
	void HandleMove(); //sau khi load giá trị khi sử lý sự kiện thì thực hiện thay đổi vị trí của mainobject

	void SetAmoList(std::vector<AmoObject*> list_amo) { p_list_amo_ = list_amo; }
	std::vector<AmoObject*> GetAmoList() const { return p_list_amo_; }

private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject* > p_list_amo_; //list trường đạn bắn
};









#endif // !MAIN_OBJECT_H_H
