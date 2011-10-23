#include "Pathfinding.h"
#include <algorithm>
#include "PlayerStateManager.h"

Pathfinding::Pathfinding(void)
{
	level = new LevelGraph(6400,720);
	x=y=0;
}
	
void Pathfinding::goToPlayer(Enemy *enemy, Player* player){							//only function to be called
	int xPlayer = (int)player->getPlayerSprite()->getPosX();
	int yPlayer = (int)player->getPlayerSprite()->getPosY();
	int xEnemy	= (int)enemy->getEnemySprite()->getPosX();
	int yEnemy	= (int)enemy->getEnemySprite()->getPosY();
	if(xEnemy>xPlayer){
		direction=SpriteData::LEFT;
	}
	else{
		direction=SpriteData::RIGHT;
	}
	openNodes.clear();																//clear previous iterations
	closedNodes.clear();															//
	int cost=0;																		//----
	int heuristic=0;																//set the initial values of the path
	int scoreFunction=0;															//
	setVariablesByPosition(xPlayer,yPlayer,cost,heuristic,scoreFunction);			//----
	PathNode *playerNode = level->getNodeByPosition(xPlayer,yPlayer);				//pointer to starting node
	PathNode *enemyNode(level->getNodeByPosition(xEnemy,yEnemy));					//pointer to goal node
	openNodes.push_back(playerNode);												//algoritm starts with current node open
	PathNode* currentNode;															//node to be used on the iterations
	while(!openNodes.empty()){														//and while the path its not a dead end
		currentNode = openNodes.back();												//assign the front of the min heap to currentNode,
		if(currentNode->getID()==enemyNode->getID()){								//if we are there 
			if(abs(xPlayer-xEnemy)<10){												//and the distance is to short
				return;																//do nothing
			}																		//otherwise
			calculatePath(enemyNode,playerNode);									//calculate the valid path
			goToPosition(enemy);													//then follow the player with AI function
			return;
		}
		else{																		//if not	
			PathNode* currentClosedNode = currentNode;
			closedNodes.push_back(currentClosedNode);								//--the current node is now 
			openNodes.pop_back();													//--closed
			std::pop_heap(openNodes.begin(),openNodes.end(),HeapCompare());			//(rearrange heap after pop)
			for(unsigned i=0;i<currentNode->getAdjacentNodes()->size();i++){		//and for its adjacent nodes
				std::vector<int> *vect = currentNode->getAdjacentNodes();
				PathNode* adjacentNode = level->getNodeByID(currentNode->getAdjacentNodes()->at(i));
				if(!searchNode(adjacentNode,openNodes)){							//if it isnt on the open list
					if(!searchNode(adjacentNode,closedNodes)){						//and it isnt in the closed list
						//and if it isnt a colision then
						adjacentNode->cost=1;										//asign costs
						adjacentNode->heuristic=(GLfloat)abs(enemyNode->getID()
													- currentNode->getID());		//and heuristics
						adjacentNode->scoreFunction=(GLfloat)currentNode->scoreFunction + 
													adjacentNode->cost +
													adjacentNode->heuristic;		//and finally calculate the score function
						openNodes.push_back(adjacentNode);							//add it to openlist
						std::push_heap(openNodes.begin(),openNodes.end(),HeapCompare());//rearrange heap
						//end if colision
					}
				}
			}
		}
	}
}

bool Pathfinding::searchNode(PathNode *node, std::vector<PathNode*> vector){
	if(vector.size()>0){
		for (unsigned i=0;i<vector.size();i++) {	
			if(vector[i]->getID()==node->getID()){
				return true;
			}
		}		
	}
	return false;
}

void Pathfinding::calculatePath(PathNode* node,PathNode* goalNode){
	path.clear();
	PathNode* pathNode;
	pathNode=node;
	pathNode->scoreFunction=FLT_MAX;
	path.push_back(pathNode);
	while(pathNode->getID()!=goalNode->getID()){
		GLfloat tentativeMinScore=FLT_MAX;
		PathNode* tempPathNode;
		for(unsigned i=0;i<pathNode->getAdjacentNodes()->size();i++){
			PathNode* adjacentNode = level->getNodeByID(pathNode->getAdjacentNodes()->at(i));
			if(adjacentNode->scoreFunction<tentativeMinScore){
				tentativeMinScore=adjacentNode->scoreFunction;
				tempPathNode=adjacentNode;
			}
			adjacentNode->scoreFunction=FLT_MAX;
		}
		path.push_back(tempPathNode);
		pathNode=tempPathNode;
	}
	path.push_back(pathNode);
}

void Pathfinding::setVariablesByPosition(int x, int y, int cost, int heuristic, int score){
	level->getNodeByPosition(x,y)->cost=(GLfloat)cost;
	level->getNodeByPosition(x,y)->heuristic=(GLfloat)heuristic;
	level->getNodeByPosition(x,y)->scoreFunction=(GLfloat)score;
}

void Pathfinding::goToPosition(Enemy* enemy){
	enemy->getEnemySprite()->changeStateEnemySprite(WALKING_STATE);	
	if(enemy->getEnemySprite()->getHandlerAnimation()->getAnimationDirection()!=direction){
		enemy->getEnemySprite()->getHandlerAnimation()->changeAnimationDirection(direction);
		enemy->getEnemySprite()->setConstantSpeedX(-1);
	}		
	enemy->walk();
}

Pathfinding::~Pathfinding(void)
{	
	openNodes.clear();
	closedNodes.clear();
	delete level;
}
