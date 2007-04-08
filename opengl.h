

#ifndef OPENGL_H
#  define OPENGL_H


#include "SDL.h"
#include "SDL_opengl.h"

#include "physics.h"


/* Recommended for compatibility and such */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RMASK   0xff000000
#  define GMASK   0x00ff0000
#  define BMASK   0x0000ff00
#  define AMASK   0x000000ff
#else
#  define RMASK   0x000000ff
#  define GMASK   0x0000ff00
#  define BMASK   0x00ff0000
#  define AMASK   0xff000000
#endif
#define RGBAMASK  RMASK,GMASK,BMASK,AMASK


#define WINDOW_CAPTION	"game"


/*
 * Contains info about the opengl screen
 */
typedef struct {
	int w, h; /* window dimensions */
	int depth; /* depth in bpp */
	int fullscreen; /* 1 = fullscreen, 0 = not fullscreen */
	int r, g, b, a; /* framebuffer values in bits */
	int doublebuf; /* doublebuffer? */
} gl_info;
extern gl_info gl_screen; /* local structure set with gl_init and co */


/*
 * Spritesheet info
 */
typedef struct {
	double w, h; /* real size of the image (excluding POT buffer) */
	double rw, rh; /* size of POT surface */
	double sx, sy; /* number of sprites on x axis and y axis */
	double sw, sh; /* size of each sprite */
	GLuint texture; /* the opengl texture itself */
} gl_texture;


/*
 * Font info
 */
typedef struct {
	float h; /* height */
	GLuint *textures;
	GLuint list_base;
} gl_font;


/*
 * gl_font loading / freeing
 */
void gl_fontInit( gl_font* font, const char *fname, unsigned int h );
void gl_freeFont( gl_font* font );


/*
 * gl_texture loading / freeing
 */
gl_texture* gl_loadImage( SDL_Surface* surface ); /* frees the surface */
gl_texture* gl_newImage( const char* path );
gl_texture* gl_newSprite( const char* path, const int sx, const int sy );
void gl_freeTexture( gl_texture* texture );

/*
 * opengl drawing
 */
void gl_blitSprite( const gl_texture* sprite, const Vector2d* pos, const int sx, const int sy );
void gl_blitStatic( const gl_texture* texture, const Vector2d* pos );
void gl_bindCamera( const Vector2d* pos );
void gl_print( const gl_font *ft_font, Vector2d *pos, const char *fmt, ...);

/*
 * initialization / cleanup
 */
int gl_init (void);
void gl_exit (void);


#endif /* OPENGL_H */
	
