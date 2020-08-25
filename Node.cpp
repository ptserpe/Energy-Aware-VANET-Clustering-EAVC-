#include <iostream>
#include <string.h>
#include <cmath>

#include "Node.h"


Node::Node(){
	nodeID = -1;
}

Node::Node(int id, int stat, int ch, float vf, float lf, float sqf, float cv, int c){
    nodeID = id;
    status = stat;
    clusterhead = ch;
    VF = vf;
    LF = lf;
    SQF =sqf;
    competencyValue = cv;
    cnt = c;

}

Node::~Node(){
    //dtor
}


int Node::getNodeID(){
	return nodeID;
}

int Node::getStatus(){
	return status;
}

int Node::getClusterhead(){
	return clusterhead;
}

float Node::getVF(){
    return VF;
}

float Node::getLF(){
    return LF;
}

float Node::getSQF(){
    return SQF;
}

float Node::getCV(){
    return competencyValue;
}

int Node::getCnt(){
    return cnt;
}

void Node::setNodeID(int id){
	nodeID = id;
}

void Node::setStatus(int stat){
	status = stat;
}

void Node::setClusterhead(int ch){
	clusterhead = ch;
}

void Node::setCnt(int c){
	cnt = c;
}


void Node::setAll(int id, int stat, int ch, float vf, float lf, float sqf, float cv, int c){
	nodeID = id;
	status = stat;
	clusterhead = ch;
	VF = vf;
	LF = lf;
	SQF = sqf;
	competencyValue = cv;
	cnt = c;
}


/* It simply empties the vector of HelloBeaconMessage.
 */
void Node::emptyNeighborsVector(){
	neighborList_I.clear();
}


/*Checks the size of the vector
 */
int Node::sizeNeighborsVector(){
	return neighborList_I.size();
}


ostream& operator << (ostream& outs, const Node& aNode){
    outs << "\tNode details: "
        << "\t<ID: " <<  aNode.nodeID
		 << "\tstatus: " << aNode.status
		 << "\tclusterhead: " << aNode.clusterhead
		 << ">\n";


	return outs;
}
