#include "game.h"

class Pipe{
	private:
		SDL_Surface *pipe[2];
		SDL_Rect clip[2];
	public:
		Pipe();
		void move();
		void show();
		bool collison( const SDL_Rect &box );
};

Pipe::Pipe()
{
	pipe[0] = load_image("pic\\pipe_up.png");
	pipe[1] = load_image("pic\\pipe_down.png");
}
