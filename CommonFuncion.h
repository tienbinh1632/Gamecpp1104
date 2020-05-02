//funcion tổng 

#pragma once

#ifndef COMMONFUNCION_H_
#define COMMONFUNCION_H_

#include <Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

const int BKG_WIDTH = 4800;
const int BKG_HEIGHT = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_Threat = 3; //số lượng threats tối đa xuất hiện trên màn hình
const int Under_limit = 200;// limit from bottom screen to threat and main move
const int Ga_failed = -1;
const int SizeText = 20;

//biến toàn cục 
static SDL_Surface* g_screen = NULL;		//con trỏ màn hình
static SDL_Surface* g_bkground = NULL;		//con trỏ load ảnh
static SDL_Event g_even;					//biến load sự kiện

static Mix_Chunk* g_sound_bullet[2]; //sound of bullet laser and sphere;
static Mix_Chunk* exp_sound_exp[2];//sound of explosion main;
static TTF_Font* g_font_text = NULL; //text


//hàm chung
namespace SDLCommonFuncion
{
	SDL_Surface* LoadImage(std::string file_path); //hàm load ảnh
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x,int y);//hàm up ảnh lên background
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);//hàm check va chạm
	void ClearnUp(); //hàm giải phóng chương trình

	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip,int x, int y);//funcion up image explosion to background
}



#endif // !COMMONFUNCION_H_
