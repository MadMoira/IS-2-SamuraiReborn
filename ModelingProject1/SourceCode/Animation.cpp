
#include "Animation.h"

Animation::Animation(int actualFrame, int maxFramesFromCurrentState, int returnFrame, SpriteData::AnimationDirection direction)
{
	currentFrame = actualFrame;
    maxFrames = maxFramesFromCurrentState;
	animationDirection = direction;
    incrementFrame = 1;
    frameRate = 30;
    oldTime = 0;
	numberCyclesPerFrame = 0;
	loopPerAnimation = 0;
	this->returnFrame = returnFrame;
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
 
	
	if ( loopPerAnimation == numberCyclesPerFrame )
	{
		currentFrame += incrementFrame;
		loopPerAnimation = 0;

		if( currentFrame > maxFrames)
		{
			currentFrame = returnFrame;
		}
	}

	else
	{
	  loopPerAnimation += 1;
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



