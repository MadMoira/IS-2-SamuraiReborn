#include "GameCore.h"


GameCore::GameCore()
{
        currentGameState = 0;
        configuration = new GameConfiguration();
        saves = new GameSaves();
        screen = new GameScreen();
        timer = new GameTimer();
        currentStateID = STATE_NULL;
}

bool GameCore::initGame()
{
	if( screen->initialize() )
	{
		return true;
    }
	
	return false;
}

GameCore::~GameCore(void)
{
        delete currentGameState;
        delete configuration;
        delete saves;
        delete screen;
        delete timer;
}

GLuint GameCore::loadTexture(std::string name)
{
	/*SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( name.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        SDL_FreeSurface( loadedImage );
    }
	
	GLuint texture;
	
	if( optimizedImage != NULL )
    {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexImage2D(   GL_TEXTURE_2D,
                                    0, 
                                    4, 
                    optimizedImage->w, 
                    optimizedImage->h,
                                    0, 
							  GL_BGRA,
                     GL_UNSIGNED_BYTE, 
               optimizedImage->pixels);

		
		SDL_FreeSurface(optimizedImage);

        return texture;
     }

     return NULL;*/

		GLuint texture;		
	SDL_Surface *surface;	
	GLenum texture_format;
	GLint  nOfColors;
 
	if ( (surface = IMG_Load(name.c_str())) ) { 
	 
		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}
	 
		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}
	 
		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
					texture_format = GL_RGBA;
			else
					texture_format = GL_BGRA_EXT;
		} 
		
		else if (nOfColors == 3)     // no alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
					texture_format = GL_RGB;
			else
					texture_format = GL_BGR_EXT;
		} 
		
		else {
			printf("warning: the image is not truecolor..  this will probably break\n");
			// this error should not go unhandled
		}

		SDL_SetAlpha(surface, 0, 0);
	 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
		 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
		 
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
							  texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	} 

	else {
		printf("SDL could not load the image: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}    
		 
	if ( surface ) { 
		SDL_FreeSurface( surface );
	}

	return texture;
}