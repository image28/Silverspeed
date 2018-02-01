#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#ifdef _WIN32 
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/container.h"
#include "../include/init.h"

int startup(struct container *screen, const GLubyte *vendor, const GLubyte *renderer, const GLubyte *version, const GLubyte *extensions)
{
	int d=0;
	int bpp=32;

// SDL INIT
	if ( (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == -1 ) ) 
	{
		printf("Could not initialize SDL: %s.\n", SDL_GetError()); 
		exit(-1);
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

	screen->image = SDL_SetVideoMode(screen->area.w, screen->area.h, bpp, SDL_OPENGL|SDL_SWSURFACE);//|SDL_RESIZABLE);//|SDL_FULLSCREEN);  
// SDL INIT	

	vendor=glGetString(GL_VENDOR);
	renderer=glGetString(GL_RENDERER);
	version=glGetString(GL_VERSION);
	extensions=glGetString(GL_EXTENSIONS);
	printf("VENDOR: %s\nRENDERER: %s\nVERSION: %s\n\n",vendor,renderer,version);

	printf("Availible Extensions:\n");
	for(d=0;d<strlen((const char*)(extensions));d++)
	{
		if ( *(extensions+d) == 32 )	
			printf("\n");
		else
			printf("%c",*(extensions+d));

	}printf("\n");

	/*
	if ( ! checkExt("GL_ARB_texture_non_power_of_two") )
	{
		printf("Required Graphics Card Extension Not Found\n");
		printf("GL_ARB_texture_non_power_of_two\n");
		exit(-1);
	}*/

	glViewport(0,0,screen->area.w,screen->area.h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0,screen->area.w,screen->area.h,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
}

int reload(struct container *screen, int *windowed, int win32)
{
	int bpp=32;

	if ( *(windowed) )
	{
		screen->image = SDL_SetVideoMode(screen->area.w, screen->area.h, bpp, SDL_OPENGL|SDL_SWSURFACE|SDL_GL_DOUBLEBUFFER|SDL_FULLSCREEN);  
		*(windowed)=0;
	}else{
		screen->image = SDL_SetVideoMode(screen->area.w, screen->area.h, bpp, SDL_OPENGL|SDL_SWSURFACE);
		*(windowed)=1;
	}

// SDL INIT	
	if ( win32 )
	{
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,     32);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,  8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
	
		glViewport(0,0,screen->area.w,screen->area.h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(0,screen->area.w,screen->area.h,0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	}
}

int checkExt(char* name)
{
	char *list = (char*) glGetString(GL_EXTENSIONS);
	unsigned int first=0;
	
	if ( !name || !list )
		return 0;

	while(*list)
	{
		first = strcspn(list," ");

		if ( strlen(name) == first && strncmp(name,list, first) == 0 )
		{
			return 1;
		}

		list += first + 1;
	}

	return 0;
}
