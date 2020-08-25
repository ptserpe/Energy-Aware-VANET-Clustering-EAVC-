#include "HelloBeaconMessage.h"
#include <iostream>

using namespace std;


HelloBeaconMessage::HelloBeaconMessage(){
	nodeID_j = -1;
}

HelloBeaconMessage::HelloBeaconMessage(int id, float x, float y, float vel_x, float vel_y, int cs, int receiver){
	nodeID_j = id;
	nodePosition_j.x = x;
	nodePosition_j.y = y;
	nodeVelocity_j.v_x = vel_x;
	nodeVelocity_j.v_y = vel_y;
	cs_id = cs;
	nodeID_i = receiver;
}

HelloBeaconMessage::~HelloBeaconMessage(){

}

int HelloBeaconMessage::getNodeID(){
	return nodeID_j;
}

float HelloBeaconMessage::getGpsX(){
	return nodePosition_j.x;
}
float HelloBeaconMessage::getGpsY(){
	return nodePosition_j.y;
}

float HelloBeaconMessage::getVelocityX(){
	return nodeVelocity_j.v_x;
}

float HelloBeaconMessage::getVelocityY(){
	return nodeVelocity_j.v_y;
}

int HelloBeaconMessage::getNumberOfNodesMovingTowardsTheSameDirection(){
	return cs_id;
}

int HelloBeaconMessage::getReceiver(){
	return nodeID_i;
}

void HelloBeaconMessage::setNodeID(int id){
	nodeID_j = id;
}

void HelloBeaconMessage::setGps(float x, float y){
	nodePosition_j.x = x;
	nodePosition_j.y = y;
}

void HelloBeaconMessage::setVelocity(float vel_x, float vel_y){
	nodeVelocity_j.v_x = vel_x;
	nodeVelocity_j.v_y = vel_y;
}

void HelloBeaconMessage::setNumberOfNodesMovingTowardsTheSameDirection(int cs){
	cs_id = cs;
}

void HelloBeaconMessage::setAll(int id, float x, float y, float vel_x, float vel_y, int cs, int receiver){
	nodeID_j = id;
	nodePosition_j.x = x;
	nodePosition_j.y = y;
	nodeVelocity_j.v_x = vel_x;
	nodeVelocity_j.v_y = vel_y;
	cs_id = cs;
	nodeID_i = receiver;
}

void HelloBeaconMessage::setReceiver(int id){
	nodeID_i = id;
}

ostream& operator << (ostream& outs, const HelloBeaconMessage& aHelloBeaconMessage){
	outs << "\tHELLO Receiver: " << aHelloBeaconMessage.nodeID_i << "\t<ID: " << aHelloBeaconMessage.nodeID_j << " position (" << aHelloBeaconMessage.nodePosition_j.x << ", " << aHelloBeaconMessage.nodePosition_j.y << ")  velocity: (" << aHelloBeaconMessage.nodeVelocity_j.v_x << ", " << aHelloBeaconMessage.nodeVelocity_j.v_y << ")  NumberOfNodesMovingTowardsTheSameDirection: " << aHelloBeaconMessage.cs_id << ">\n";
	return outs;
}
