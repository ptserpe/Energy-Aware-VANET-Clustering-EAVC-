
/*
 * This file simply contains the function that calls the APROVE algorithm
 */

#ifndef FUZZYLOGICALGORITHM_H
#define FUZZYLOGICALGORITHM_H
#include "Movement.h"
#include "HelloBeaconMessage.h"
#include "NeighborListEntry.h"
#include <iostream>
#include <vector>


/*All the following values may vary, in order to succeed different and maybe more stable clusters.*/

#define TAF_F 5		//(time future parameter) seconds from now to calculate the next estimated position
#define T_H 1		//(time between hellos)

#define T_M 1		//(message period) T_M must be small enough to allow the algorithm to converge within
					//the CI period
					//e.g. a neighborhood of 40 nodes can converge in less than 10 iterations.
					//     So a T_M = 1s requires a minimum CI = 10s.
#define CI 10		//(clustering Interval) Interval to make a clustering decision

#define T_CM 1		//(cluster maintenance period) Every T_CM node i clears its neighbor list by checking the t_expire
					//field and checks if he still has a clusterhead

#define T_UP 1
#define DAMPING_A 0.7
#define EXPIRE_TIME_DEFAULT 4

#define VFO 1.0
#define LF0 0.0
#define SQF0 0.0
#define HELLORECIEVED 0
#define HELLOSENT 0

using namespace std;



void fuzzyLogicAlgorithm(int periodTimes, int numberOfNodes, Movement **movement, float transmission_radius);

int checkSameDirection(float vel_x_i, float vel_x_j, float vel_y_i, float vel_y_j); //find the number of nodes moving towards the same direction

float calculateVelocityFactor_i_j(float vel_x_j, float vel_y_j, float maxV, float minV); //, float v_g_min, float v_g_max

float calculateLeadershipFactor_i_j(int c_i, int maxC); //, int c_g_max

float calculateSQF_i(int num_hello_recived, int num_hello_sent);


string calculateRank(string VF, string LF, string SQF);
//float calculateCompetencyValue(vector<NeighborListEntry>* neighborList_I, int id);


#endif //FUZZYLOGICALGORITHM_H
