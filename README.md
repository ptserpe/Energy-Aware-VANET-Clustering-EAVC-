# Energy-Aware-VANET-Clustering-EAVC-

Implementation of Energy- Aware VANET Clustering(EAVC), a two-level clustering approach for electric and non-electric vehicles, integrating LTE with 802.11p. More specifically, a fuzzy logic-based algorithm is used in the first-level clustering for the cluster head(CH) selection, and a Q-learning algorithm is employed in the second-level clustering to tune the number of gateway nodes, as well as for formation and maintenance of clusters. We conducted several simulations to evaluate
the performance of the proposed algorithm, by applying various scenarios for different network conditions respectively.

To obtain the results of our algorithm we had to create a realistic environment where the vehicles could move with some velocity towards a random direction but into predefine roads. The simulation of the road networks was made with tool SUMO and ns-3 was used for the wireless network's creation and communication establishment. 

Files description:

--main.cpp: which contains the call of the main function. During the execution of the program, it is
designed to accept at least 3 arguments with a certain order: (1) number of nodes that participate in
the simulation, (2) the period of times that the simulation lasts and (3) the name of the file that con-
tains the simulation details and has been produced with the TraceExporter (the SUMO’s extension
that was described previously). If the user doesn’t provide the adequate number of arguments, the
program is terminated by providing to the user the message “Please enter the number of nodes and
the period of times that the program runs as the second and the third parameter. Also give the file-
name that declares the movement.”. In the end of the file, there is a call to the main function. Finally, this file sets the transmission radio of the
nodes that participate in the simulation.

--Movement.h & Movement.cpp: These 2 files implement the class “Movement”, which contains details read from the input simulation file that is declared by the user. Each node keeps its nodeID, its position (int x, int y) and its velocity (which is the total velocity on x and y axes and is not really necessary
for the implemented algorithms).

--HelloBeaconMessage.h & HelloBeaconMessage.cpp: These files simulate the information that is transmitted from a node to another, when a Hello_Beacon message is transmitted form one node to its neighbors in order to inform them for his existence.

--NeighborListEntry.h & NeighborListEntry.cpp: These files contain the list of neighbors that a node retains.

--simple.ns: Highway simulation network

--city.ns: Urban environment Simulation network.

