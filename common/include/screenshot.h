#include <png.h>

int png_save_surface(char *filename, SDL_Surface *surf);
void png_user_error(png_structp ctx, png_const_charp str);
void png_user_warn(png_structp ctx, png_const_charp str);
static int png_colortype_from_surface(SDL_Surface *surface);


