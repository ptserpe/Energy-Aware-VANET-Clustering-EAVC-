#include "NeighborListEntry.h"

#include <iostream>

using namespace std;


NeighborListEntry::NeighborListEntry(){
	nodeID_j = -1;
}

NeighborListEntry::NeighborListEntry(int id, float x, float y, float vel_x, float vel_y, float vf_i_j, float lf_i_j, float sqf_j, string c_v_j, int CH_converge, int CH, int expirationTime){
	nodeID_j = id;
	nodePosition_j.x = x;
	nodePosition_j.y = y;
	nodeVelocity_j.v_x = vel_x;
	nodeVelocity_j.v_y = vel_y;
	velocityfactor_i_j = vf_i_j;
	leadershipfactor_i_j = lf_i_j;
	SQF_j = sqf_j;
	competency_value_j = c_v_j;
	CH_cnvg_j = CH_converge;
	CH_j = CH;
	t_expire = expirationTime;
}

NeighborListEntry::~NeighborListEntry(){

}

int NeighborListEntry::getNodeID(){
	return nodeID_j;
}

float NeighborListEntry::getGpsX(){
	return nodePosition_j.x;
}

float NeighborListEntry::getGpsY(){
	return nodePosition_j.y;
}

float NeighborListEntry::getVelocityX(){
	return nodeVelocity_j.v_x;
}

float NeighborListEntry::getVelocityY(){
	return nodeVelocity_j.v_y;
}

float NeighborListEntry::getVF_i_j(){
	return velocityfactor_i_j;
}

float NeighborListEntry::getLF_i_j(){
	return leadershipfactor_i_j;
}

float NeighborListEntry::getSQF_j(){
	return SQF_j;
}

string NeighborListEntry::getCV_j(){
    return competency_value_j;
}


int NeighborListEntry::getClusterheadConverge(){
	return CH_cnvg_j;
}

int NeighborListEntry::getClusterhead(){
	return CH_j;
}

int NeighborListEntry::getExpirationTime(){
	return t_expire;
}

void NeighborListEntry::setNodeID(int id){
	nodeID_j = id;
}

void NeighborListEntry::setGps(float x, float y){
	nodePosition_j.x = x;
	nodePosition_j.y = y;
}

void NeighborListEntry::setVelocity(float vel_x, float vel_y){
	nodeVelocity_j.v_x = vel_x;
	nodeVelocity_j.v_y = vel_y;
}

void NeighborListEntry::setVF_i_j(float vf_i_j){
	velocityfactor_i_j = vf_i_j;
}

void NeighborListEntry::setLF_i_j(float lf_i_j){
	leadershipfactor_i_j = lf_i_j;
}

void NeighborListEntry::setSQF_j(float sqf_j){
	SQF_j = sqf_j;
}

void  NeighborListEntry::setCV_j(string c_v_j){
    competency_value_j = c_v_j;
}

void NeighborListEntry::setClusterheadConverge(int CH_converge){
	CH_cnvg_j = CH_converge;
}

void NeighborListEntry::setClusterhead(int CH){
	CH_j = CH;
}

void NeighborListEntry::setExpirationTime(int expirationTime){
	t_expire = expirationTime;
}

void NeighborListEntry::setAll(int id, float x, float y, float vel_x, float vel_y, float vf_i_j, float lf_i_j, float sqf_j, string c_v_j, int CH_converge, int CH, int expirationTime){
	nodeID_j = id;
	nodePosition_j.x = x;
	nodePosition_j.y = y;
	nodeVelocity_j.v_x = vel_x;
	nodeVelocity_j.v_y = vel_y;
	velocityfactor_i_j = vf_i_j;
	leadershipfactor_i_j = lf_i_j;
	SQF_j = sqf_j;
	competency_value_j = c_v_j;
	CH_cnvg_j = CH_converge;
	CH_j = CH;
	t_expire = expirationTime;
}

ostream& operator << (ostream& outs, const NeighborListEntry& aNeighborListEntry){
	outs << "ID:  " << aNeighborListEntry.nodeID_j <<
	"\tposition (" << aNeighborListEntry.nodePosition_j.x << ", " << aNeighborListEntry.nodePosition_j.y <<
	") \tvelocity: (" << aNeighborListEntry.nodeVelocity_j.v_x << ", " << aNeighborListEntry.nodeVelocity_j.v_y <<
	") \tVF_i_j: " << aNeighborListEntry.velocityfactor_i_j <<
	"\tLF_i_j: " << aNeighborListEntry.leadershipfactor_i_j <<
	"\tSQF_j: " << aNeighborListEntry.SQF_j <<
	"\tCV_j:" <<aNeighborListEntry.competency_value_j<<
	"\tCH_cnvg_j: " << aNeighborListEntry.CH_cnvg_j <<
	"\tCH_j: " << aNeighborListEntry.CH_j <<
	"\tt_expire: " << aNeighborListEntry.t_expire <<
	"\n";
	return outs;
}
