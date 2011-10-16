#pragma once

#include "SDL/SDL.h"
#include "SpriteDataConstants.h"

class Animation
{
public:
	Animation(int actualFrame, int maxFramesFromCurrentState, int returnFrame, SpriteData::AnimationDirection direction);
	~Animation(void);
 
    int animate();

	void setFrameRate(int rate) { frameRate = rate; }
 
	int getCurrentFrame() { return currentFrame; }
    void setCurrentFrame(int frame);
	void restartCurrentFrame() { currentFrame = 1; }

	void setMaxFrame(int max) { maxFrames = max; }

	void setReturnFrame(int returnFrame) { this->returnFrame = returnFrame; }

	void setCyclesPerFrame(int cycles) { numberCyclesPerFrame = cycles; }

	void setLoopPerAnimation(int loop) { loopPerAnimation = loop; }

	int getAnimationDirection() { return animationDirection; }
	int changeAnimationDirection(int direction);

private:
	int currentFrame, incrementFrame;
	int maxFrames, returnFrame;
	int numberCyclesPerFrame, loopPerAnimation;
	Uint32 frameRate, oldTime;
	int animationDirection;
};

