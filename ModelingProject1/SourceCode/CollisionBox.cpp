#include "CollisionBox.h"

CollisionBox::CollisionBox(float x, float y ,float w, float h){
	box.x= x;
	box.y= y;
	box.w = w;
	box.h = h;
}

CollisionBox::~CollisionBox(void){
}

void CollisionBox::setx(float n){
	box.x=n;
}
void CollisionBox::sety(float n){
	box.y=n;
}
float CollisionBox::getx(){
	return box.x;
}
float CollisionBox::gety(){
	return box.y;
}
float CollisionBox::geth(){
	return box.h;
}
float CollisionBox::getw(){
	return box.w;
}