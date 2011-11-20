
#include "Animation.h"

Animation::Animation(int actualFrame, int currentState, SpriteData::AnimationDirection direction, 
	                 std::vector< int > maxFrames, std::vector< int > returnFrames, std::vector< int > framerates)
{
  currentFrame = actualFrame;
  this->currentState = currentState;
  animationDirectionX = direction;
  animationDirectionY = SpriteData::NO_DIRECTION;
  incrementFrame = 1;
  oldTime = SDL_GetTicks();
  animationAlreadyEnd = false;

  maxFramesPerAnimation = maxFrames;
  returnFramesPerAnimation = returnFrames;
  frameratePerAnimation = framerates;
}

Animation::~Animation(void)
{
  maxFramesPerAnimation.clear();
  returnFramesPerAnimation.clear();
  frameratePerAnimation.clear();
}

int Animation::animate() 
{
  if( oldTime + frameratePerAnimation.at(currentState) > SDL_GetTicks() ) 
  {
    return -1;
  }
 
  oldTime += frameratePerAnimation.at(currentState);

  animationAlreadyEnd = false;
  if ( maxFramesPerAnimation.at(currentState) > 0 )
  {
    currentFrame += incrementFrame;
    if( currentFrame > maxFramesPerAnimation.at(currentState) )
    {
      animationAlreadyEnd = true;
	  currentFrame = returnFramesPerAnimation.at(currentState);
	}
  }

  return currentFrame;
}

void Animation::setCurrentStateForAnimation(int state)
{
  currentState = state;
}

void Animation::setCurrentFrame(int frame)
{
  if( frame < 0 || frame > maxFramesPerAnimation.at(currentState)) 
  {
    currentFrame = returnFramesPerAnimation.at(currentState);
    return;
  }
 
  currentFrame = frame;
}

int Animation::changeAnimationDirection(int direction)
{
  if ( animationDirectionX != direction )
  {
    animationDirectionX = direction;
    return -1;
  }

  return 1;
}

int Animation::returnAnimationDirectionAxisValue()
{
  if ( animationDirectionX == SpriteData::LEFT )
  {
	return 1;
  }
  return -1;
}

void Animation::changeDirectionY(float speed)
{
  if ( speed > 0.0f )
  {
    animationDirectionY = SpriteData::DOWN;
	return;
  }
  else if ( speed < 0.0f )
  {
    animationDirectionY = SpriteData::UP;
	return;
  }

  animationDirectionY = SpriteData::NO_DIRECTION;
}


