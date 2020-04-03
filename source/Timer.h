/*********��ʱ��***************/ 

#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class Timer{
	private:
		int startTicks;															// ��ʱ��ʼʱ��ʱ�� 
		int pausedTicks;														// ��ͣʱ��ʱ�� 
		bool paused;															// �Ƿ���ͣ 
		bool started;															// �Ƿ�ʼ��ʱ 
	public:
		Timer();																// ���캯�� 
		void start();															// ��ʼ��ʱ 
		void stop();															// ֹͣ��ʱ 
		void pause();															// ��ͣ��ʱ 
		void unpause();															// �ָ���ʱ 
		int get_ticks();														// ��ü�ʱ��ʼ�����ڹ��˶���ʱ�� 
		bool is_started();														// �Ƿ�ʼ 
		bool is_paused();														// �Ƿ���ͣ 
};

//���� 
Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

//��ʼ��ʱ 
void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();												// ��õ�ǰʱ�� 
}

//ֹͣ��ʱ 
void Timer::stop()
{
	started = false;
	paused = false;
}

//��ü�ʱ��ʼ�����ڹ��˶೤ʱ�� 
int Timer::get_ticks()
{
	if( started == true )														// ���ѿ�ʼ��ʱ 
	{
		if( paused == true )													// ����ͣ��������ͣʱ��ʱ�� 
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;									// ���򷵻ص�ǰʱ�俪ʼʱʱ�� 
		}
	}
	
	return 0;
}

//��ͣ��ʱ 
void Timer::pause()
{
	if( ( started == true ) && ( paused == false ) )
	{
		paused = true;
		
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

//�ָ���ʱ 
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
