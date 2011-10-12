#include "Collider.h"

Collider::Collider(boost::ptr_vector< Enemy > *enemiesList, boost::ptr_vector< Player > *playersList){
	enemies=enemiesList;
	players=playersList;
}

Collider::~Collider(void){
}

//Method to check for collisions between two collision boxes
 bool Collider::checkCollision( CollisionBox &A, CollisionBox &B , float directionX){

	//Collisions for left to right, right to left and up to down
	if( ( ( ((A.gety()+A.geth()) > B.gety()) && ( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw()))) || (( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw())) && directionX>0.0) || (( (A.getx()+A.getw()) > (B.getx()) ) && ( A.getx() < (B.getx()+B.getw())) && directionX<0.0))){
		return true;
	}
	return false;
}

bool Collider::checkTileCollision( Sprite &A, float directionX){
	for(int i=A.getPosX();i<=A.getWidth();i++){
		for(int j=A.getPosY();j<=A.getHeight();j++){
			if(true/*Function to handle the collisions*/){
				return true;
			}
		}
	}	
	return false;
}

bool Collider::checkEnemiesCollision( CollisionBox &A, float directionX){
	for(int i=0; i==enemies->size(); i++){
		if(checkCollision(A, *enemies->at(i).getSprite()->getCollisionBox(), directionX)){
			return true;
		}
	}
	return false;
}


boost::ptr_vector< Enemy > Collider::checkAttackCollision( CollisionBox &A, float directionX){
	boost::ptr_vector< Enemy > enemiesCollided;
	for(int i=0; i==enemies->size(); i++){
		if(checkCollision( A, *enemies->at(i).getSprite()->getCollisionBox(), directionX)){
			enemiesCollided.push_back(&enemies->at(i));
		}
	}
	return enemiesCollided;
}

boost::ptr_vector< Player > Collider::checkEnemiesAttackCollision( CollisionBox &A, float directionX){
	boost::ptr_vector< Player > playersCollided;
	for(int i=0; i==players->size(); i++){
		if(checkCollision( A, *players->at(i).getPlayerSprite()->getCollisionBox(), directionX)){
			playersCollided.push_back(&players->at(i));
		}
	}
	return playersCollided;
}

bool Collider::onTheGround( Sprite &A, float directionX){
	for(int i=A.getPosX();i<=A.getWidth();i++){
		if(true/*Function to handle the Tile collisions*/){
			return true;	}
	}	
	return false;
}