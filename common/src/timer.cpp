#include <SDL/SDL.h>

int get_ticks(int startTicks)
{
	//Return the current time minus the start time
	return SDL_GetTicks() - startTicks;
}
