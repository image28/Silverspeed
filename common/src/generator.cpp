#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/path.h"

int genorateDrops(int *drops, int *seed, int *seedDefault, int difficulty, int collisions, int *dropX, int *dropY, int *type ,int *enemyX, int *enemyY, int *collide, int *enemyHits )
{
	int random=0;
	int d=0;

	for(d=*(drops);d<collisions+*(drops);d++)
	{

		*(dropX+d)=*(enemyX+*(collide+(d-*(drops))))+20;
		*(dropY+d)=*(enemyY+*(collide+(d-*(drops))))+20;

		srand(time(0));
		random=rand()%*(seed);

		if ( *(seed) >= 30 )
		{
			*(seed)=*(seed)-1;
			*(type+d)=1;
		}else{
			if ( random == 0 )
			{
				if ( difficulty == 0 )
				{
					*(seed)=*(seedDefault);
				}else if ( difficulty == 1 ){
					*(seed)=*(seedDefault+1);
				}else{
					*(seed)=*(seedDefault+2);
				}
				*(type+d)=0;
			}else{
				*(type+d)=1;
				*(seed)=*(seed)-1;
			}
		}
		
	}

	*(drops)=*(drops)+collisions;
return(0);
}

int genorateEnemies(int *count, int *seed, int *seedDefault, int difficulty, int *type, int typeTotal, int backTotal, int *hits, int *hitsDefault,int *enemyX, int *enemyY, int *enemyW, int pos, int level)
{
	int random=0;

	srand(time(0));
	// given level and time
		// set enemy to be genorated type

	int interval=(backTotal/(typeTotal/2))+(typeTotal-(typeTotal/2)*2);

	*(type+*(count))=(pos/interval)*2;

	// genorate a random number between 0 and X
		// if 0 minus 1 from type
	if ( *(type+*(count)) < typeTotal-1 )
	{
		random=(rand()+*(count))%4;
		if ( ! random )
		{
			*(type+*(count))=*(type+*(count))+1;
		}
	}

	// pass the given enemies type seed to random
	random=(rand()+*(count))%*(seed+difficulty);

	if ( *(count) > 0 )
	{
		if ( *(enemyX+*(count)-1) < 960-*(enemyW+*(count)-1) )
		{	
			if ( random == 0 )
			{
				*(seed+difficulty)=*(seedDefault+difficulty);
				*(enemyY+*(count))=rand()%648;
				*(enemyX+*(count))=1024;
				*(hits+*(count))=*(hitsDefault+*(type+*(count))); // load value for enemy type from config file
				// if type equal zero hits equal one, if type equal one hits equal two, etc...
				*(count)=*(count)+1;
			}else{
				*(seed+difficulty)=*(seed+difficulty)-1;
			}
		}
	}else{
		if ( random == 0 )
		{
			*(seed+difficulty)=*(seedDefault+difficulty);
			*(enemyY+*(count))=rand()%648;
			*(enemyX+*(count))=1024;
			*(hits+*(count))=*(hitsDefault+*(type+*(count)));
			// if type equal zero hits equal one, if type equal one hits equal two, etc...
			*(count)=*(count)+1;
		}else{
			*(seed+difficulty)=*(seed+difficulty)-1;
		}
	}
	return(0);
}

int genorateEnemyBullets(int *count, int enemyCount, int *seed, int *seedDefault, int difficulty, int *enemyX, int *enemyY, int enemyW, int enemyH, struct coords *area)
{
	long random=0;
	int d=0;



	for(d=0;d<enemyCount;d++)
	{
		srand(time(0));
		random=rand()%*(seed);

		if ( *(count) > 0 )
		{
			if ( random == 0 )
			{
				if ( *(seed) < 50 )
				{
					if ( ( *( enemyX+d) > 0 ) && ( *(enemyX+d)+enemyW < 1024 ) )
					{
						if ( difficulty == 0 )
						{
							*(seed)=*(seedDefault);
						}else if ( difficulty == 1 )
						{
							*(seed)=*(seedDefault+1);
						}else{
							*(seed)=*(seedDefault+2);
						}
						area[*(count)].y=*(enemyY+d)+(enemyH/2);
						area[*(count)].x=*(enemyX+d)+(enemyW/2);
						*(count)=*(count)+1;
					}
				}
			}else{
				*(seed)=*(seed)-1;
			}
		}else{
			if ( random == 0 )
			{
				if ( *(seed) < 50 )
				{
					if ( ( *( enemyX+d) > 0 ) && ( *(enemyX+d)+enemyW < 1024 ) )
					{
						if ( difficulty == 0 )
						{
							*(seed)=*(seedDefault);
						}else if ( difficulty == 1 )
						{
							*(seed)=*(seedDefault+1);
						}else{
							*(seed)=*(seedDefault+2);
						}
						area[*(count)].y=*(enemyY+d)+(enemyH/2);
						area[*(count)].x=*(enemyX+d)+(enemyW/2);
						*(count)=*(count)+1;
					}
				}
			}else{
				*(seed)=*(seed)-1;
			}
		}
	}
	return(0);
}

