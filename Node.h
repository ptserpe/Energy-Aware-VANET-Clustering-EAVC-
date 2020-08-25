#ifndef NODE_H
#define NODE_H

#include <vector>
#include "NeighborListEntry.h"

#define EDGE_CH 0
#define GW 1
#define ON 2 //ordinary node

class Node{

    private:
        int nodeID;
        int status;
        int clusterhead;
        float VF;
        float LF;
        float SQF;
        float competencyValue;
        int cnt;
        vector<NeighborListEntry> neighborList_I;

     public:
        Node();
        Node(int id, int stat, int ch, float vf, float lf, float sqf,float cv, int c);
        virtual ~Node();

        int getNodeID();
		int getStatus();
		int getClusterhead();
        float getVF();
        float getLF();
        float getSQF();
        float getCV();
        int getCnt();

        void setNodeID(int id);
		void setStatus(int stat);
		void setClusterhead(int ch);
		void setCnt(int c);

		void setAll(int id, int stat, int ch, float vf, float lf, float sqf, float cv, int c);

		void emptyNeighborsVector();
		int sizeNeighborsVector();

		friend ostream& operator << (ostream& outs, const Node& aNode);
};

#endif // NODE_H
