#pragma once

#include "SDL/SDL.h"
#include "SpriteDataConstants.h"

class Animation
{
public:
	Animation(int actualFrame, int maxFramesFromCurrentState, int returnFrame, int framerate,
		      SpriteData::AnimationDirection direction);
	~Animation(void);
 
    int animate();

	bool getAnimationAlreadyEnd() { return animationAlreadyEnd; }
 
	int getCurrentFrame() { return currentFrame; }
    void setCurrentFrame(int frame);
	void restartCurrentFrame() { currentFrame = 1; }

	void setMaxFrame(int max) { maxFrames = max; }

	void setReturnFrame(int returnFrame) { this->returnFrame = returnFrame; }

	void setFrameRate(int frame) { frameRate = frame; }

	void restartOldTime() { oldTime = SDL_GetTicks(); }

	int getAnimationDirection() { return animationDirection; }
	int changeAnimationDirection(int direction);

private:
	int currentFrame, incrementFrame;
	int maxFrames, returnFrame;
	Uint32 frameRate, oldTime;
	int animationDirection;
	bool animationAlreadyEnd;
};

