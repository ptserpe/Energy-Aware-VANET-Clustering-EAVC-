#include "Fuzzy_logic_algorithm.h"
#include <iostream>
#include <cmath>
#include "CFuzzyFunction.h"

//TOD INSERT NODES

using namespace std;

volatile const double cdMinimumPrice = 0;
volatile const double cdMaximumPrice = 1;

//I want a class about nodes
void fuzzyLogicAlgorithm(int periodTimes, int numberOfNodes, Movement **movement, float transmission_radius){
	int i, j, t, k;
	//int hello_recived,hello_sent; // hello_sent when I send to receiver i its parameter ++

	HelloBeaconMessage aHelloMessage;
    float velocityfactor_i_j, leadershipfactor_i_j, SQF_i;

    string competency_value_j;

    float eucleidianDistance;

    int *clusterheads;	//Parameter for the Procedure 1.
    int *sentHello;    //number of hello messages sent from all neighbors ,for all nodes
    int *receivedHello; //number of hello messages received from this node ,for all nodes

	float vel_x_i, vel_y_i, vel_x_j, vel_y_j;
	float maxVelocity, minVelocity;
	int cs_j =0 , c_i = 0;
	int maxCnt;

    string *competency_value;
	competency_value = new string[numberOfNodes];

	int found_flag;
	vector<int> possible_clusterheads;
	vector<int>::iterator possible_clusterheadsIt;

	vector<NeighborListEntry> *neighborList_I;
	vector<NeighborListEntry>::iterator nListIt;

    neighborList_I = new vector<NeighborListEntry>[numberOfNodes];

    clusterheads = new int[numberOfNodes];
	for(i=0; i<numberOfNodes; i++){
		clusterheads[i] = -1;
	}

	sentHello = new int[numberOfNodes];
	for(i=0; i<numberOfNodes; i++){
        sentHello[i] = 0; //initialize
	}

    receivedHello = new int[numberOfNodes];
	for(i=0; i<numberOfNodes; i++){
        receivedHello[i] = 0; //initialize
	}

	for(t=0; t<periodTimes; t++){		//advance of time
										//Here will be specified the "time cases" concerning which decision the nodes
										//have to take.

		cout << "TIME : " << t << endl;
		//Procedure 1: Broadcast and reception of HELLO Beacons
		if(t % T_H == 0){
			//From the table movement we have to decide which neighbors has each node, by calculating
			//the eucleidian distance.
			for(j=0; j<numberOfNodes; j++){
				cout << j << " neighbors {\n" ;
				if(t==0){
					vel_x_j = 0;
					vel_y_j = 0;
				}
				else{
					vel_x_j = movement[t][j].getGpsX() - movement[t-1][j].getGpsX();
					vel_y_j = movement[t][j].getGpsY() - movement[t-1][j].getGpsY();
				}
				for(i=0; i<numberOfNodes; i++){
					if(j!=i){
						eucleidianDistance = sqrt( pow( movement[t][j].getGpsX() - movement[t][i].getGpsX(), 2) + pow(movement[t][j].getGpsY() - movement[t][i].getGpsY(), 2));

						if( eucleidianDistance < (transmission_radius/2)){
							//cout << i << " ";

							//j needs to broadcast a message to i with details <j, (x,y)j, (vx,vy)j, CHj>
							//to each node i.
							aHelloMessage.setAll(j, movement[t][j].getGpsX(), movement[t][j].getGpsY(), vel_x_j, vel_y_j, cs_j, i);
							cout << aHelloMessage;

							sentHello[i]++ ;

							//Upon reception of the message, i checks whether j is travelling in the same direction
							//In order to decide whether the 2 nodes travel towards the same direction, we compare
							//the signs of their velocities on x and on y (positive or negative).
							receivedHello[i]++ ;

							if(t==0){
								vel_x_i = 0;
								vel_y_i = 0;
							}
							else{
								vel_x_i = movement[t][i].getGpsX() - movement[t-1][i].getGpsX();
								vel_y_i = movement[t][i].getGpsY() - movement[t-1][i].getGpsY();
							}

							//calculate the number f vehicles moving towards the same direction for all nodes
							cs_j =0;
							c_i = 0;
							for (k=0; k<numberOfNodes; k++ ){
                                for(nListIt = neighborList_I[k].begin(); nListIt != neighborList_I[k].end(); nListIt++){
                                    if(checkSameDirection(nListIt->getVelocityX(), (nListIt+1)->getVelocityX(), nListIt->getVelocityY(), (nListIt+1)->getVelocityY())){
                                        c_i ++;
                                        cs_j ++;
                                        nListIt->setCnt(c_i);
                                        (nListIt+1)->setCnt(cs_j);
                                    }
                                }
							}

							//if(checkSameDirection(vel_x_i, vel_x_j, vel_y_i, vel_y_j) == 1){
                            //in this case node i, calculates its velocityfactor & leadershipfactor with j ( VF(i,j), LF(i,j) )

                            //find the max and min Velocity vx and vy

                            maxVelocity = -1.0;
                            minVelocity = 1000.0;
                               for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){

                                    if(maxVelocity < abs(nListIt->getVelocityX() + nListIt->getVelocityY())){
                                        maxVelocity = abs(nListIt->getVelocityX() + nListIt->getVelocityY());
                                    }

                                    if(minVelocity > abs(nListIt->getVelocityX() + nListIt->getVelocityY())){
                                        minVelocity = abs(nListIt->getVelocityX() + nListIt->getVelocityY());
                                    }

                                }

                                velocityfactor_i_j = calculateVelocityFactor_i_j( vel_x_j, vel_y_j, maxVelocity, minVelocity);

                                //find the max Cnt
                                maxCnt = -1;
                                for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){

                                    if(maxCnt < nListIt->getCnt()){
                                        maxCnt = nListIt->getCnt();
                                    }

                                }

                                leadershipfactor_i_j = calculateLeadershipFactor_i_j(c_i, maxCnt);
                                //update of leadership factor
                                leadershipfactor_i_j = (1-DAMPING_A) * (nListIt->getLF_i_j()) + (DAMPING_A) * leadershipfactor_i_j;

                                SQF_i = calculateSQF_i(sentHello[i], receivedHello[i]);

                                //Then node i adds/updates j's neighbor list entry
                                if(neighborList_I[i].size() == 0 ){		//No elements in the neighborList_I
									neighborList_I[i].push_back(NeighborListEntry(j, movement[t][j].getGpsX(), movement[t][j].getGpsY(), vel_x_j, vel_y_j, cs_j, velocityfactor_i_j, leadershipfactor_i_j, 0.0, "", 0, clusterheads[j], EXPIRE_TIME_DEFAULT));
								}
                                else{									//There are elements in the neighborList_I
									for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){
										if(nListIt->getNodeID() == j){		//If node j has a record in the neighborList_I
											nListIt->setGps(movement[t][j].getGpsX(), movement[t][j].getGpsY());
											nListIt->setVelocity(vel_x_j, vel_y_j);
											nListIt->setCnt(cs_j);
											nListIt->setVF_i_j(velocityfactor_i_j);
											nListIt->setLF_i_j(leadershipfactor_i_j);
											nListIt->setExpirationTime(EXPIRE_TIME_DEFAULT);
											nListIt->setClusterhead(clusterheads[j]);
											break;
										}
									}
                                        if(nListIt == neighborList_I[i].end()){	//If node j has no record in the neighborList_I
                                            neighborList_I[i].push_back(NeighborListEntry(j, movement[t][j].getGpsX(), movement[t][j].getGpsY(), vel_x_j, vel_y_j,cs_j, velocityfactor_i_j, leadershipfactor_i_j, 0.0,"", 0, clusterheads[j], EXPIRE_TIME_DEFAULT));
                                        }
                                    }

                                }
                            //}
                        }
                    }
                    cout << "}" << endl;

                }
            }


            //update of the factors
            if(t % T_UP == 0){
                //each node update its factors
                for(i = 0; i < numberOfNodes; i++){
                    //scans the list of its neighbors
                    for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){

                        velocityfactor_i_j = (1-DAMPING_A) * (nListIt->getVF_i_j()) + (DAMPING_A) * velocityfactor_i_j;
                        SQF_i = (1-DAMPING_A) * (nListIt->getSQF_j()) + (DAMPING_A) * SQF_i;
                    }

                }

            }
		//At the end of every period, print the neighbor list
		for(i = 0; i < numberOfNodes; i++){
			///cout << "NEIGHBOR LIST OF NODE " << i << endl;
			///cout << "Clusterhead " << clusterheads[i] << endl;
			//scans the list of the neighbor nodes
			for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){
				///cout << *nListIt;
			}
		}
		
		/***Code for comparisons***/
		for(i = 0; i < numberOfNodes; i++){
			for(listOfVariaClusters_It = listOfVariaClusters.begin(); listOfVariaClusters_It != listOfVariaClusters.end(); listOfVariaClusters_It++){
				if(clusterheads[i] == *listOfVariaClusters_It){
					break;
				}
			}
			if(listOfVariaClusters_It == listOfVariaClusters.end()){
				listOfVariaClusters.push_back(clusterheads[i]);
			}
			
		}
		
		if(t>0){
			for(listOfVariaClusters_It = listOfVariaClusters.begin(); listOfVariaClusters_It != listOfVariaClusters.end(); listOfVariaClusters_It++){
				numberOfNodesInCluster.push_back( neighborList_I[*listOfVariaClusters_It].size() );
			}
			
			for(numberOfNodesInCluster_It = numberOfNodesInCluster.begin(); numberOfNodesInCluster_It != numberOfNodesInCluster.end(); numberOfNodesInCluster_It++){
				totalSizeOfCluster = totalSizeOfCluster + *numberOfNodesInCluster_It; 
			}
			
			averageSizeOfCluster = totalSizeOfCluster / listOfVariaClusters.size();
			sizeOfCluster[t] = averageSizeOfCluster;
		}
		
// 		for(listOfVariaClusters_It = listOfVariaClusters.begin(); listOfVariaClusters_It != listOfVariaClusters.end(); listOfVariaClusters_It++){
// 			cout << *listOfVariaClusters_It << " ";
// 		}
// 		cout << endl;
		
// 		for(numberOfNodesInCluster_It = numberOfNodesInCluster.begin(); numberOfNodesInCluster_It != numberOfNodesInCluster.end(); numberOfNodesInCluster_It++){
// 			cout << *numberOfNodesInCluster_It << " ";
// 		}
// 		cout << endl;
		
		totalSizeOfCluster = 0;
		numberOfClusters[t] = listOfVariaClusters.size();
		listOfVariaClusters.clear();
		numberOfNodesInCluster.clear();
	}
	
	
	/*************************COMPARISONS**********************************/
	
	/*Estimated Average number of messages*/
	for(t=0; t<periodTimes; t++){
		//cout << numberOfMessages[t] << " ";
		totalNumberOfMessages = totalNumberOfMessages + numberOfMessages[t];
		totalNumberOfClusters = totalNumberOfClusters + numberOfClusters[t];
	}
	
	for(t=1; t<periodTimes; t++){
		//cout << sizeOfCluster[t] << " ";
		totalSizeOfCluster = totalSizeOfCluster + sizeOfCluster[t];
	}
	cout << endl;
	
	averageNumberOfMessages = (float) totalNumberOfMessages / periodTimes;
	averageNumberOfClusters = (float) totalNumberOfClusters / periodTimes;
	averageSizeOfCluster = (float) totalSizeOfCluster / (periodTimes-1);
	cout << "Average number of messages per min: " << averageNumberOfMessages << endl;
	cout << "Average number of clusters per min: " << averageNumberOfClusters << endl;
	cout << "Average number of cluster size per min: " << averageSizeOfCluster << endl;
	if(periodTimes % T_H == 0){
		cout << "Average number of messages per " << T_H << " min: " << totalNumberOfMessages / (periodTimes / T_H) << endl;
		cout << "Average number of clusters per " << T_H << " min: " << totalNumberOfClusters / (periodTimes / T_H) << endl;
	}
	else{
		i = periodTimes % T_H;
		for(j = 0; j<periodTimes % T_H; j++){
			totalNumberOfMessages = totalNumberOfMessages - numberOfMessages[periodTimes -j -1];
			totalNumberOfClusters = totalNumberOfClusters - numberOfClusters[periodTimes -j -1];
		}
		cout << "Average number of messages per " << T_H << " min: " << totalNumberOfMessages / (periodTimes / T_H) << endl;
		cout << "Average number of clusters per " << T_H << " min: " << totalNumberOfClusters / (periodTimes / T_H) << endl;
	}
	
}



/*****************************************************************************************************************************************/
/*****************************************************OTHER FUNCTIONS*********************************************************************/
/*****************************************************************************************************************************************/

            //SECOND STEP - FUZZIFICATION AND FUZZY RULES
            //calculation of the rank
            for(i = 0; i < numberOfNodes; i++){
                //scans the list of its neighbors
                for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){

                    Rank = calculateRank();

                }

            }



            //At the end of each period, every node diminishes the t_expire time.
            for(i = 0; i < numberOfNodes; i++){
                //scans the list of the neighbor nodes
                for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){
                    nListIt->setExpirationTime( nListIt->getExpirationTime() -1 );
                }
            }
            //At the end of every period, print the neighbor list
            for(i = 0; i < numberOfNodes; i++){
                cout << "NEIGHBOR LIST OF NODE " << i << endl;
                cout << "Clusterhead " << clusterheads[i] << endl;
                //scans the list of the neighbor nodes
                for(nListIt = neighborList_I[i].begin(); nListIt != neighborList_I[i].end(); nListIt++){
                    cout << *nListIt;
                }
            }

        }

}

//Checks the signs of the velocities that are received as parameters.
//If the vehicles travel towards the same direction: return 1
//Else return 0
int checkSameDirection(float vel_x_i, float vel_x_j, float vel_y_i, float vel_y_j){

	//x>=0, y>=0
	if(vel_x_i >=0 && vel_x_j>=0 && vel_y_i>=0 && vel_y_j>=0){
		return 1;
	}
	//x<0, y>=0
	else if(vel_x_i<0 && vel_x_j<0 && vel_y_i>=0 && vel_y_j>=0){
		return 1;
	}
	//x<0, y<0
	else if(vel_x_i<0 && vel_x_j<0 && vel_y_i<0 && vel_y_j<0){
		return 1;
	}
	//x>=0, y<0
	else if(vel_x_i>=0 && vel_x_j>=0 && vel_y_i<0 && vel_y_j<0){
		return 1;
	}
	//any othercase
	else{
		return 0;
	}
}


//Velocity Factor between two nodes i and j
//VF_i_j = (|Vj| + |minV|)/ |maxV|
//Vj = Vxj + Vyj, j is the transmiter
float calculateVelocityFactor_i_j(float vel_x_j, float vel_y_j, float maxV,float minV){

    float VFij;

    VFij = (abs(vel_x_j + vel_y_j) - minV) / maxV;

    return VFij;
}

//Leadership Factor between two nodes i and j
// LF_i_j = c_i / maxCnt, i is the receiver

float calculateLeadershipFactor_i_j(int c_i, int maxC){

    float LFij;

    LFij = c_i / maxC;

    return LFij;
}

//calculate Signal Quality Factor of i
//i is the receiver

float calculateSQF_i(int num_hello_received, int num_hello_sent){

    float SQFi;

    SQFi = num_hello_received / num_hello_sent ;

    return SQFi;
}


void fuzzyVF(float VF)
{
	CFuzzyFunction *FuzzySet[3];

	FuzzySet[0] = new CTriangle;
	FuzzySet[1] = new CTriangle;
	FuzzySet[2] = new CTriangle;

	FuzzySet[0]->setInterval(-0.5,0.5);
	FuzzySet[0]->setMiddle(0,0);
	FuzzySet[0]->setType('t');
	FuzzySet[0]->setName("SLOW");

	FuzzySet[1]->setInterval(0,1);
	FuzzySet[1]->setMiddle(0.5,0.5);
	FuzzySet[1]->setType('t');
	FuzzySet[1]->setName("MEDIUM");

	FuzzySet[2]->setInterval(0.5,1.5);
	FuzzySet[2]->setMiddle(1.0,1.0);
	FuzzySet[2]->setType('t');
	FuzzySet[2]->setName("FAST");

	float dValue;

	dValue = VF;

    //CHECK IF THESE OPERATIONS ARE NECESSARY
	if(dValue<cdMinimumPrice && dValue>cdMaximumPrice){
		for(int i=0; i<3; i++){
            cout<<"\nThe dot="<<dValue<<endl;
            if(FuzzySet[i]->isDotInInterval(dValue))
                cout<<"In the interval";
            else
                cout<<"Not in the interval";
            cout<<endl;

            cout<<"The name of function is"<<endl;
            FuzzySet[i]->getName();
            cout<<"and the membership is=";

            cout<<FuzzySet[i]->getValue(dValue);

		}
	}
}



void fuzzyLF(float LF)
{
	CFuzzyFunction *FuzzySet[3];

	FuzzySet[0] = new CTriangle;
	FuzzySet[1] = new CTriangle;
	FuzzySet[2] = new CTriangle;

	FuzzySet[0]->setInterval(-0.5,0.5);
	FuzzySet[0]->setMiddle(0,0);
	FuzzySet[0]->setType('t');
	FuzzySet[0]->setName("POOR");

	FuzzySet[1]->setInterval(0,1);
	FuzzySet[1]->setMiddle(0.5,0.5);
	FuzzySet[1]->setType('t');
	FuzzySet[1]->setName("FAIR");

	FuzzySet[2]->setInterval(0.5,1.5);
	FuzzySet[2]->setMiddle(1.0,1.0);
	FuzzySet[2]->setType('t');
	FuzzySet[2]->setName("GOOD");

	float dValue;

	dValue = LF;

    //CHECK IF THESE OPERATIONS ARE NECESSARY
	if(dValue<cdMinimumPrice && dValue>cdMaximumPrice){
		for(int i=0; i<3; i++){
            cout<<"\nThe dot="<<dValue<<endl;
            if(FuzzySet[i]->isDotInInterval(dValue))
                cout<<"In the interval";
            else
                cout<<"Not in the interval";
            cout<<endl;

            cout<<"The name of function is"<<endl;
            FuzzySet[i]->getName();
            cout<<"and the membership is=";

            cout<<FuzzySet[i]->getValue(dValue);

		}
	}
}

void fuzzySQF(float SQF)
{
	CFuzzyFunction *FuzzySet[3];

	FuzzySet[0] = new CTrapezoid;
	FuzzySet[1] = new CTriangle;
	FuzzySet[2] = new CTriangle;

	FuzzySet[0]->setInterval(-0,0.8);
	FuzzySet[0]->setMiddle(0,0.5);
	FuzzySet[0]->setType('r');
	FuzzySet[0]->setName("BAD");

	FuzzySet[1]->setInterval(0.5,1);
	FuzzySet[1]->setMiddle(0.75,0.75);
	FuzzySet[1]->setType('t');
	FuzzySet[1]->setName("MEDIUM");

	FuzzySet[2]->setInterval(0.75,1.25);
	FuzzySet[2]->setMiddle(1.0,1.0);
	FuzzySet[2]->setType('t');
	FuzzySet[2]->setName("GOOD");

	float dValue;

	dValue = SQF;

    //CHECK IF THESE OPERATIONS ARE NECESSARY
	if(dValue<cdMinimumPrice && dValue>cdMaximumPrice){
		for(int i=0; i<3; i++){
            cout<<"\nThe dot="<<dValue<<endl;
            if(FuzzySet[i]->isDotInInterval(dValue))
                cout<<"In the interval";
            else
                cout<<"Not in the interval";
            cout<<endl;

            cout<<"The name of function is"<<endl;
            FuzzySet[i]->getName();
            cout<<"and the membership is=";

            cout<<FuzzySet[i]->getValue(dValue);

		}
	}
}


//TODO: FIRST CHECK THE IMPLEMENTETION OF THE SCHEME WITH THE RULES(matlab file) , IF NOT WORKS CHECK IF TO TAKE THE DECISION ABOUT THE STR VALUE OF FACTOR WITH MIN MEMBERSHIP ,E.G IF MEMBRESHIP GOOD > MEMBERSHIP MEDIUM THEN THE VALUE IS GOOD

//Calculate the Rank based  oon IF/THEN rules
//Number of rules = 27
string calculateRank(string VF, string LF, string SQF){

    string Rank;

    if(VF=="SLOW" && LF=="GOOD" && SQF=="GOOD"){
        Rank = "PERFECT";
    }
    if(VF=="SLOW" && LF=="GOOD" && SQF=="MEDIUM"){
        Rank = "GOOD";
    }
    if(VF=="SLOW" && LF=="GOOD" && SQF=="BAD"){
        Rank = "UNPREFERABLE";
    }
    if(VF=="SLOW" && LF=="FAIR" && SQF=="GOOD"){
        Rank = "GOOD";
    }
    if(VF=="SLOW" && LF=="FAIR" && SQF=="MEDIUM"){
        Rank = "ACCEPTABLE";
    }
    if(VF=="SLOW" && LF=="FAIR" && SQF=="BAD"){
        Rank = "BAD";
    }
    if(VF=="SLOW" && LF=="POOR" && SQF=="GOOD"){
        Rank = "UNPREFERABLE";
    }
    if(VF=="SLOW" && LF=="POOR" && SQF=="MEDIUM"){
        Rank = "BAD";
    }
    if(VF=="SLOW" && LF=="POOR" && SQF=="BAD"){
        Rank = "VERYBAD";
    }
    if(VF=="MEDIUM" && LF=="GOOD" && SQF=="GOOD"){
        Rank = "GOOD";
    }
    if(VF=="MEDIUM" && LF=="GOOD" && SQF=="MEDIUM"){
        Rank = "ACCEPTABLE";
    }
    if(VF=="MEDIUM" && LF=="GOOD" && SQF=="BAD"){
        Rank = "BAD";
    }
    if(VF=="MEDIUM" && LF=="FAIR" && SQF=="GOOD"){
        Rank = "ACCEPTABLE";
    }
    if(VF=="MEDIUM" && LF=="FAIR" && SQF=="MEDIUM"){
        Rank = "UNPREFERABLE";
    }
    if(VF=="MEDIUM" && LF=="FAIR" && SQF=="BAD"){
        Rank = "BAD";
    }
    if(VF=="MEDIUM" && LF=="POOR" && SQF=="GOOD"){
        Rank = "BAD";
    }
    if(VF=="MEDIUM" && LF=="POOR" && SQF=="MEDIUM"){
        Rank = "BAD";
    }
    if(VF=="MEDIUM" && LF=="POOR" && SQF=="BAD"){
        Rank = "VERYBAD";
    }
    if(VF=="FAST" && LF=="GOOD" && SQF=="GOOD"){
        Rank = "UNPREFERABLE";
    }
    if(VF=="FAST" && LF=="GOOD" && SQF=="MEDIUM"){
        Rank = "BAD";
    }
    if(VF=="FAST" && LF=="GOOD" && SQF=="BAD"){
        Rank = "VERYBAD";
    }
    if(VF=="FAST" && LF=="FAIR" && SQF=="GOOD"){
        Rank = "BAD";
    }
    if(VF=="FAST" && LF=="FAIR" && SQF=="MEDIUM"){
        Rank = "BAD";
    }
    if(VF=="FAST" && LF=="FAIR" && SQF=="BAD"){
        Rank = "VERYBAD";
    }
    if(VF=="FAST" && LF=="POOR" && SQF=="GOOD"){
        Rank = "BAD";
    }
    if(VF=="FAST" && LF=="POOR" && SQF=="MEDIUM"){
        Rank = "VERYBAD";
    }
    if(VF=="FAST" && LF=="POOR" && SQF=="BAD"){
        Rank = "VERYBAD";
    }

    return Rank;
}

