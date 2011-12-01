#pragma once

namespace GamePhysics
{
  enum PhysicModes
  {
    RIGID_BODY
  };

  enum PhysicMovements
  {
    X,
    Y,
  };

  enum AccelerationState
  {
	NO_ACCELERATE,
	ACCELERATE,
	DECELERATE,
  };
}