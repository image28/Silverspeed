#include <SDL/SDL.h>
#include <GL/gl.h>
#include <png.h>

static int png_colortype_from_surface(SDL_Surface *surface)
{
	int colortype = PNG_COLOR_MASK_COLOR; /* grayscale not supported */

	if (surface->format->palette)
		colortype |= PNG_COLOR_MASK_PALETTE;
	else if (surface->format->Amask)
		colortype |= PNG_COLOR_MASK_ALPHA;
		
	return colortype;
}


void png_user_warn(png_structp ctx, png_const_charp str)
{
	fprintf(stderr, "libpng: warning: %s\n", str);
}


void png_user_error(png_structp ctx, png_const_charp str)
{
	fprintf(stderr, "libpng: error: %s\n", str);
}


int png_save_surface(char *filename, SDL_Surface *surf)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	int i, colortype;
	int rev=0;
	png_bytep *row_pointers;
   	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface *image;
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, 1024, 768, 32, rmask, gmask, bmask,amask);
	
	glReadPixels(0, 0, 1024, 768, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);


	/* Opening output file */
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		perror("fopen error");
		return -1;
	}

	/* Initializing png structures and callbacks */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
		NULL, png_user_error, png_user_warn);
	if (png_ptr == NULL) {
		printf("png_create_write_struct error!\n");
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		printf("png_create_info_struct error!\n");
		exit(-1);
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		exit(-1);
	}

	png_init_io(png_ptr, fp);

	colortype = png_colortype_from_surface(image);
	png_set_IHDR(png_ptr, info_ptr, image->w, image->h, 8, colortype,	PNG_INTERLACE_NONE, 
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	/* Writing the image */
	png_write_info(png_ptr, info_ptr);
	png_set_packing(png_ptr);

	int rowsize = image->w * 32 / 8 ;

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep)*image->h);
	for (i = 0; i < image->h; i++)
	{
		rev=((image->h-i)-1) * rowsize;
		row_pointers[i] = (png_bytep)(Uint8 *)image->pixels + rev; // + i*image->pitch;
	}
	png_write_image(png_ptr, row_pointers);
	png_write_end(png_ptr, info_ptr);

	/* Cleaning out... */
	SDL_FreeSurface(image);
	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	return 0;
}
