
#ifndef MAIN_OBJECT_H_H
#define  MAIN_OBJECT_H_H
#include "CommonFuncion.h"
#include "BaseObject.h"
#include <vector>
#include "BulletObject.h"

#define Main_Width 77
#define Main_Height 52

class MainObject: public BaseOBject
{
public:
	MainObject();
	~MainObject();


	void HandleInputAction(SDL_Event events,Mix_Chunk* Bullet_sound[2]); //hàm sử lý sự kiện bàn phím
	void HandleMove(); //sau khi load giá trị khi sử lý sự kiện thì thực hiện thay đổi vị trí của mainobject

	void MakeBullet(SDL_Surface* des);//hàm xử lý đạn bắn

	void SetBulletList(std::vector<BulletObject*> list_bullet) { p_list_bullet_ = list_bullet; }
	std::vector<BulletObject*> GetBulletList() const { return p_list_bullet_; }
	void RemoveBullet(const int& idx); //funcion delele bullet of main


private:
	int x_val_;
	int y_val_;

	std::vector<BulletObject* > p_list_bullet_; //list trường đạn bắn
};









#endif // !MAIN_OBJECT_H_H
