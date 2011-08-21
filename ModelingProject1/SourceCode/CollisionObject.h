#pragma once

enum CollisionProperty
{
	FULL_COLLISION
};

class CollisionObject
{
public:
	CollisionObject(void);
	~CollisionObject(void);

private:
	int propertyObj, specialCollision, tileNumber;
};
