
#ifndef PLAYERPOWER_H_
#define PLAYERPOWER_H_
#include "BaseObject.h"
#include <vector>

class PlayerPower:public BaseOBject
{
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& number) { number_ = number; }
	void Addpos(const int& xpos); //add số mạng lên screen tại vị trí xpos
	void Render(SDL_Surface* des);
	void Init();
	void Decrease();

private:
	int number_; //số mạng
	std::vector<int> pos_list; //list mạng;
};

#endif // !PLAYERPOWER_H_

