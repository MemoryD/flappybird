#ifndef _GAME_H_ 
#define _GAME_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Timer.h"
#include <string>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 560;
const int SCREEN_BPP = 32;

const int START_X = 65;
const int START_Y = 300;

const int INTERVAL_X = 170;
const int INTERVAL_Y = 100;

const int GAME_HEIGHT = 460;

const int LAND_WIDTH = 336;
const int BG_WIDTH = 275;
const int PIPE_WIDTH = 52;

const int FPS = 48;

const int FLASH_TIME = 16;

const int PIC_SIZE = 48;
const int STEP = 3;

const int UP_SPEED = 10;
const int DOWN_SPEED = 3;

const int UP = 0;
const int LEVEL = 1;
const int DOWN = 2;

const int BLACK_KEY = 263172;												// 部分黑色背景的值 
const int WHITE_KEY = 16777215;												// 白色背景的值 

SDL_Surface *screen;

//载入图片，传入文件名 和 关键色，关键色即要屏蔽的背景色，默认为 0 
SDL_Surface *load_image( std::string filename ,int key = 0 )
{
    SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );

        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, key );
        }
    }

    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination , SDL_Rect *clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
    SDL_WM_SetCaption( "flappybird", "..\\pic\\bird.ico" );
    
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
    {
        return false;
    }
    
    

    return true;
}

int random( int min, int max )
{
	return rand() % ( max - min + 1 ) + min;
}

#endif
