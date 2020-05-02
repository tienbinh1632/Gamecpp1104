 
#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{

}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::setclip()
{
    clip_[0].x = 0;
    clip_[0].y = 0;
    clip_[0].w = exp_width;
    clip_[0].h = exp_height;

    clip_[1].x = exp_width;
    clip_[1].y = 0;
    clip_[1].w = exp_width;
    clip_[1].h = exp_height;

    clip_[2].x = exp_width * 2;
    clip_[2].y = 0;
    clip_[2].w = exp_width;
    clip_[2].h = exp_height;

    clip_[3].x = exp_width * 3;
    clip_[3].y = 0;
    clip_[3].w = exp_width;
    clip_[3].h = exp_height;

}



void ExplosionObject::ShowExplosion(SDL_Surface* des)
{
    if (frame_ >= 4)
    {
        frame_ = 0;
    }

    SDLCommonFuncion::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);

}