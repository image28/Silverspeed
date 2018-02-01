#define MAXTEXTURES 64

struct textures
{
	char name[128];
};

int pow2(int dim);
SDL_Surface* loadSurface(char *graphic);
int loadList(char *infile, struct textures *list, GLuint *fcount);
int SDL_GL_LoadTexture(struct textures *list, GLuint *texture, GLuint *texcount, GLfloat *texcoord, int *w, int *h);
void makeAlpha(SDL_Surface *image1, SDL_Surface *image2);
