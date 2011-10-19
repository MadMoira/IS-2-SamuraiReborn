
#include "MeerkatP2.h"

MeerkatP2::~MeerkatP2()
{
}

void MeerkatP2::initializePlayer(IDSprites id, std::string filename, std::vector< Vector2f > speed,
				Vector2f pos, int initialFrame, std::vector < int > maxFrame, 
				std::vector < int > returnFrame, GLfloat widthSprite, GLfloat heightSprite,
				std::vector < int > framerateAnimations, std::vector< Vector2f> delayMovement)
{
  playerSprite = new Sprite(id, filename, speed, pos, initialFrame, maxFrame, returnFrame,
							widthSprite, heightSprite, framerateAnimations, delayMovement);
  inputMapper = new InputMapping::GameInputMapper();
  inputMapper->pushContext("maincontext");
  inputMapper->addCallback( Player::inputCallback, 0);
}

void MeerkatP2::noAction()
{
}

void MeerkatP2::walk()
{
}

void MeerkatP2::run()
{
}

void MeerkatP2::jump()
{
}

void MeerkatP2::draw()
{
  playerSprite->drawTexture();
}