#include "../include/path.h"

int dupCollide(int *collide, int *collisions)
{
	int d,e,l;
	int shuffle=0;

	for(d=0;d<*(collisions);d++)
	{
		for(e=d+1;e<*(collisions);e++)
		{
			if ( *(collide+d) == *(collide+e) )
			{
				shuffle=1;
				*(collisions)=*(collisions)-1;
			}

			if ( shuffle )
			{
				for(l=e; l < *(collisions); l++ )
				{
					*(collide+l)=*(collide+(l+1));
				}

				e--;
				shuffle=0;
			}
		}
	}
return(0);
}

int shuffleObj(int *count, int *type, int *objX, int *objY, int less, int amount)
{
	int d,e;
	int shuffle=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			if ( ! shuffle )
			{
				if ( less )
				{
					if ( *(objX+d) < amount )
					{
						shuffle=1;
						*(count)=*(count)-1;
					}
				}else{
					if ( *(objX+d) > amount )
					{
						shuffle=1;
						*(count)=*(count)-1;
					}
				}


			}

			if ( d < *(count) )
			{
				if ( shuffle )
				{
					*(objX+d)=*(objX+(d+1));
					*(objY+d)=*(objY+(d+1));
					*(type+d)=*(type+(d+1));
				}
			}
	
		}

		shuffle=0;
	}
	return(0);
}

int shuffleDropScreen(int *count, int *type, int *objX, int *objY, int dHold[][16], int dFramePos[][16],int less, int amount)
{
	int d,e,l;
	int shuffle=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			if ( ! shuffle )
			{
				if ( less )
				{
					if ( *(objX+d) < amount )
					{
						shuffle=1;
						*(count)=*(count)-1;
					}
				}else{
					if ( *(objX+d) > amount )
					{
						shuffle=1;
						*(count)=*(count)-1;
					}
				}


			}

			if ( d < *(count) )
			{
				if ( shuffle )
				{
					*(objX+d)=*(objX+(d+1));
					*(objY+d)=*(objY+(d+1));
					*(type+d)=*(type+(d+1));
					for(l=0;l<16;l++)
					{
						//*(eHold+(d*16)+l)=*(eHold+(d+1)*16+l);
						//*(eFramePos+(d*16)+l)=*(eFramePos+(d+1)*16+l);
						dHold[d][l]=dHold[d+1][l];
						dFramePos[d][l]=dFramePos[d+1][l];
					}
				}
			}
	
		}

		shuffle=0;
	}
	return(0);
}

int shuffleDrop(int *count, int *type, int *enemyX, int *enemyY, int *collide, int dHold[][16], int dFramePos[][16], int collisions)
{
	
	int d,e,l,f;
	int shuffle=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			for(l=0;l<collisions;l++)
			{

				if ( ! shuffle )
				{
					if ( d == *(collide+l) )
					{
						*(count)=*(count)-1;
						collisions--;
						shuffle=1;

					}	
				}
		
				if ( shuffle )
				{
					if ( l < collisions )
					{
						*(collide+l)=*(collide+(l+1));
						*(collide+l)=*(collide+l)-1;
					}
				}
				
				
			}

			if ( shuffle )
			{

				if ( d < *(count) )
				{
					*(enemyX+d)=*(enemyX+(d+1));
					*(enemyY+d)=*(enemyY+(d+1));
					*(type+d)=*(type+(d+1));
					for(f=0;f<16;f++)
					{
						//*(eHold+(d*16)+l)=*(eHold+(d+1)*16+l);
						//*(eFramePos+(d*16)+l)=*(eFramePos+(d+1)*16+l);
						dHold[d][f]=dHold[d+1][f];
						dFramePos[d][f]=dFramePos[d+1][f];
					}
				}
			}



	
		}
		
		shuffle=0;
	}
	return(0);

}

int shuffleEnemyBulletCollide(int *count, int *type, int *dist, int *start, int *objX, int *objY, struct coords *area, int *collide, int collisions)
{
	int d,e;

	for(d=0;d<collisions;d++)
	{
		*(count)=*(count)-1;
		for(e=*(collide+d);e<*(count);e++)
		{
			*(objX+e)=*(objX+(e+1));
			*(objY+e)=*(objY+(e+1));
			*(type+e)=*(type+(e+1));
			*(dist+e)=*(dist+(d+1));
			*(start+e)=*(start+(d+1));
			area[e].x = area[e+1].x;
			area[e].y = area[e+1].y;
			area[e].w = area[e+1].w;
			area[e].h = area[e+1].h;

		}

	}
return(0);

}

int shuffleEnemyBullet(int *count, int *type, int *dist, int *start, int *objX, int *objY, int *objW, int *objH, struct coords *area)
{
	int d,e;
	int shuffle=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			if ( ! shuffle )
			{
				if ( *(objX+d) < 0-*(objW+*(type+d)) )
				{
					shuffle=1;
					*(count)=*(count)-1;
				}else if ( *(objX+d) > 1024+*(objW+*(type+d)) )
				{
					shuffle=1;
					*(count)=*(count)-1;
				}else if ( *(objY+d) < 0-*(objH+*(type+d)) )
				{
					shuffle=1;
					*(count)=*(count)-1;
				}else if ( *(objY+d) > 768+*(objH+*(type+d)) )
				{
					shuffle=1;
					*(count)=*(count)-1;
				}
			}

			if ( d < *(count) )
			{
				if ( shuffle )
				{
					*(objX+d)=*(objX+(d+1));
					*(objY+d)=*(objY+(d+1));
					*(type+d)=*(type+(d+1));
					*(dist+d)=*(dist+(d+1));
					*(start+d)=*(start+(d+1));
					area[d].x = area[d+1].x;
					area[d].y = area[d+1].y;
					area[d].w = area[d+1].w;
					area[d].h = area[d+1].h;

				}
			}
	
		}

		shuffle=0;
	}
	return(0);
}

int shuffleCollide(int *count, int *type, int *enemyX, int *enemyY, int *collide, int collisions)
{
	
	int d,e,l;
	int shuffle=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			for(l=0;l<collisions;l++)
			{

				if ( ! shuffle )
				{
					if ( d == *(collide+l) )
					{
						*(count)=*(count)-1;
						collisions--;
						shuffle=1;

					}	
				}
		
				if ( shuffle )
				{
					if ( l < collisions )
					{
						*(collide+l)=*(collide+(l+1));
						*(collide+l)=*(collide+l)-1;
					}
				}
				
				
			}

			if ( shuffle )
			{

				if ( d < *(count) )
				{
					*(enemyX+d)=*(enemyX+(d+1));
					*(enemyY+d)=*(enemyY+(d+1));
					*(type+d)=*(type+(d+1));
				}
			}



	
		}
		
		shuffle=0;
	}
	return(0);

}

int shuffleEnemyHit(int *hits, int *collide, int *collisions)
{
	
	int d,e,l;
	int shuffle=0;
	int remCollide=0;

	for(l=0;l<*(collisions);l++)
	{
		if ( *(hits+*(collide+l)) > 0 )
		{
			*(hits+*(collide+l))=*(hits+*(collide+l))-1;
			*(collisions)=*(collisions)-1;
			remCollide=1;
			
		}	

		if ( remCollide )
		{
			for(d=l;d<*(collisions);d++)
			{
				*(collide+d)=*(collide+(d+1));
				//*(collide+d)=*(collide+d)-1;
				
			}
			l--;
			remCollide=0;
		}
	}
	return(0);
}

int shuffleEnemyScreen(int *count, int *type, int *hits, int *objX, int *objY, int eHold[][16], int eFramePos[][16], int eBulletHold[][16], int less, int amount)
{
	int d,e,l;
	int shuffle=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			if ( ! shuffle )
			{
				if ( less )
				{
					if ( *(objX+d) < amount )
					{
						shuffle=1;
						*(count)=*(count)-1;
					}
				}else{
					if ( *(objX+d) > amount )
					{
						shuffle=1;
						*(count)=*(count)-1;
					}
				}


			}

			if ( d < *(count) )
			{
				if ( shuffle )
				{
					*(objX+d)=*(objX+(d+1));
					*(objY+d)=*(objY+(d+1));
					*(type+d)=*(type+(d+1));
					*(hits+d)=*(hits+(d+1));
					for(l=0;l<16;l++)
					{
					
						eHold[d][l]=eHold[d+1][l];
						eFramePos[d][l]=eFramePos[d+1][l];
						eBulletHold[d][l]=eBulletHold[d+1][l];
					}
				}
			}
	
		}

		shuffle=0;
	}
	return(0);
}


int shuffleEnemy(int *count, int *type, int *hits, int *enemyX, int *enemyY, int *collide, int eHold[][16], int eFramePos[][16], int eBulletHold[][16], int collisions)
{
	
	int d,e,l,f;
	int shuffle=0;
	int remCollide=0;

	for(e=0;e<*(count);e++)
	{
		for(d=e;d<*(count);d++)
		{
			for(l=0;l<collisions;l++)
			{

				if ( ! shuffle ) 
				{
					if ( d == *(collide+l) )
					{
							*(count)=*(count)-1;
							collisions--;
							shuffle=1;
					}	
				}

				if ( shuffle )
				{
					if ( l < collisions )
					{
						*(collide+l)=*(collide+(l+1));
						*(collide+l)=*(collide+l)-1;
					}
				}
			
			
			}

			if ( shuffle )
			{

				if ( d < *(count) )
				{
					*(enemyX+d)=*(enemyX+(d+1));
					*(enemyY+d)=*(enemyY+(d+1));
					*(type+d)=*(type+(d+1));
					*(hits+d)=*(hits+(d+1));
					for(f=0;f<16;f++)
					{
						
						eHold[d][f]=eHold[d+1][f];
						eFramePos[d][f]=eFramePos[d+1][f];
						eBulletHold[d][f]=eBulletHold[d+1][f];
					}
				}
			}



	
		}
		
		shuffle=0;
	}
	return(0);

}

