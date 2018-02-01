#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

int startup(struct container *screen, const GLubyte *vendor, const GLubyte *renderer, const GLubyte *version, const GLubyte *extensions);
int reload(struct container *screen, int *windowed, int win32);
int checkExt(char *name);

