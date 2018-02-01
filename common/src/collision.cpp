#include <SDL/SDL.h>
#ifdef _WIN32 
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/container.h"
#include "../include/draw.h"
#include "../include/collision.h"
#include "../include/texture.h"

int genCollisionCoords(char *infile, int *left, int *right, int *top, int *bottom)
{
	SDL_Surface *imagetemp;
	int d,e;
	Uint32 pixel;
	int enemyW=0;
	int enemyH=0;

	// Load the surface
	imagetemp=loadSurface(infile);
	enemyW=imagetemp->w;
	enemyH=imagetemp->h;

	// Fill arrays with -1 ( no pixel )
	for(d=0;d<enemyH;d++)
	{
		*(left+d)=-1;
		*(right+d)=-1;
	}

	for(d=0;d<enemyW;d++)
	{
		*(top+d)=-1;
		*(bottom+d)=-1;
	}

	// Left Side
	for(d=0;d<enemyW;d++)
	{
		for(e=0;e<enemyH;e++)
		{
			pixel=0;
			pixel=getPixel(imagetemp,d,e);
			
			if ( pixel > 16777215 )
			{
				if ( *(left+e) == -1 )
				{
					*(left+e)=d;
				}
			}
		}
	}

	// Right Side
	for(d=enemyW-1;d>=0;d--)
	{
		for(e=0;e<enemyH;e++)
		{
			pixel=0;
			pixel=getPixel(imagetemp,d,e);
			
			if ( pixel > 16777215 )
			{
				if ( *(right+e) == -1 )
				{
					*(right+e)=d;
				}
			}
		}
	}


	// Top Side
	for(d=0;d<enemyW;d++)
	{
		for(e=0;e<enemyH;e++)
		{
			pixel=0;
			pixel=getPixel(imagetemp,d,e);
			
			if ( pixel > 16777215 )
			{
				if ( *(top+d) == -1 )
				{
					*(top+d)=e;
					e=enemyH;
				}
			}
		}
	}
	
	// Bottom Side
	for(d=0;d<enemyW;d++)
	{
		for(e=enemyH-1;e>=0;e--)
		{
			pixel=0;
			pixel=getPixel(imagetemp,d,e);
			
			if ( pixel > 16777215 )
			{
				if ( *(bottom+d) == -1 )
				{
					*(bottom+d)=e;
					e=-1;
				}
			}
		}
	}

	SDL_FreeSurface(imagetemp);
	return(0);

}

int enemyCollision(SDL_Surface *graphic[10], int *enemyType, int objX, int objW, int objY, int objH, int enemies, int *enemyX, int *enemyY, int *enemyW, int *enemyH, int *collide, int *collisions, int *top, int *bottom, int *left, int *right)
{
	int d=0;
	int ret=0;
	long minus=*(collisions);
	long count=*(collisions);

	//printf("OBJ3: %d %d\n",objW,objH);

	for(d=0;d<enemies;d++)
	{
		ret=collision(graphic[*(enemyType+d)], objX,objW,objY,objH,*(enemyX+d),*(enemyY+d),*(enemyW+*(enemyType+d)),*(enemyH+*(enemyType+d)),top,bottom,left,right);

		if ( ret )
		{
			*(collide+count)=d;
			count++;
			ret=0;
		}

		
	}

	if ( count-minus > 0 )
	{
		*(collisions)=count;
		return(1);
	}else{
		return(0);
	}

	return(ret);
}

int collision(SDL_Surface *graphic, int objX, int objW, int objY, int objH, int enemyX, int enemyY, int enemyW, int enemyH, int *top, int *bottom, int *left, int *right)
{
	
	
	int nothing=0;
	int d=0;
	int result=0;
	
	//printf("OBJ: %d %d\n",objW,objH);

	if( ( ( objY + objH ) <= enemyY) || (objY >= (enemyY+enemyH)) || ((objX+objW) <= enemyX) || (objX >= (enemyX+enemyW)) )
	{
		nothing=0;
	}else{
		if ( ( objX >= enemyX ) && ( objX <= enemyX+enemyW) ) 
		{ // left
			result=pixelCollide(graphic,2,objX,objW,objY,objH,enemyX, enemyY,left);
		}

		if ( ( objY <= enemyY+enemyH) && ( objY >= enemyY) )
		{ // top
			result=pixelCollide(graphic,0,objX,objW,objY,objH,enemyX, enemyY,top);
		}

		if ( ( objY + objH >= enemyY) && ( objY+objH <= enemyY+enemyH) )
		{ // bottom
			result=pixelCollide(graphic,1,objX,objW,objY,objH,enemyX, enemyY,bottom);
		}

		if ( ( objX+objW >= (enemyX) ) && ( objX+objW <= enemyX+enemyW) )
		{// right
			result=pixelCollide(graphic,3,objX,objW,objY,objH,enemyX, enemyY,right);
		}

		//printf("Result: %d\n",result);

	}

	return(result);
	
}


int pixelCollide(SDL_Surface *imagetemp, int comp, int objX,int objW, int objY, int objH, int enemyX, int enemyY, int *side)
{

	int collide=0;
	int d=0;
	Uint32 pixel=0;
	int start=0;
	int end=0;
	int enemyW=imagetemp->w;
	int enemyH=imagetemp->h;
	//printf("OBJ2: %d %d\n",enemyW,enemyH);

	// left have errors

	if ( comp == 0 )
	{
		// top
		if ( enemyX >= objX )
		{
		
			start=enemyX-objX;
			for(d=start;d<objW;d++)
			{
				if ( *(side+d) != -1 )
				{
					if ( *(side+d) <= enemyH-(objY-enemyY) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);
						pixel=0;
						pixel=getPixel(imagetemp,(d-start),((objY-enemyY)+*(side+d)));
						// test pixel
						//printf("Test %d\n",pixel);
						if ( pixel > 16777215 )
						{
							//printf("Collide 1\n");
							collide=1;
						}  			
					}
				}
			}
		}else{	
			start=objX-enemyX;
			if ( enemyW-start < objW )
			{
				end=enemyW-start;
			}else{
				end=objW;
			}
			
			for(d=0;d<end;d++)
			{
				if ( *(side+d) != -1 )
				{

					//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);
					if ( *(side+d) <= enemyH-(objY-enemyY) )
					{
						pixel=0;
						pixel=getPixel(imagetemp,start+d,((objY-enemyY)+*(side+d)));
						// test pixel
						//printf("-Test %d\n",pixel);
						if ( pixel > 16777215 )
						{
							//printf("Collide 2\n");
							collide=2;
						}  			
					}
				}

			}
		}
	}else if ( comp == 1 )
	{
		// bottom
		
		if ( enemyX >= objX )
		{
			start=enemyX-objX;
			for(d=start;d<objW;d++)
			{
				if ( *(side+d) != -1 )
				{
					if ( *(side+d) >= (enemyY-objY) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);
						pixel=0;
						pixel=getPixel(imagetemp,(d-start),(*(side+d)-(enemyY-objY)));

						// test pixel
						if ( pixel > 16777215 )
						{
							//printf("Collide 3\n");
							collide=3;
						}  			
					}
				}
			}
		}else{	
			start=objX-enemyX;
			if ( enemyW-start < objW )
			{
				end=enemyW-start;
			}else{
				end=objW;
			}
			
			for(d=0;d<end;d++)
			{
				if ( *(side+d) != -1 )
				{
					if ( *(side+d) >= (enemyY-objY) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);

						pixel=0;
						pixel=getPixel(imagetemp,start+d,*(side+d)-(enemyY-objY));
						// test pixel
						if ( pixel > 16777215 )
						{
							//printf("Collide 4\n");
							collide=4;
						}  			
					}
				}
			}
		}


	}else if ( comp == 2 )
	{//printf("BOO2");
		// left
		if ( enemyY >= objY )
		{
			
			start=enemyY-objY;
			for(d=start;d<objH;d++)
			{
				if ( *(side+d) != -1 )
				{
					if ( *(side+d) <= enemyW-(objX-enemyX) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);
						pixel=0;
						pixel=getPixel(imagetemp,(*(side+d)+(objX-enemyX)),(d-start));

						// test pixel
						if ( pixel > 16777215 )
						{
							//printf("Collide 5\n");
							collide=5;
						}  			
					}
				}
			}
		}else{	
//printf("enemyY < objY\n");
			start=objY-enemyY;
			if ( enemyH-start < objH )
			{
				end=enemyH-start;
			}else{
				end=objH;
			}

			for(d=0;d<end;d++)
			{
					
				if ( *(side+d) != -1 )
				{
					
					if ( *(side+d) <= enemyW-(objX-enemyX) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);

						pixel=0;
						pixel=getPixel(imagetemp,*(side+d)+(objX-enemyX),start+d);
						// test pixel
						if ( pixel > 16777215 )
						{
							//printf("Collide 6\n");
							collide=6;
						}  			
					}
				}
			}
		}


	}else if ( comp == 3 )
	{
		// right above enemy
		if ( enemyY >= objY )
		{
			start=enemyY-objY;
			for(d=start;d<objH;d++)
			{
				if ( *(side+d) != -1 )
				{
					if ( *(side+d) >= (enemyX-objX) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);
						pixel=0;
						pixel=getPixel(imagetemp,(*(side+d)-(enemyX-objX)),(d-start));

						// test pixel
						if ( pixel > 16777215 )
						{
							//printf("Collide 7\n");
							collide=7;
						}  			

					}
				}
			}
		}else{	


			// right bellow enemy
			start=objY-enemyY;
			if ( enemyH-start < objH )
			{
				end=enemyH-start;
			}else{
				end=objH;
			}

			for(d=0;d<end;d++)
			{
				if ( *(side+d) != -1 )
				{
					if ( *(side+d) >= (enemyX-objX) )
					{
						//printf("START: %d\nEnemyX %d\nobjX %d\nobjW %d\nSIDE: %d\nD: %d\n\n",start,enemyX,objX,objW,*(side+d),d);

						pixel=0;
						pixel=getPixel(imagetemp,(*(side+d)-(enemyX-objX)),(start+d));
						// test pixel
						if ( pixel > 16777215 )
						{
							//printf("Collide 8\n");
							collide=8;
						}  			
					}
				}
			}
		}

	}

	
	return(collide);
}
