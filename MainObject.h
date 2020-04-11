
#ifndef MAIN_OBJECT_H_H
#define  MAIN_OBJECT_H_H
#include "CommonFuncion.h"
#include "BaseObject.h"

#define Main_Width 80
#define Main_Height 46

class MainObject: public BaseOBject
{
public:
	MainObject();
	~MainObject();

	void HandleMove(); 


private:
	int x_val_;
	int y_val_;
};









#endif // !MAIN_OBJECT_H_H
