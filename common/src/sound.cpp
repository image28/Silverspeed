#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

int playSFX(Mix_Chunk *sound, int *channels)
{
	if(Mix_PlayChannel(-1, sound, 0)==-1) 
	{
		printf("Mix_PlayChannel: %s\n",Mix_GetError());
		if ( *(channels) < 64 )
		{
			printf("Trying to add a new channel\n");
			*(channels)=*(channels)+1;    
			Mix_AllocateChannels(*(channels));
			if(Mix_PlayChannel(-1, sound, 0)==-1) 
			{
				printf("Mix_PlayChannel: %s\n",Mix_GetError());
				printf("Allocating a new channel didn't help");
			}
		}
	}
	return(0);
}
