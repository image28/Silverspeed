#include <SDL/SDL.h>
#ifdef _WIN32 
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_ttf.h>
#include "../include/container.h"
#include "../include/draw.h"
#include "../include/texture.h"

void SDL_GL_Enter2DMode()
{
	glColor4ub(255,255,255,255);
	glEnable(GL_TEXTURE_2D);	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_DECAL);
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable( GL_LIGHTING );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	
	
}

void SDL_GL_Leave2DMode()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void DrawPixel(struct container *screen, struct colour colour, int x, int y, int update)
{

	glColor4ub(colour.R,colour.G,colour.B,colour.A);
	
	if ( ( x < screen->area.w ) && ( y < screen->area.h ) )
	{
		glBegin(GL_POINTS);
			glVertex2i(x,y);
		glEnd();
	}

	if ( update )
		SDL_GL_SwapBuffers();
}




void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	 int bpp = surface->format->BytesPerPixel;
 // Here p is the address to the pixel we want to set

	if (( x > 0 ) && ( y > 0 ) && ( x < surface->w ) && ( y < surface->h ) )
	{
	 Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		 switch(bpp)
		 {
			  case 1:
			   *p = pixel;
			   break;
			  case 2:
			   *(Uint16 *)p = pixel;
			   break;
			  case 3:
			   if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			   {
			    p[0] = (pixel >> 16) & 0xff;
			    p[1] = (pixel >> 8) & 0xff;
			    p[2] = pixel & 0xff;
			   } else {
			    p[0] = pixel & 0xff;
			    p[1] = (pixel >> 8) & 0xff;
			    p[2] = (pixel >> 16) & 0xff;
			   }
			   break;
			  case 4:
			   *(Uint32 *)p = pixel;
			   break;
		 }

	}
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    if ( ( x > 0 ) && ( y > 0 ) && ( x < surface->w ) && ( y < surface->h ) )
    {
	    int bpp = surface->format->BytesPerPixel;
	    /* Here p is the address to the pixel we want to retrieve */
	    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	    switch(bpp) {
	    case 1:
		return *p;

	    case 2:
		return *(Uint16 *)p;

	    case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		    return p[0] << 16 | p[1] << 8 | p[2];
		else
		    return p[0] | p[1] << 8 | p[2] << 16;

	    case 4:
		return *(Uint32 *)p;

	    default:
		return 0;       /* shouldn't happen, but avoids warnings */
	    }
    }else{
	return(0);
   }
}

int genTextTexture(GLuint *texture, char *temp, GLuint *texcount, TTF_Font *font, struct colour colour, int *w, int *h)
{
	char text[128];
	strcpy(text,"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:#");
	int d,e,l;
	int tempW[128];
	int tempH[128];
	//char temp[2];
	*(texcount)=strlen(text);

	unsigned int pixel;
	SDL_Color color={colour.R,colour.G,colour.B};
	SDL_Surface *surface[256];
	SDL_Surface *image[256];


	for(d=0;d<*(texcount);d++)
	{
		
		*(temp+0)='\0';
		*(temp+0)=text[d];
		*(temp+1)='\0';
		
		surface[d] = TTF_RenderText_Solid(font, temp, color);
		*(w+d) = surface[d]->w;
		*(h+d) = surface[d]->h;
		tempW[d]=pow2(*(w+d));
		tempH[d]=pow2(*(h+d));
	}

	for(d=0;d<*(texcount);d++)
	{
		image[d] = SDL_CreateRGBSurface(
				SDL_SWSURFACE,
				tempW[d], tempH[d],
				32,
	#if SDL_BYTEORDER == SDL_LIL_ENDIAN // OpenGL RGBA masks 
				0x000000FF, 
				0x0000FF00, 
				0x00FF0000, 
				0xFF000000
	#else
				0xFF000000,
				0x00FF0000, 
				0x0000FF00, 
				0x000000FF
	#endif
			       );

		SDL_BlitSurface(surface[d], NULL, image[d], NULL);
	}



	// Genorate and bind textures in list
	glGenTextures(*(texcount), texture);
	for(d=0;d<*(texcount);d++)
	{
		glBindTexture(GL_TEXTURE_2D, *(texture+d));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,tempW[d],tempH[d],0,GL_RGBA,GL_UNSIGNED_BYTE,image[d]->pixels);
		SDL_FreeSurface(surface[d]);
		SDL_FreeSurface(image[d]);
		 
	}	
	return(0);
}

int putText(struct container *screen, char *text, GLuint *texture, int x, int y, int *w, int *h)
{

	int d,e;

	//Uint32 pixel;
	//SDL_Color color={colour.R,colour.G,colour.B};
	//SDL_Surface *image = TTF_RenderText_Solid(font, text, color);
/*
	for(d=0;d<image->w;d++)
	{
		for(e=0;e<image->h;e++)

		{
			pixel=0;
			pixel=getPixel(image,d,e);
			SDL_GetRGB(pixel,image->format,&colour.R,&colour.G,&colour.B);
			colour.A=0;
			if ( pixel != 0 )
				DrawPixel(screen,colour,x+d,y+e,0);
		}
	}

	SDL_FreeSurface(image);
*/

	for(d=0;d<strlen(text);d++)
	{
		if ( d == 0 )
		{
			if ( ( *(text+d) > 64 ) && ( *(text+d) < 91 ) )
			{
				draw(screen,*(text+d)-65,texture,x,y,*(w+(*(text+d)-65)),*(h+(*(text+d)-65)));
			}else if ( ( *(text+d) > 47 ) && ( *(text+d) < 59 ) )
			{
				draw(screen,*(text+d)-22,texture,x,y,*(w+(*(text+d)-22)),*(h+(*(text+d)-22)));
			}else{
				
				draw(screen,*(text+d)+2,texture,x,y,*(w+(*(text+d)+2)),*(h+(*(text+d)+2)));
			}
		}else{
			

			if ( ( *(text+d) > 64 ) && ( *(text+d) < 91 ) )
			{
				if ( *(text+(d-1)) != 32 )
				{
					if ( *(text+(d-1)) < 59 ) 
						x=x+*(w+(*(text+(d-1))-22));
					else
						x=x+*(w+(*(text+(d-1))-65));
				}

				draw(screen,*(text+d)-65,texture,x,y,*(w+(*(text+d)-65)),*(h+(*(text+d)-65)));
			}else if ( ( *(text+d) > 47 ) && ( *(text+d) < 59 ) )
			{
				if ( *(text+(d-1)) != 32 )
				{
					if ( *(text+(d-1)) < 59 ) 
						x=x+*(w+(*(text+(d-1))-22));
					else
						x=x+*(w+(*(text+(d-1))-65));
				}

				draw(screen,*(text+d)-22,texture,x,y,*(w+(*(text+d)-22)),*(h+(*(text+d)-22)));
			}else if ( *(text+d) == 32 )
			{
				if ( *(text+(d-1)) < 59 ) 
					x=x+*(w+(*(text+(d-1))-22))+8;
				else
					x=x+*(w+(*(text+(d-1))-65))+8;

			}else{
				x=x+*(w+(*(text+(d-1))+2));
				draw(screen,*(text+d)+2,texture,x,y,*(w+(*(text+d)+2)),*(h+(*(text+d)+2)));
			}
		}
	}
	return(0);
}

int draw(struct container *screen, int entity, GLuint *texture, int x, int y, int w, int h)
{

	// open png for tile
	//SDL_GL_Enter2DMode();
	int tempW=pow2(w);
	int tempH=pow2(h);

	glBindTexture( GL_TEXTURE_2D, *(texture+entity) );

	glBegin( GL_QUADS );
		// Top-left vertex (corner)
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( x, y, 0 );

		// Bottom-left vertex (corner)
		glTexCoord2f( 0.0f, (float)h/(float)tempH );
		glVertex3f( x, y+h, 0 );

		// Bottom-right vertex (corner)
		glTexCoord2f( (float)w/(float)tempW, (float)h/(float)tempH );
		glVertex3f( x+w, y+h, 0 );

		// Top-right vertex (corner)
		glTexCoord2f( (float)w/(float)tempW, 0.0f );
		glVertex3f( x+w, y, 0 );
	glEnd();

	//SDL_GL_Leave2DMode();

	return(0);

}

int drawpart(struct container *screen, int entity, GLuint *texture, int startx, int x, int y, int w, int h)
{

	// open png for tile
	//SDL_GL_Enter2DMode();
	int tempW=pow2(w);
	int tempH=pow2(h);

	glBindTexture( GL_TEXTURE_2D, *(texture+entity) );

	glBegin( GL_QUADS );
		// Top-left vertex (corner)
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( x, y, 0 );

		// Bottom-left vertex (corner)
		glTexCoord2f( 0.0f, (float)h/(float)tempH );
		glVertex3f( x, y+h, 0 );

		if ( w > startx )
		{
			// Bottom-right vertex (corner)
			glTexCoord2f( (float)startx/(float)tempW, (float)h/(float)tempH );
			glVertex3f( x+startx, y+h, 0 );

			// Top-right vertex (corner)
			glTexCoord2f( (float)startx/(float)tempW, 0.0f );
			glVertex3f( x+startx, y, 0 );

		}else{
			// Bottom-right vertex (corner)
			glTexCoord2f( (float)w/(float)tempW, (float)h/(float)tempH );
			glVertex3f( x+w, y+h, 0 );

			// Top-right vertex (corner)
			glTexCoord2f( (float)w/(float)tempW, 0.0f );
			glVertex3f( x+w, y, 0 );
		}


	glEnd();

	//SDL_GL_Leave2DMode();

	return(0);

}




