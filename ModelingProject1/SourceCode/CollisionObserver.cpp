#include "CollisionObserver.h"

CollisionObserver::CollisionObserver(){
	enemies=NULL;
	players=NULL;
}

CollisionObserver::~CollisionObserver(void){
}

//Method to check for collisions between two collision boxes
bool CollisionObserver::checkCollision( CollisionBox &A, CollisionBox &B , float directionX){

	//Collisions for left to right, right to left and up to down
	if( ( ( ((A.gety()+A.geth()) > B.gety()) && ( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw()))) || (( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw())) && directionX>0.0) || (( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw())) && directionX<0.0))){
		return true;
	}
	return false;
}