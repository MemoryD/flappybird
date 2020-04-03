#include "game.h"
#include <stdio.h>
#include "pipe.h"

class Bird{
	private:
		int score;
		int current_FPS;
		int up_speed;
		int is_down;
		int status;
		int body_type;
		bool end;
		bool start;
		int endTime;
		int land_dist;
		int bg_dist;
		int day_time;
		Timer fps;
		SDL_Surface *bird0[2];
		SDL_Surface *bird0_down;
		SDL_Surface *bg[2];
		SDL_Surface *land;
		SDL_Surface *gg;
		SDL_Rect bird_offset;
		SDL_Rect bird_clip[3][3];
		Pipe *pipe[2];
	public:
		Bird();
		bool handInput( const SDL_Event &event );
		void show();
		void show_score();
		void turn_down();
		void move();
		bool isEnd();
		void gameRun();
		void controlFps();
};

Bird::Bird()
{
	score = 0;
	current_FPS = 0;
	status = 1;
	body_type = LEVEL;
	up_speed = -1;
	is_down = 0;
	day_time = 1;
	end = false;
	endTime = 500;
	land_dist = 0;
	bg_dist = -13;
	fps.start();
	bird_offset.x = START_X;
	bird_offset.y = START_Y;
	bird_offset.w = PIC_SIZE;
	bird_offset.h = PIC_SIZE;
	pipe[0] = new Pipe( 2 * SCREEN_WIDTH - INTERVAL_X);
	pipe[1] = new Pipe( 2 * SCREEN_WIDTH );
	
	bird0[0] = load_image("..\\pic\\bird0.png",WHITE_KEY);
	bird0[1] = load_image("..\\pic\\bird0_down.png",WHITE_KEY);
	bg[0] = load_image("..\\pic\\bg_day.png");
	bg[1] = load_image("..\\pic\\bg_night.png");
	land = load_image("..\\pic\\land.png");
	gg = load_image("..\\pic\\game_over.png");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			bird_clip[i][j].x = i * PIC_SIZE;
			bird_clip[i][j].y = j * PIC_SIZE;
			bird_clip[i][j].w = PIC_SIZE;
			bird_clip[i][j].h = PIC_SIZE;
		}
	}
}

void Bird::show()
{
	apply_surface(bg_dist, 0, bg[day_time], screen);
	apply_surface(bg_dist + BG_WIDTH, 0, bg[day_time], screen);
	
	pipe[0]->show();
	pipe[1]->show();
	
	apply_surface(land_dist, GAME_HEIGHT, land, screen);
	SDL_BlitSurface(bird0[is_down], &bird_clip[status][body_type], screen, &bird_offset);
	
	if( endTime < 480)
	{
		apply_surface( ( SCREEN_WIDTH - gg->w ) / 2, 150, gg, screen);
	}
	
	bg_dist = bg_dist - 1 <= -BG_WIDTH ? 0 : bg_dist - 1;
	land_dist = land_dist - 2 <= -48 ? 0 : land_dist - 2;
	SDL_Flip( screen );   
}

bool Bird::handInput( const SDL_Event &event )
{
	if( !end && event.type == SDL_MOUSEBUTTONDOWN )
	{
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			is_down = 0;
			status = UP;
			body_type = LEVEL;
			up_speed = UP_SPEED;
		}
	}
}
void Bird::turn_down()
{
	is_down = 1;
	status = 0;
	body_type = 0;
	if( bird_offset.y + 39 < GAME_HEIGHT )
		bird_offset.y += 2 * DOWN_SPEED;
	else
		endTime = 0;
}

void Bird::move()
{
	if( endTime < 500 ) 
	{
		turn_down();
		return;	
	}
	
	pipe[0]->move();
	pipe[1]->move(); 
	for(int i = 0; i <2; i++)
	{
		if( pipe[i]->collison(bird_offset) )
		{
			pipe[ (i+1) %2 ]->unmove();
			pipe[i]->unmove();
			end = true;
			SDL_Delay( 200 );
		}
	}
	
	if( up_speed >= -8 )
	{
		up_speed--;
		if( up_speed >= 0 )
		{
			bird_offset.y -= up_speed;
		}
	}
	else if( up_speed >= -42 )
	{
		up_speed--;
		
		if( up_speed <= -30 )
			status = DOWN;
		else if( up_speed <= -16 )
			status = LEVEL;
		bird_offset.y += DOWN_SPEED;
	}
	else
	{
		is_down = 1;
		status = 0;
		body_type = 0;
		bird_offset.y += 2 * DOWN_SPEED;
	}
	
	if( bird_offset.y + 39 > GAME_HEIGHT )
	{
		end = true;
	}
}

bool Bird::isEnd()
{
	if( end )
	{
		endTime--;
	}
	return endTime <= 0;
}

void Bird::gameRun()
{
	move();
	show();
	controlFps();
}

void Bird::controlFps()
{
	if( fps.get_ticks() < 1000 / FPS )
    {
        SDL_Delay( ( 1000 / FPS ) - fps.get_ticks() );
    }
    fps.start();
    current_FPS = (current_FPS + 1) % FPS;
    
    if( current_FPS % 4 == 0 )
    {
    	body_type = (body_type + 1) % 3;
	}
}

int main(int argc, char *args[])
{
	freopen("bug.txt","w",stdout);
	
	init();
	srand(unsigned(time(NULL)));
	
	bool quit = false;
	SDL_Event event;
	
	
	while( !quit )
	{
		Bird bird;
		
		while( !bird.isEnd() )
		{
			if( SDL_PollEvent( &event ))											// 若有待处理的事件 
			{
				
				if( event.type == SDL_QUIT )										// 若叉掉窗口 
				{
					quit = true;													// 则退出 
					break;
				}
				bird.handInput( event );
			}
			
			bird.gameRun();
		}
	}
	
	return 0;
}
