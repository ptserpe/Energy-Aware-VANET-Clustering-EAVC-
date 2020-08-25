#ifndef HELLOBEACONMESSAGE_H
#define HELLOBEACONMESSAGE_H

#include <iostream>
using namespace std;

class HelloBeaconMessage
{
   	public:

		struct gps{
			float x;
			float y;
		};
		typedef struct gps pos;

		struct velocity{
			float v_x;
			float v_y;
		};
		typedef struct velocity vel;

	private:
		int nodeID_j;			//j is the transmitter
		pos nodePosition_j;
		vel nodeVelocity_j;
		int cs_id;

		int nodeID_i;					//i is the receiver

	public:
		HelloBeaconMessage();
		HelloBeaconMessage(int id, float x, float y, float vel_x, float vel_y, int cs, int receiver);
		~HelloBeaconMessage();
		int getNodeID();
		float getGpsX();
		float getGpsY();
		float getVelocityX();
		float getVelocityY();
		int getNumberOfNodesMovingTowardsTheSameDirection();
		int getReceiver();
		void setNodeID(int nodeID);
		void setGps(float x, float y);
		void setVelocity(float vel_x, float vel_y);
		void setNumberOfNodesMovingTowardsTheSameDirection(int cs);
		void setReceiver(int id);
		void setAll(int id, float x, float y, float vel_x, float vel_y, int cs, int receiver);
		friend ostream& operator << (ostream& outs, const HelloBeaconMessage& aHelloBeaconMessage);
};

#endif // HELLOBEACONMESSAGE_H
