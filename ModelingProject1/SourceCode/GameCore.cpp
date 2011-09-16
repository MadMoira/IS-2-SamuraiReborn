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
	SDL_Surface* loadedImage = NULL;

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

     return NULL;
}

void GameCore::drawTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat offx, GLfloat offy)
{

	glBindTexture( GL_TEXTURE_2D, texture );

	glBegin( GL_QUADS );
				//Top-left vertex (corner)
				glTexCoord2i( 0, 0 );
				glVertex3f( x, y, 0.f );

				//Bottom-left vertex (corner)
				glTexCoord2i( 1, 0 );
				glVertex3f( x + offx, y, 0.f );
			 
				//Bottom-right vertex (corner)
				glTexCoord2i( 1, 1 );
				glVertex3f( x + offx, y + offy, 0.f );
			 
				//Top-right vertex (corner)
				glTexCoord2i( 0, 1 );
				glVertex3f( x,  y + offy, 0.f );
	glEnd();
}