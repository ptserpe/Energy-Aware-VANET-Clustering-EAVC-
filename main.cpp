#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cmath>
#include "Movement.h"

using namespace std;


int main(int argc, char *argv[]){
	int numberOfNodes;
	int periodTimes;
	Movement **nodeMovements;

	char filename[50], line[128];
	ifstream inStream;
	//parameters read from the file
	float time, positionX, positionY, velocity;
	int nodeID;

	int i, j, k;

	float minEucleidianDistance, maxEucleidianDistance, eucleidianDistance;
	float transmission_radius;

	//>>>>>>>>>STAGE 1:
	//initial code to read the parameters about the number of nodes and the time of the whole simulation
	if(argc<4){
		cout << "Please enter the number of nodes and the period of times that the program runs as the second and the third parameter.\n Also give the filename that declares the movement.";
		exit(1);
	}
	numberOfNodes = atoi(argv[1]);
	periodTimes = atoi(argv[2]);
	strcpy(filename, argv[3]);

	cout << "=================================================\n";
	cout << "Number of nodes: " << numberOfNodes << "\n" ;
	cout << "Time periods: " << periodTimes << "\n" ;
	cout << "Filename: \"" << filename << "\"\n" ;
	cout << "=================================================\n";

	//>>>>>>>>>STAGE 2:
	//From the file given as the third parameter on the code, we can initialize a table with the movement of the nodes.

	nodeMovements = new Movement*[periodTimes];
	for(i=0; i<periodTimes; i++){
		nodeMovements[i] = new Movement[numberOfNodes];
	}

	inStream.open(filename);
	if(inStream.fail()){		//check whether the file exists...
		cout << "The file couldn't be opened or couldn't be found!\n";
		exit(1);
	}

	for(i=0; i<periodTimes; i++){
		for(j=0; j<numberOfNodes; j++){
			nodeMovements[i][j].setNodeID(-1);
		}
	}

	while(1){
		inStream.getline(line, 127);
		if(strncmp(line, "  $node_", 8)==0){
			break;
		}
		//cout<<line<<"\n";

		/*It's line we read from the file follows the next pattern
		* $ns_ at 0.0 "$node_(15) setdest 5.79 -4.95 0.78"
		* More specifically,
		* $ns_ at *periodtime* "$node_(*nodeID*) setdest *positionX* *positionY* *velocity*"
		* So, we have to use sscanf in order to separate the values that interest us!
		*/
		sscanf(line, "$ns_ at %f \"$node_(%d) setdest %f %f %f\"", &time, &nodeID, &positionX, &positionY, &velocity);
		//cout << ceil(time) << "  " << nodeID << " (" << positionX << "," << positionY << ") " << velocity << "\n";
		nodeMovements[(int) ceil(time)][nodeID].setAll(nodeID, positionX, positionY, velocity);
	}

// 	for(i=0; i<periodTimes; i++){
// 		for(j=0; j<numberOfNodes; j++){
// 			cout << i << "  " << nodeMovements[i][j];
// 		}
// 	}

// 	for(i=0; i<periodTimes; i++){
// 		cout << i << endl ;
// 		for(j=0; j<numberOfNodes; j++){
// 			cout << nodeMovements[i][j].getNodeID() << "  " ;
// 		}
// 		cout << endl ;
// 	}

	//Now that we have read the whole file, we can close it!
	inStream.close();		//Close the file that was opened

	//>>>>>>>>>STAGE 3:
	//If we start losing data from one of the nodes, we fill the table nodeMovements with the data we had from
	//previous positions, as it follows.
	for(i=1; i<periodTimes; i++){
		for(j=1; j<numberOfNodes; j++){
			if(nodeMovements[i][j].getNodeID() == -1){
				nodeMovements[i][j].setNodeID(j);
				nodeMovements[i][j].setGps(nodeMovements[i-1][j].getGpsX(), nodeMovements[i-1][j].getGpsY());
				nodeMovements[i][j].setVelocity(nodeMovements[i-1][j].getVelocity());
			}
		}
	}

	for(i=0; i<periodTimes; i++){
		for(j=0; j<numberOfNodes; j++){
			cout << i << "  " << nodeMovements[i][j];
		}
	}

// 	for(i=0; i<periodTimes; i++){
// 		cout << i << endl ;
// 		for(j=0; j<numberOfNodes; j++){
// 			cout << nodeMovements[i][j].getNodeID() << "  " ;
// 		}
// 		cout << endl ;
// 	}


	//>>>>>>>>>STAGE 5:
	//Calculate the min and the max eucleidian distance that 2 different nodes will ever have with its other.
	//This step is optional. It could be used in order to assign a minimum radius in which a node needs to
	//transmit a message in order to be heard by its neighbors, so that the graph is always connected...

	//initialization with the first set of values
	minEucleidianDistance = sqrt( pow( nodeMovements[0][0].getGpsX() - nodeMovements[0][1].getGpsX(), 2) + pow(nodeMovements[0][0].getGpsY() - nodeMovements[0][1].getGpsY(), 2));
	maxEucleidianDistance = minEucleidianDistance;

	for(i=0; i<periodTimes; i++){
		for(j=0; j<numberOfNodes; j++){
			for(k=0; k<numberOfNodes; k++){
				if(j!=k){
					eucleidianDistance = sqrt( pow( nodeMovements[i][j].getGpsX() - nodeMovements[i][k].getGpsX(), 2) + pow(nodeMovements[i][j].getGpsY() - nodeMovements[i][k].getGpsY(), 2));

					if( eucleidianDistance < minEucleidianDistance){
						minEucleidianDistance = eucleidianDistance;
					}

					if(eucleidianDistance > maxEucleidianDistance){
						maxEucleidianDistance = eucleidianDistance;
					}
				}

			}
		}
	}

	transmission_radius = minEucleidianDistance + (maxEucleidianDistance - minEucleidianDistance)*0.2;

	cout << endl;
	cout << "=================================================\n";
	cout << "minEucleidianDistance: " << minEucleidianDistance << "\n";
	cout << "maxEucleidianDistance: " << maxEucleidianDistance << "\n";
	cout << "transmission_radius: " << transmission_radius << "\n";
	cout << "=================================================\n";


	Fuzzy_logic_aalgorithm(periodTimes, numberOfNodes, nodeMovements, transmission_radius);


	return 0;
}
