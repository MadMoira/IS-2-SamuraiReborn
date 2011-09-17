
#include "Animation.h"

Animation::Animation(int actualFrame, int maxFramesFromCurrentState, int returnFrame, AnimationDirection direction)
{
	currentFrame = actualFrame;
    maxFrames = maxFramesFromCurrentState;
	animationDirection = direction;
    incrementFrame = 1;
    frameRate = 50;
    oldTime = 0;
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
 
    currentFrame += incrementFrame;

    if( currentFrame + 1 > maxFrames)
	{
		currentFrame = returnFrame;
    }

	return currentFrame;
}

void Animation::setCurrentFrame(int frame)
{
    if( frame < 0 || frame >= maxFrames) 
	{
		return;
	}
 
    currentFrame = frame;
}

int Animation::changeAnimationDirection(AnimationDirection direction)
{
	if ( animationDirection != direction )
	{
		animationDirection = direction;
		return -1;
	}

	return 1;
}



