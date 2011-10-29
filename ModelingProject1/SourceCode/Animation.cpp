
#include "Animation.h"

Animation::Animation(int actualFrame, int maxFramesFromCurrentState, int returnFrame, int framerate,
	                 SpriteData::AnimationDirection direction)
{
  currentFrame = actualFrame;
  maxFrames = maxFramesFromCurrentState;
  animationDirection = direction;
  incrementFrame = 1;
  frameRate = framerate;
  oldTime = SDL_GetTicks();
  this->returnFrame = returnFrame;
  animationAlreadyEnd = false;
}

Animation::~Animation(void)
{
}

int Animation::animate() 
{
  if( oldTime + frameRate > SDL_GetTicks() ) 
  {
    return -1;
  }
 
  oldTime += frameRate;

  animationAlreadyEnd = false;
  if ( maxFrames > 0 )
  {
    currentFrame += incrementFrame;
    if( currentFrame > maxFrames )
    {
      animationAlreadyEnd = true;
	  currentFrame = returnFrame;
	}
  }

  return currentFrame;
}

void Animation::setCurrentFrame(int frame)
{
  if( frame < 0 || frame > maxFrames) 
  {
    currentFrame = returnFrame;
    return;
  }
 
  currentFrame = frame;
}

int Animation::changeAnimationDirection(int direction)
{
  if ( animationDirection != direction )
  {
    animationDirection = direction;
    return -1;
  }

  return 1;
}

int Animation::returnAnimationDirectionAxisValue()
{
  if ( animationDirection == SpriteData::RIGHT )
  {
    return 1;
  }

  return -1;
}



