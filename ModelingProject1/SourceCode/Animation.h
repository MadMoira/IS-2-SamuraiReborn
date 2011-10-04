#pragma once

#include "SDL/SDL.h"

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

	void setCyclesPerFrame(int cycles) { numberCyclesPerFrame = cycles; }

	void setLoopPerAnimation(int loop) { loopPerAnimation = loop; }

	AnimationDirection getAnimationDirection() { return animationDirection; }
	int changeAnimationDirection(AnimationDirection direction);

private:
	int currentFrame, incrementFrame;
	int maxFrames, returnFrame;
	int numberCyclesPerFrame, loopPerAnimation;
	Uint32 frameRate, oldTime;
	AnimationDirection animationDirection;
};

