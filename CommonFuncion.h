//funcion tổng 

#pragma once

#ifndef COMMONFUNCION_H_
#define COMMONFUNCION_H_

#include <Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//biến toàn cục 
static SDL_Surface* g_screen = NULL;		//con trỏ màn hình
static SDL_Surface* g_bkground = NULL;		//con trỏ load ảnh
static SDL_Event g_even;					//biến load sự kiện


//hàm chung
namespace SDLCommonFuncion
{
	SDL_Surface* LoadImage(std::string file_path); //hàm load ảnh
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x,int y);//hàm up ảnh lên background
	void ClearnUp(); //hàm giải phóng chương trình
}



#endif // !COMMONFUNCION_H_
