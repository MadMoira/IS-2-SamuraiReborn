#include "GameCore.h"
#include "Level.h"
#include <windows.h>
#include <gl\GL.h>

enum{right, left};

class test {
	
	private:
		int velx, vely;
		int status;

	public:
		test(void);
		int getx();
		int gety();
		void setTest1(GLuint);
		bool handle_events(SDL_Event);
		void move();

		int x, y;
		int offsetx, offsety;
		int frame;
		GLuint text1;
		GLuint getText1();

};

int test::getx(){
	return x;
}

int test::gety(){
	return y;
}

GLuint test::getText1(){
	return text1;
}

void test::setTest1(GLuint sprite){
	text1 = sprite;
}


bool test::handle_events(SDL_Event evento){
	if( evento.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP: vely -= 4 ; break;
            case SDLK_DOWN: vely += 4 ; break;
            case SDLK_LEFT: velx -= 4 ; break;
            case SDLK_RIGHT: velx += 4 ; break;    
        }
		return true;
    }

	else if( evento.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( evento.key.keysym.sym )
        {
            case SDLK_UP: vely += 4 ; break;
            case SDLK_DOWN: vely -= 4 ; break;
            case SDLK_LEFT: velx += 4 ; break;
            case SDLK_RIGHT: velx -= 4 ; break;   
        }
		return false;
    }
	return false;
}

test::test(void) 
{
	x = 0;
	y = 0;
	velx = 0;
	vely = 0;
	offsetx = 600;
	offsety = 320;
	frame = 0;
	status = right;
}	

void test::move(){

	offsetx += velx;
    frame++;
    //Keep the stick figure in bounds
    if( ( x < 0 ) || ( offsetx > 1280 ) )
    {
        x -= velx;    
    }

	

	offsety += vely;
    frame++;
    //Keep the stick figure in bounds
    if( ( y < 0 ) || ( offsety + 100 > 1280 ) )
    {
        y -= vely;    
    }

}

void cleanup(){

	SDL_Quit();

}

int main( int argc, char* args[] )
{
	GameCore Core;
	test test1;
	
	if(Core.initGame() == false)
	{
		return 1;
	}

	test1.setTest1(Core.loadTexture("Panda - SpriteSheet.png"));

	/*Level *levelOne = new Level();
	levelOne->loadTMXTileMapFile("test1.tmx");	
	
	levelOne->drawLevelMap();*/

	//GLuint texture1 = Core.loadTexture("Mov1.png");
	//GLuint texture2 = Core.loadTexture("InitialPosition.png");
	//GLuint textureBackground = Core.loadTexture("background.png");

	//Core.drawTexture(textureBackground, 0.0f, 0.0f, 1280.0f, 720.0f);
    //Core.drawTexture(texture1, 0.0f, 100.0f, 800.0f, 600.0f);

	//glTranslatef(100.0f, 130.0f, 0.0f);

	//Core.drawTexture(texture2, 0.0f, 0.0f, 800.0f, 600.0f);
			
	bool quit = false;
	SDL_Event evento;

	while( !quit )
	{
		Core.startTimer();
		
		while( SDL_PollEvent( &evento ) )
		{

			test1.handle_events(evento);
			if( evento.type == SDL_KEYDOWN )
			{
				if(evento.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
			}
			if(evento.type == SDL_QUIT){
				quit = true;
			}
		}

		test1.move();
		glClear( GL_COLOR_BUFFER_BIT );
		Core.show(test1.x, test1.y, test1.text1, test1.frame, test1.offsetx, test1.offsety);
		SDL_GL_SwapBuffers();			
		Core.setupFPS();
	}

	

	//glDeleteTextures(1, &texture1);
	//glDeleteTextures(1, &texture2);
	//glDeleteTextures(1, &textureBackground);
	//delete levelOne;
	glDeleteTextures(1, &test1.text1);
	Core.getGameSound()->closeAll();
	cleanup();
	

	
    return 0;
}
