
#pragma once

namespace CollisionSystem
{
  struct DirectionsMove
  {
    bool canMoveXRight;
    bool canMoveXLeft;
    bool canMoveYUp;
    bool canMoveYDown;
  };

  struct CharacterMovement
  {
	bool playerMoveInX;
	bool playerMoveInY;
	bool playerMoveInXInCurrentFrame;
	bool playerMoveInYInCurrentFrame;
  };
}