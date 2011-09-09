#include "GameCore.h"
#include "Level.h"
#include <windows.h>
#include <gl\GL.h>
#include <SDL\SDL_mixer.h>

enum { right, left};

class test {
	
	private:
	
	int velx, vely;
	int status;
	
		
	public:
	int x, y;
	int frame;
	GLuint text1;
	test(void);
	int getx();
	int gety();
	GLuint getText1();
	void setTest1(GLuint sprite);
	void handle_events();
	void move();

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

test::test(void) 
{
	x = 0;
	y = 0;
	velx = 10;
	vely = 1;
	frame = 0;
	status = right;
}	

void test::move(){

	x += velx;
    frame++;
    //Keep the stick figure in bounds
    if( ( x < 0 ) || ( x + 1 > 1280 ) )
    {
        x -= velx;    
    }

}

void cleanup(){

	Mix_CloseAudio();
	Mix_Quit();
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

	/*Level *levelOne = new Level();
	levelOne->loadTMXTileMapFile("test1.tmx");	
	
	levelOne->drawLevelMap();*/

	GLuint texture1 = Core.loadTexture("Mov1.png");
	GLuint texture2 = Core.loadTexture("InitialPosition.png");
	GLuint textureBackground = Core.loadTexture("background.png");

	//Core.drawTexture(textureBackground, 0.0f, 0.0f, 1280.0f, 720.0f);
    //Core.drawTexture(texture1, 0.0f, 100.0f, 800.0f, 600.0f);

	glTranslatef(100.0f, 130.0f, 0.0f);

	Core.drawTexture(texture2, 0.0f, 0.0f, 800.0f, 600.0f);

	bool quit = false;
	
		
	SDL_Event evento;

	while( !quit )
	{
		while( SDL_PollEvent( &evento ) )
		{
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

		test1.setTest1(Core.loadTexture("Panda - SpriteSheet.png"));
		test1.move();
		
		glClear( GL_COLOR_BUFFER_BIT );
		Core.show(test1.x, test1.y, test1.text1, test1.frame);

		SDL_GL_SwapBuffers();
	}

	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glDeleteTextures(1, &textureBackground);
	//delete levelOne;

	cleanup();
	

	
    return 0;
}
