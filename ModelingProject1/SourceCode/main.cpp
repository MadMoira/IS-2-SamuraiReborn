#include "GameCore.h"
#include "Level.h"
#include <windows.h>
#include <gl\GL.h>
#include "CollisionObserver.h"

int main( int argc, char* args[] ){

	GameCore Core;
	CollisionObserver observer = CollisionObserver();

	if(Core.initGame() == false){
		return 1;
	}

	//motion rate
	float x=0.0f;
	float dx;

	//collision boxes
	CollisionBox box1= CollisionBox(x+80, 100 , 139,  498); // Meerkat
	CollisionBox box2= CollisionBox(250+246, 100 , 265,  537); // Panda

	//Images
	GLuint texture1 = Core.loadTexture("Mov1.png");

	GLuint texture2 = Core.loadTexture("InitialPosition.png");

	GLuint textureBackground = Core.loadTexture("background.jpg");

	bool quit = false;
	SDL_Event evento;
	while( !quit ){

		while( SDL_PollEvent( &evento ) ){
			if( evento.type == SDL_KEYDOWN ){
				if(evento.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
				if(evento.key.keysym.sym == SDLK_RIGHT){
					dx = 20.0f;
					x+=dx;
					box1.setx(x+80);
					if(observer.checkCollision(box1,box2,dx)==true){
						x-=dx;
					}
					box1.setx(x+80);
				}
				if(evento.key.keysym.sym == SDLK_LEFT){
					dx = -20.0f;
					x+=dx;
					box1.setx(x+80);
					if(observer.checkCollision(box1,box2,dx)==true){
						x-=dx;
					}
					box1.setx(x+80);
				}
				if(evento.key.keysym.sym == SDLK_1){
					x=1000.0;
				}
				if(evento.key.keysym.sym == SDLK_2){
					x=0.0;
				}
			}  
			if(evento.type == SDL_QUIT){
				quit = true;
			}
		}

		Core.drawTexture(textureBackground, 0.0f, 0.0f, 1280.0f, 720.0f);

		Core.drawTexture(texture1, x, 100.0f, 800.0f, 600.0f);

		Core.drawTexture(texture2, 250.0f, 100.0f, 800.0f, 600.0f);

		SDL_GL_SwapBuffers();
	}

	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glDeleteTextures(1, &textureBackground);
	//delete levelOne;

	SDL_Quit();

	return 0;
}