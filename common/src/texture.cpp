#include <SDL/SDL.h>
#ifdef _WIN32 
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>
#include "../include/container.h"
#include "../include/draw.h"
#include "../include/texture.h"

int pow2(int dim)
{
	int d = 1;

	while ( d < dim ) 
	{
		d <<= 1;
	}

	return(d);
}

SDL_Surface* loadSurface(char *graphic)
{
	SDL_Surface *surface;
	surface=IMG_Load(graphic);

	if ( surface == NULL )
	{
		printf("Failed to load %s\n",graphic);
		return(NULL);
	}else{
		printf("Loaded %s\n",graphic);
		return(surface);
	}
}


int loadList(char *infile, struct textures *list, GLuint *fcount)
{
	FILE *input;
	int count=0;
	char inbyte='\0';
	*(fcount)=0;

	if ( ( input=fopen(infile,"rb") ) == NULL ) exit(-1);

	while ( ! feof(input) )
	{
		inbyte='\0';
		fread(&inbyte,1,1,input);
	
		if ( ( inbyte == '\n' ) || ( feof(input) ) )
		{
			if ( ! feof(input) )
			{
				list[*(fcount)].name[count]='\0';
			
				*(fcount)=*(fcount)+1;
			}
			count=0;
		}else{
			list[*(fcount)].name[count]='\0';
			list[*(fcount)].name[count]=inbyte;
			count++;
		}
	}

	fclose(input);
	return(0);
}

int SDL_GL_LoadTexture(struct textures *list, GLuint *texture, GLuint *texcount, GLfloat *texcoord, int *w, int *h)
{
	SDL_Surface *tempSurf[100];
	SDL_Surface *surface[100];
	int d=0;
	int x,y;
	int tempW[100];
	int tempH[100];
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8  saved_alpha;

	// Load all surfaces in list
	for(d=0;d<*(texcount);d++)
	{
		tempSurf[d]=loadSurface(list[d].name);
		*(w+d)=0;
		*(h+d)=0;
		*(w+d) = tempSurf[d]->w;
		*(h+d) = tempSurf[d]->h;
		tempW[d]=0;
		tempH[d]=0;
		tempW[d]=pow2(*(w+d));
		tempH[d]=pow2(*(h+d));
	}

	for(d=0;d<*(texcount);d++)
	{
		if ( tempSurf[d]->format->BytesPerPixel == 3 )
		{

		surface[d] = SDL_CreateRGBSurface(
				SDL_SWSURFACE,
				tempW[d], tempH[d],
				24,
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
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
		}else{
			surface[d] = SDL_CreateRGBSurface(
					SDL_SWSURFACE,
					tempW[d], tempH[d],
					32,
		#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
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

		}

	/* Save the alpha blending attributes */
		saved_flags = tempSurf[d]->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
		saved_alpha = tempSurf[d]->format->alpha;
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(tempSurf[d], 0, 0);
		}

		SDL_BlitSurface(tempSurf[d], NULL, surface[d], NULL);

	/* Restore the alpha blending attributes */
		if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
			SDL_SetAlpha(tempSurf[d], saved_flags, saved_alpha);
		}

	}

	// Genorate and bind textures in list
	glGenTextures(*(texcount), texture);
	for(d=0;d<*(texcount);d++)
	{
		glBindTexture(GL_TEXTURE_2D, *(texture+d));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		if ( surface[d]->format->BytesPerPixel == 3 )
		{
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,tempW[d],tempH[d],0,GL_RGB,GL_UNSIGNED_BYTE,surface[d]->pixels);
		}else{
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,tempW[d],tempH[d],0,GL_RGBA,GL_UNSIGNED_BYTE,surface[d]->pixels);
		}
		
	}

	for(d=0;d<*(texcount);d++)
	{
		SDL_FreeSurface(tempSurf[d]);
		SDL_FreeSurface(surface[d]); 
	}
	return(0);
}
