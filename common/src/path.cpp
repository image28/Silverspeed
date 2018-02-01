#include <SDL/SDL.h>
#include <math.h>
#include "../include/container.h"
#include "../include/path.h"

/*
#ifdef _WIN32
	static inline double round(double val)
	{   
	    return floor(val + 0.5);
	}
#endif
*/
int calcMaxPathLength(int w, int h)
{
	//#ifdef _WIN32
	//	double m,n;
	//#else
		long m,n;
	//#endif

	m   = abs(w);
	n   = abs(h);
	if (m<=n) {
		m   = abs(h);
		n   = abs(w);
	}
	
	return(round(m)*2);

}

int pathPos(struct coords path, int dist, int xy)
{


	/*if ( path.x > path.w )
	{
		temp = path.x;
		path.x=path.w;
		path.w=temp;
	}

	if ( path.y > path.h )
	{
		temp=path.y;
		path.y=path.h;
		path.h=temp;
	}*/

	int res=0;
	long double length = sqrt((long double)(path.w - path.x) * (path.w - path.x) + (path.h - path.y) * (path.h - path.y));

	if ( ! xy )
	{
		res = path.x + dist * (path.w - path.x) / length;
	}else{
		res = path.y + dist * (path.h - path.y) / length;
	}

	return(res);
}

int multiplyPath(struct container *screen, struct coords *area)
{
	int count=0;
	int d=0;
	int temp,temp2;
	int width=0;

	//if ( ( area->x != area->w ) && ( area->y != area->h ) )
	//{
		if ( area->x > area->w )
		{
			temp=area->x-area->w;

			if ( area->y > area->h )
			{
				temp2=area->y-area->h;
	
				if ( temp > temp2 )
				{
					width=1;
				}
			}else 
			{
				temp2=area->h-area->y;
	
				if ( temp > temp2 )
				{
					width=1;
				}
			}
		}else
		{
			temp=area->w-area->x;
			

			if ( area->y > area->h )
			{
				temp2=area->y-area->h;
	
				if ( temp > temp2 )
				{
					width=1;
				}
			}else 
			{
				temp2=area->h-area->y;
	
				if ( temp > temp2 )
				{
					width=1;
				}
			}
		}

		if ( width )
		{
			if ( area->x > area->w )
			{
				while ( area->w > -20 )
				{
					area->w=area->w-(area->x-area->w);
					count++;
				}	
			}else{
				while ( area->w < screen->area.w+20 )
				{
					area->w=area->w+(area->w-area->x);
					count++;	
				}
			}

			if ( area->y != area->h )
			{
				if ( area->y > area->h )
				{
					for(d=0;d<count;d++)
					{
						area->h=area->h-(area->y-area->h);
					}

				}else{
					for(d=0;d<count;d++)
					{
						area->h=area->h+(area->h-area->y);
					}
				}
			}
		}else{

			if ( area->y > area->h )
			{
				while ( area->h > -20 )
				{
					area->h=area->h-(area->y-area->h);	

					count++;
				}

			}else{
				while ( area->h < screen->area.h+20 )
				{
					area->h=area->h+(area->h-area->y);	
					count++;
				}
			}

			if ( area->x != area->w )
			{
				if ( area->x > area->w )
				{
					for(d=0;d<count;d++)
					{
						area->w=area->w-(area->x-area->w);
				
					}	
				}else{
					for(d=0;d<count;d++)
					{
						area->w=area->w+(area->w-area->x);
					}
				}
			}
		}
	//}

	return(0);
}

int sgn (long a) 
{
	if (a > 0) 
		return +1;
	else if (a < 0) 
		return -1;
	else 
		return 0;
}
