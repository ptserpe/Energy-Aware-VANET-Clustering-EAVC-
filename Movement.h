/*Class Movement
* Represents the position of a certain node and its velocity at a certain time.
* The node id is not actually needed...
*/

#ifndef MOVEMENT_H
#define MOVEMENT_H


#include <iostream>
using namespace std;


class Movement{
	public:
		struct gps{
			float x;
			float y;
		};
		typedef struct gps pos;

	private:
		int nodeID;		//This parameter could also be omitted and retrieved by the position of the table.
						//It is used only because we don't read the nodes in a certain row from the input file.
		pos position;
		float velocity;
		//int time;		//This parameter can also be avoided, because it can be retrieved by the row of
						//the two dimension table.
	public:
		Movement();
		Movement(int id, float x, float y, float velocity);
		~Movement();
		int getNodeID();
		float getGpsX();
		float getGpsY();
		float getVelocity();
		void setNodeID(int nodeID);
		void setGps(float x, float y);
		void setVelocity(float vel);
		void setAll(int id, float x, float y, float vel);
		friend ostream& operator << (ostream& outs, const Movement& aMovement);
};

#endif // MOVEMENT_H
