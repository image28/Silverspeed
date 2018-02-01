#include <SDL/SDL.h>
#include <GL/gl.h>
#include "../include/container.h"
#include "../include/draw.h"

int levelComplete(struct container *screen, int *pos, int *count, int money, int lives, int kills, int startLives, int enemiesTotal, GLuint *textures, int *texW, int *texH, GLuint *fontTexture, int *fontW, int *fontH)
{

	int curTime=0;
	char killsText[128];
	char cashText[128];
	char livesText[128];

	// draw screen background
	draw(screen,0,textures,screen->image->w/2-*(texW)/2-10,screen->image->h/2-*(texH)/2,*(texW),*(texH));
	

	switch(*(pos))
	{
		// Kills count
		case 0:
			if ( *(count) < ((float)100/(float)enemiesTotal)*kills )
			{
				*(count)=*(count)+1;
				kills=*(count);
				
			}else{
				*(count)=0;
				kills=((float)100/(float)enemiesTotal)*kills;
				*(pos)=*(pos)+1;
			}

			
			money=0;
			lives=0;
		break;

		// Money Collected
		case 1:
			
			if ( *(count) < money )
			{
				*(count)=*(count)+100;
				money=*(count);
			}else{
				*(count)=0;
				*(pos)=*(pos)+1;
			}

			kills=((float)100/(float)enemiesTotal)*kills;
			lives=0;

		break;
	
		// Lives Lost
		case 2:
			if ( startLives > lives )
			{
				if ( *(count) < startLives-lives )
				{
					*(count)=*(count)+1;
					lives=*(count);
				}else{
					*(count)=0;
					*(pos)=*(pos)+1;
				}
			}else{
				if ( *(count) < lives )
				{
					*(count)=*(count)+1;
					lives=*(count);
				}else{
					*(count)=0;
					*(pos)=*(pos)+1;
				}
			}	

			kills=((float)100/(float)enemiesTotal)*kills;

		break;

		// Score count complete
		default:
			

			kills=((float)100/(float)enemiesTotal)*kills;

	
		break;
	}

	draw(screen,1,textures,screen->image->w/2-*(texW)/2+40,screen->image->h/2-*(texH)/2+60,*(texW+1),*(texH+1));
	sprintf(killsText,"%d",kills);
	putText(screen, killsText,fontTexture,screen->image->w/2-*(texW)/2+40+*(texW+1),screen->image->h/2-*(texH)/2+100,fontW,fontH);
	draw(screen,2,textures,screen->image->w/2-*(texW)/2+40,screen->image->h/2-*(texH)/2+120,*(texW+2),*(texH+2));
	sprintf(cashText,"%d",money);
	putText(screen, cashText,fontTexture,screen->image->w/2-*(texW)/2+40+*(texW+2),screen->image->h/2-*(texH)/2+160,fontW,fontH);
	draw(screen,3,textures,screen->image->w/2-*(texW)/2+40,screen->image->h/2-*(texH)/2+180,*(texW+3),*(texH+3));
	sprintf(livesText,"%d",lives);
	putText(screen, livesText,fontTexture,screen->image->w/2-*(texW)/2+40+*(texW+3),screen->image->h/2-*(texH)/2+240,fontW,fontH);

}
