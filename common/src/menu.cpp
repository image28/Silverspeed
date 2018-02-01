#include <SDL/SDL.h>
#ifdef _WIN32 
	#include <windows.h>
#endif
#include "../include/container.h"
#include "../include/draw.h"
#include "../include/config.h"
#include "../include/path.h"
#include <SDL/SDL_mixer.h>
#ifdef _WIN32
#else
	#include "../include/screenshot.h"
#endif
#include <GL/gl.h>
#include <GL/glu.h>



int gameMenu(struct container *screen, GLuint *menuTexture, int *menuW, int *menuH, int pos, int status)
{
	int winPos=screen->image->h/2-*(menuH+9)/2;
	// draw title

	if ( status == 1 )
	{
		draw(screen,9,menuTexture,screen->image->w/2-*(menuW+9)/2-10,winPos,*(menuW+9),*(menuH+9));

		if ( pos == 0 )
		{ 
			// draw resume game highlighted
			draw(screen,0,menuTexture,312,winPos+40,*(menuW),*(menuH));
		}else{
			// draw resume game
			draw(screen,1,menuTexture,312,winPos+40,*(menuW+1),*(menuH+1));
		}

		if ( pos == 1 )
		{
			// draw new game highlighted
			draw(screen,2,menuTexture,312,winPos+140,*(menuW+2),*(menuH+2));
		}else{
		// 	// draw new game
			draw(screen,3,menuTexture,312,winPos+140,*(menuW+3),*(menuH+3));
		}

		if ( pos == 2 )
		{
			// draw options highlighted
			draw(screen,4,menuTexture,312,winPos+240,*(menuW+4),*(menuH+4));
		}else{
			// draw options
			draw(screen,5,menuTexture,312,winPos+240,*(menuW+5),*(menuH+5));
		}

		if ( pos == 3 )
		{
			// draw quit game highlighted
			draw(screen,6,menuTexture,312,winPos+340,*(menuW+6),*(menuH+6));
		}else{
			// draw quit game
			draw(screen,7,menuTexture,312,winPos+340,*(menuW+7),*(menuH+7));
		}
	}else{
		draw(screen,8,menuTexture,0,0,*(menuW+8),*(menuH+8));
		draw(screen,9,menuTexture,screen->image->w/2-*(menuW+9)/2-10,winPos,*(menuW+9),*(menuH+9));

		if ( pos == 0 )
		{
			// draw new game highlighted
			draw(screen,2,menuTexture,312,winPos+80,*(menuW+2),*(menuH+2));
		}else{
			// draw new game
			draw(screen,3,menuTexture,312,winPos+80,*(menuW+3),*(menuH+3));
		}

		if ( pos == 1 )
		{
			// draw options highlighted
			draw(screen,4,menuTexture,312,winPos+180,*(menuW+4),*(menuH+4));
		}else{
			// draw options
			draw(screen,5,menuTexture,312,winPos+180,*(menuW+5),*(menuH+5));
		}

		if ( pos == 2 )
		{
			// draw quit game highlighted
			draw(screen,6,menuTexture,312,winPos+280,*(menuW+6),*(menuH+6));
		}else{
			// draw quit game	
			draw(screen,7,menuTexture,312,winPos+280,*(menuW+7),*(menuH+7));
		}
	}
return(0);
}

int gameEvent(struct container *screen, int *screenshot, SDL_Event event, int *menu, int *keydown, int *clicked, int *status, int first, int *power, int *newlevel,int *back, struct coords *pBulletArea, int *pBulletStart, int *pBulletDist, int *pBulletType, int *bulletCount, struct spriteGroup *player, int *shipX, int *shipY, int *w, int *h, int *quit)
{
	char outfile[1000];
	int f=0;

	switch( event.type ) 
	{
		case SDL_KEYDOWN:
			*(keydown)=1;
		break;

		case SDL_KEYUP:
			if ( *(keydown) )
			{

				if ( event.key.keysym.sym == SDLK_ESCAPE )
				{
					//quit=1;
					*(menu)=1;
					*(status)=1;
				}
				#ifdef CHEAT
					if ( event.key.keysym.sym == SDLK_p )
					{
						if ( *(power) < 3 )
						{
							*(power)=*(power)+1;
						}else{
							*(power)=0;
						}
					}else if ( event.key.keysym.sym == SDLK_l )
					{
						*(back)=10;
						*(newlevel)=1;
					}else if ( event.key.keysym.sym == SDLK_b )
					{
						*(back)=10;
					}
				#endif
			}
		break;

		case SDL_MOUSEMOTION:

			*(shipX)=event.motion.x-(*(w+0)/2);
			*(shipY)=event.motion.y-(*(h+0)/2);

		break;

		case SDL_MOUSEBUTTONDOWN:

			if ( event.button.button == 1 )
			{
				*(clicked)=1;
			}
		break;

		case SDL_MOUSEBUTTONUP:
			if ( *(clicked) == 1 )
			{
				
				for(f=0;f<player->part[*(power)].firing;f++)
				{
					
					//eBulletHold[d][f]--;
					//if ( eBulletHold[d][f] == 0 )
					//{
						
						//eBulletHold[d][f]=eData[enemyType[d]].part[l].fireinterval[f];
						pBulletArea[*(bulletCount)].w=*(shipX)+player->part[*(power)].firex1[f];
						pBulletArea[*(bulletCount)].h=*(shipY)+player->part[*(power)].firey1[f];
						pBulletArea[*(bulletCount)].x=*(shipX)+player->part[*(power)].firex2[f];
						pBulletArea[*(bulletCount)].y=*(shipY)+player->part[*(power)].firey2[f];
						*(pBulletType+*(bulletCount))=player->part[*(power)].firetex[f];
						*(pBulletStart+*(bulletCount))=0;
						*(pBulletDist+*(bulletCount))=0;
						multiplyPath(screen,&pBulletArea[*(bulletCount)]);
						*(bulletCount)=*(bulletCount)+1;

						
					//}
				}
				
				// get mouse x,y coords
				//mousex=event.button.x;
				//mousey=event.button.y;

				*(clicked)=0;
			}


		break;

		case SDL_QUIT: 
			*(quit)=1;
		break;
	}
	return(0);
}

int gameMenuEvent(SDL_Event event, int *menu, int *status, int *pos, int *clicked, int *keydown, int *quit, int *newgame)
{
	switch( event.type ) 
	{
		case SDL_MOUSEMOTION:
			if ( *(status) == 0 )
			{
				if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 222 ) && ( event.motion.y < 322 ) )
				{
					*(pos)=0;
				}else if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 322 ) && ( event.motion.y < 422 ) )
				{
					*(pos)=1;
				}else if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 422 ) && ( event.motion.y < 522 ) )
				{
					*(pos)=2;
				}
			}else{
				if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 182 ) && ( event.motion.y < 282 ) )
				{
					*(pos)=0;
				}else if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 282 ) && ( event.motion.y < 382 ) )
				{
					*(pos)=1;
				}else if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 382 ) && ( event.motion.y < 482 ) )
				{
					*(pos)=2;
				}else if (( event.motion.x > 312 ) && ( event.motion.x < 712 ) && ( event.motion.y > 482 ) && ( event.motion.y < 582 ) )
				{
					*(pos)=3;
				}
			}

		break;

		case SDL_MOUSEBUTTONDOWN:

			if ( event.button.button == 1 )
			{
				*(clicked)=1;
			}
		break;

		case SDL_MOUSEBUTTONUP:
			if ( *(clicked) == 1 )
			{

				if ( *(status) == 0 )
				{
					if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 222 ) && ( event.button.y < 322 ) )
					{
						*(newgame)=1;
						*(menu)=0;
					}else if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 322 ) && ( event.button.y < 422 ) )
					{
						*(menu)=2;
					}else if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 422 ) && ( event.button.y < 522 ) )
					{
						*(quit)=1;
					}
				}else{
					if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 182 ) && ( event.button.y < 282 ) )
					{
						*(menu)=0;
					}else if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 282 ) && ( event.button.y < 382 ) )
					{
						*(newgame)=1;
						*(menu)=0;
					}else if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 382 ) && ( event.button.y < 482 ) )
					{
						*(menu)=2;
					}else if (( event.button.x > 312 ) && ( event.button.x < 712 ) && ( event.button.y > 482 ) && ( event.button.y < 582 ) )
					{
						*(quit)=1;
					}
				}

			}
		break;

		case SDL_KEYDOWN:
			*(keydown)=1;
		break;

		case SDL_KEYUP:
			if ( *(keydown) == 1 )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_ESCAPE:
						if ( *(status) == 1 )
							*(menu)=0;
					break;

					case SDLK_RETURN:
						if ( *(status) == 0 )
						{
							if ( *(menu) == 1 )
							{
								if ( *(pos) == 0 )
								{
									// Start a new game
									*(menu)=0;
									*(newgame)=1;
								}else if ( *(pos) == 1 ){
									// Enter Options Menu									
									*(menu)=2;
								}else{
									// Quit Game
									*(quit)=1;
								}
							}
						}else{
							if ( *(pos) == 0 )
							{
								// Resume game
								*(menu)=0;
							}else if ( *(pos) == 1 ){
								// New Game	
								*(newgame)=1;
								*(menu)=0;
							}else if ( *(pos) == 2 ) {
								// Options Menu
								*(menu)=2;

							}else{
								// Quit Game
								*(quit)=1;
							}
						}
					break;

					case SDLK_UP:
						if ( *(status) == 0 )

						{
							if ( *(menu) == 1 ) // Title Game Menu
							{
								if ( *(pos) == 0 )
								{
									*(pos)=2;
								}else{
									*(pos)=*(pos)-1;
								}
							}else{ // Options Menu
			
							}
						}else{
							// In Game Menu 
							if ( *(pos) == 0 )
							{
								*(pos)=3;
							}else{
								*(pos)=*(pos)-1;
							}
						}
					break;
		
					case SDLK_DOWN:
						if ( *(status) == 0 )
						{
							if ( *(menu) == 1 ) // Title Game Menu
							{
								if ( *(pos) == 2 )
								{
									*(pos)=0;
								}else{
									*(pos)=*(pos)+1;
								}
							}else{ // Options Menu

							}
						}else{
							// In Game Menu
							if ( *(pos) == 3 )
							{
								*(pos)=0;
							}else{
								*(pos)=*(pos)+1;
							}
						}
					break;
				}
			}
			*(keydown)=0;
		break;

		case SDL_QUIT: 
			*(quit)=1;
		break;
	}
	return(0);
}

int optionMenu(struct container *screen, GLuint *optionsTexture, int *optionsW, int *optionsH, int optionsPos, int difficulty, int windowed,  int soundVol, int musicVol, int status)
{
	float musicPos=0;
	float soundPos=0;

	if ( ! status )
		draw(screen,16,optionsTexture,0,0,*(optionsW+16),*(optionsH+16));

	draw(screen,17,optionsTexture,screen->image->w/2-*(optionsW+17)/2-10,screen->image->h/2-*(optionsH+17)/2,*(optionsW+17),*(optionsH+17));

	if ( optionsPos == 0 )
	{ 
		// draw difficulty highlighted
		draw(screen,0,optionsTexture,200,240-50,*(optionsW),*(optionsH));
		// draw mode
		draw(screen,8+(difficulty*2),optionsTexture,*(optionsW)+200,240-50,*(optionsW+(8+(difficulty*2))),*(optionsH+(8+(difficulty*2))));
	}else{
		// draw difficulty game
		draw(screen,1,optionsTexture,200,240-50,*(optionsW+1),*(optionsH+1));
		// draw mode
		draw(screen,9+(difficulty*2),optionsTexture,*(optionsW+1)+200,240-50,*(optionsW+(9+(difficulty*2))),*(optionsH+(9+(difficulty*2))));
	
	}

	if ( optionsPos == 1 )
	{
		// draw fullscreen highlighted
		draw(screen,18,optionsTexture,200,290,*(optionsW+18),*(optionsH+18));
		// draw on/off highlighted
		draw(screen,20+(windowed*2),optionsTexture,*(optionsW+1)+200,290,*(optionsW+(20+(windowed*2))),*(optionsH+(20+(windowed*2))));
	}else{
		// draw fullscreen
		draw(screen,19,optionsTexture,200,290,*(optionsW+19),*(optionsH+19));
		// draw on/off
		draw(screen,21+(windowed*2),optionsTexture,*(optionsW+1)+200,290,*(optionsW+(21+(windowed*2))),*(optionsH+(21+(windowed*2))));

/*
		// draw sound highlighted
		draw(screen,2,optionsTexture,200,340-50,*(optionsW+2),*(optionsH+2));
		// draw slider bar
		draw(screen,14,optionsTexture,*(optionsW+2)+200,340-50,*(optionsW+14),*(optionsH+14));
		// draw slider
		soundPos=((float)soundVol*((float)*(optionsW+14)/100))-15;
		draw(screen,15,optionsTexture,*(optionsW+2)+200+soundPos,340-50,*(optionsW+15),*(optionsH+15));
	
	}else{
	 	// draw sound
		draw(screen,3,optionsTexture,200,340-50,*(optionsW+3),*(optionsH+3));
		// draw slider bar
		draw(screen,14,optionsTexture,*(optionsW+3)+200,340-50,*(optionsW+14),*(optionsH+14));
		// draw slider
		soundPos=((float)soundVol*((float)*(optionsW+14)/100))-15;
		draw(screen,15,optionsTexture,*(optionsW+3)+200+soundPos,340-50,*(optionsW+15),*(optionsH+15));
*/
	}

	if ( optionsPos == 2 )
	{
		// draw music highlighted
		draw(screen,4,optionsTexture,200,440-50,*(optionsW+4),*(optionsH+4));
		// draw slider bar
		draw(screen,14,optionsTexture,*(optionsW+4)+200,440-50,*(optionsW+14),*(optionsH+14));
		// draw slider
		musicPos=((float)musicVol*((float)*(optionsW+14)/100))-15;
		draw(screen,15,optionsTexture,*(optionsW+4)+200+musicPos,440-50,*(optionsW+15),*(optionsH+15));
	
	}else{
		// draw music
		draw(screen,5,optionsTexture,200,440-50,*(optionsW+5),*(optionsH+5));
		// draw slider bar
		//printf("%d %d %d %d\n",*(optionsW+5)+200,390,*(optionsW+14),*(optionsH+14));
		draw(screen,14,optionsTexture,*(optionsW+5)+200,440-50,*(optionsW+14),*(optionsH+14));
		// draw slider
		//musicPos=((float)musicVol*((float)*(optionsW+14)/100))-15;
		musicPos=((float)musicVol*((float)*(optionsW+14)/100))-15;
		draw(screen,15,optionsTexture,*(optionsW+5)+200+musicPos,440-50,*(optionsW+15),*(optionsH+15));
	
	}

	if ( optionsPos == 3 )
	{
		// draw back highlighted
		draw(screen,6,optionsTexture,300,540-50,*(optionsW+6),*(optionsH+6));
	}else{
		// draw back 
		draw(screen,7,optionsTexture,300,540-50,*(optionsW+7),*(optionsH+7));
	}

	return(0);
}

int optionMenuEvent(struct container *screen, SDL_Event event, int *windowed, int *menu, int *status, int *optPos, int *clicked, int *keydown, int *difficulty, int *soundVol, int *musicVol)
{
	switch( event.type ) 
	{
		case SDL_MOUSEMOTION:

			if (( event.motion.x > 240 ) && ( event.motion.x < 712 ) && ( event.motion.y > 190 ) && ( event.motion.y < 290 ) )
			{
				*(optPos)=0;
			}else if (( event.motion.x > 240 ) && ( event.motion.x < 712 ) && ( event.motion.y > 290 ) && ( event.motion.y < 390) )
			{
				*(optPos)=1;
			}else if (( event.motion.x > 240 ) && ( event.motion.x < 712 ) && ( event.motion.y > 390 ) && ( event.motion.y < 490 ) )
			{
				*(optPos)=2;
			}else if (( event.motion.x > 160 ) && ( event.motion.x < 712 ) && ( event.motion.y > 490 ) && ( event.motion.y < 590 ) )
			{
				*(optPos)=3;
			}

		break;

		case SDL_MOUSEBUTTONDOWN:

			if ( event.button.button == 1 )
			{
				*(clicked)=1;
			}
		break;

		case SDL_MOUSEBUTTONUP:
			if ( *(clicked) == 1 )
			{


				if (( event.button.x > 240 ) && ( event.button.x < 712 ) && ( event.button.y > 190 ) && ( event.button.y < 290 ) )
				{
					// Difficulty Mode
					*(difficulty)=*(difficulty)+1;
					if ( *(difficulty) == 3 )
						*(difficulty)=0;

				}else if (( event.button.x > 240 ) && ( event.button.x < 780 ) && ( event.button.y > 290 ) && ( event.button.y < 390 ) )
				{
					// Sound Volume
					//*(soundVol)=((float)event.button.x-600)*((float)100/180);
					*(windowed)=1;
				}else if (( event.button.x > 600 ) && ( event.button.x < 780 ) && ( event.button.y > 390 ) && ( event.button.y < 486 ) )
				{
					// Music Volume
					*(musicVol)=((float)event.button.x-600)*((float)100/180);
					Mix_VolumeMusic(*(musicVol));

				}else if (( event.button.x > 160 ) && ( event.button.x < 712 ) && ( event.button.y > 490 ) && ( event.button.y < 590 ) )
				{
					// Back to main menu
					*(menu)=1;
				}

			}
		break;

		case SDL_KEYDOWN:

			// could move music and sound adjustment here
			*(keydown)=1;
		break;

		case SDL_KEYUP:
			if ( *(keydown) == 1 )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_ESCAPE:
						if ( *(status) == 1 )
							*(menu)=0;
						else
							*(menu)=1;
					break;

					case SDLK_RETURN:
						if ( *(optPos) == 0 )
						{
							// Difficulty Mode
							*(difficulty)=*(difficulty)+1;
							if ( *(difficulty) == 3 )
								*(difficulty)=0;
						}else if ( *(optPos) == 1 ){
							// Sound Volume	

							*(windowed)=1;

							//if ( *(soundVol) < 100 )
							//	*(soundVol)=*(soundVol)+10;
						}else if ( *(optPos) == 2 ) {
							// Music Volume
							if ( *(musicVol) < 100 )
								*(musicVol)=*(musicVol)+10;
							Mix_VolumeMusic(*(musicVol));
						}else{
							// Back
							*(menu)=1;
						}
					break;

					case SDLK_RIGHT:
						if ( *(optPos) == 0 )
						{
							// Difficulty Mode
							if ( *(difficulty) < 2 )
								*(difficulty)=*(difficulty)+1;
						}
						else if ( *(optPos) == 2 )
						{
							// Music Volume
							if ( *(musicVol) < 100 )
								*(musicVol)=*(musicVol)+10;
							Mix_VolumeMusic(*(musicVol));

						}
					break;

					case SDLK_LEFT:
						if ( *(optPos) == 0 )
						{
							// Difficulty Mode
							if ( *(difficulty) > 0 )
								*(difficulty)=*(difficulty)-1;
						}
						else if ( *(optPos) == 2 )
						{
							// Music Volume
							if ( *(musicVol) > 0 )
								*(musicVol)=*(musicVol)-10;
							Mix_VolumeMusic(*(musicVol));

						}
					break;

					case SDLK_UP:
						if ( *(optPos) == 0 )
						{
							*(optPos)=3;
						}else{
							*(optPos)=*(optPos)-1;
						}
					break;
		
					case SDLK_DOWN:
						if ( *(optPos) == 3 )
						{
							*(optPos)=0;
						}else{
							*(optPos)=*(optPos)+1;
						}
					break;
				}
			}
			*(keydown)=0;
		break;

	}

	return(0);
}

