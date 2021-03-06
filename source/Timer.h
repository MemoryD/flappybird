/*********计时器***************/ 

#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class Timer{
	private:
		int startTicks;															// 计时开始时的时间 
		int pausedTicks;														// 暂停时的时间 
		bool paused;															// 是否暂停 
		bool started;															// 是否开始计时 
	public:
		Timer();																// 构造函数 
		void start();															// 开始计时 
		void stop();															// 停止计时 
		void pause();															// 暂停计时 
		void unpause();															// 恢复计时 
		int get_ticks();														// 获得计时开始到现在过了多少时间 
		bool is_started();														// 是否开始 
		bool is_paused();														// 是否暂停 
};

//构造 
Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

//开始计时 
void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();												// 获得当前时间 
}

//停止计时 
void Timer::stop()
{
	started = false;
	paused = false;
}

//获得计时开始到现在过了多长时间 
int Timer::get_ticks()
{
	if( started == true )														// 若已开始计时 
	{
		if( paused == true )													// 若暂停，返回暂停时的时间 
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;									// 否则返回当前时间开始时时间 
		}
	}
	
	return 0;
}

//暂停计时 
void Timer::pause()
{
	if( ( started == true ) && ( paused == false ) )
	{
		paused = true;
		
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

//恢复计时 
void Timer::unpause()
{
	if( paused == true )
	{
		paused = false;
		
		startTicks = SDL_GetTicks() - pausedTicks;
		
		pausedTicks = 0;
	}
}

bool Timer::is_started()
{
    return started;    
}
 
bool Timer::is_paused()
{
    return paused;    
}

#endif
