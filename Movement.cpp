#include "Movement.h"
#include <iostream>

using namespace std;


Movement::Movement(){
	nodeID = -1;
}

Movement::Movement(int id, float x, float y, float velocity){
	nodeID = id;
	position.x = x;
	position.y = y;
	velocity = velocity;
}

Movement::~Movement(){

}

int Movement::getNodeID(){
	return nodeID;
}

float Movement::getGpsX(){
	return position.x;
}
float Movement::getGpsY(){
	return position.y;
}

float Movement::getVelocity(){
	return velocity;
}

void Movement::setNodeID(int id){
	nodeID = id;
}

void Movement::setGps(float x, float y){
	position.x = x;
	position.y = y;
}

void Movement::setVelocity(float vel){
	velocity = vel;
}

void Movement::setAll(int id, float x, float y, float vel){
	nodeID = id;
	position.x = x;
	position.y = y;
	velocity = vel;
}

ostream& operator << (ostream& outs, const Movement& aMovement){
	outs << "ID:  " << aMovement.nodeID << "\t (" << aMovement.position.x << ", " << aMovement.position.y << ") \tvelocity: " << aMovement.velocity << "\n";
	return outs;
}
