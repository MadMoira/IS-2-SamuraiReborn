#include "CollisionObserver.h"

CollisionObserver::CollisionObserver(){
	enemies=NULL;
	players=NULL;
}

CollisionObserver::~CollisionObserver(void){
}

bool CollisionObserver::checkCollision( CollisionBox &A, CollisionBox &B , float direction){

	//If any sides from A is inside of B
	if( ( /*( (A.gety()+A.geth()) > B.gety()) || ( A.gety() < (B.gety()+B.geth()) ) || */(( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw())) && direction>0.0) || (( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw())) && direction<0.0))){
		return true;
	}
	return false;
}