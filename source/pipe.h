#ifndef __PIPE_H__
#define __PIPE_H_
 
#include "game.h"

struct offset{
	int x;
	int y;
};
class Pipe{
	private:
		SDL_Surface *pipe[2];
		offset box[2];
	public:
		Pipe(int x);
		void move();
		void unmove();
		void reset();
		void show();
		bool collison( SDL_Rect b );
};

Pipe::Pipe(int x)
{
	pipe[0] = load_image("..\\pic\\pipe_down.png");
	pipe[1] = load_image("..\\pic\\pipe_up.png");
	
	box[0].x = x;
	box[0].y = random(-280,0);
	box[1].x = x;
	box[1].y = box[0].y + INTERVAL_Y + pipe[0]->h;
}

void Pipe::reset()
{
	box[0].x = SCREEN_WIDTH;
	box[0].y = random(-280,0);
	box[1].x = SCREEN_WIDTH;
	box[1].y = box[0].y + INTERVAL_Y + pipe[0]->h;
}

void Pipe::move()
{
	box[0].x--;
	if( box[0].x <= -pipe[0]->w )
	{
		reset();
		return;
	}
	box[1].x--;
}

void Pipe::unmove()
{
	box[0].x++;
	box[1].x++;
}

void Pipe::show()
{
	apply_surface( box[0].x, box[0].y, pipe[0], screen );
	apply_surface( box[1].x, box[1].y, pipe[1], screen );
}

bool Pipe::collison( SDL_Rect b )
{
	b.x += 9;
	b.y += 9;
	b.w -= 18;
	b.h -= 18;
	if( ( b.x + b.w < box[1].x || b.y + b.h < box[1].y || b.x > box[1].x + pipe[1]->w) && ( b.x + b.w < box[0].x || b.y > box[0].y + pipe[0]->h || b.x > box[0].x + pipe[0]->w) )
	{
		return false;
	}
	return true;
} 
#endif
