#include <GL/gl.h>
#include <SDL/SDL_ttf.h>

//struct colour { Uint8 R; Uint8 G; Uint8 B; Uint8 A; };
struct colour { GLubyte R; GLubyte G; GLubyte B; GLubyte A; };

void SDL_GL_Leave2DMode();
void SDL_GL_Enter2DMode();
void DrawPixel(struct container *screen, struct colour colour, int x, int y, int update);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 getPixel(SDL_Surface *surface, int x, int y);
int draw(struct container *screen, int entity, GLuint *texture, int x, int y, int w, int h);
int putText(struct container *screen, char *text, GLuint *texture, int x, int y, int *w, int *h);
int genTextTexture(GLuint *texture, char *temp, GLuint *texcount, TTF_Font *font, struct colour colour, int *w, int *h);
int drawpart(struct container *screen, int entity, GLuint *texture, int startx, int x, int y, int w, int h);

