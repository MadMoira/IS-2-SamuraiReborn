#pragma once

#include "SDL.h"

enum AnimationDirection
{
	RIGHT,
	LEFT
};

class Animation
{
public:
	Animation(int actualFrame, int maxFramesFromCurrentState, int returnFrame, AnimationDirection direction);
	~Animation(void);
 
    int animate();

	void setFrameRate(int rate) { frameRate = rate; }
 
	int getCurrentFrame() { return currentFrame; }
    void setCurrentFrame(int frame);

	void setMaxFrame(int max) { maxFrames = max; }

	void setReturnFrame(int returnFrame) { this->returnFrame = returnFrame; }

	AnimationDirection getAnimationDirection() { return animationDirection; }
	int changeAnimationDirection(AnimationDirection direction);

private:
	int currentFrame, incrementFrame;
	int maxFrames;
	int returnFrame;
	Uint32 frameRate, oldTime;
	AnimationDirection animationDirection;
};

