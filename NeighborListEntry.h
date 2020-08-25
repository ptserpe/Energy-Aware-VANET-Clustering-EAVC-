#ifndef NEIGHBORLISTENTRY_H
#define NEIGHBORLISTENTRY_H
#include <iostream>
using namespace std;

class NeighborListEntry{

	public:
		typedef struct {
			float x;
			float y;
		} gps;

		typedef struct {
			float v_x;
			float v_y;
		} velocity;

	private:
		int nodeID_j;
		gps nodePosition_j;
		velocity nodeVelocity_j;
		float velocityfactor_i_j;
		float leadershipfactor_i_j;
		float SQF_j;
		string competency_value_j;
		int CH_cnvg_j;				//1: converged_clusterhead, 0: no_convergence
		int CH_j;
		int t_expire;
	public:
		NeighborListEntry();
		NeighborListEntry(int id, float x, float y, float vel_x, float vel_y, float vf_i_j, float lf_i_j, float sqf_j, string c_v_j,int CH_converge, int CH, int expirationTime);
		~NeighborListEntry();
		int getNodeID();
		float getGpsX();
		float getGpsY();
		float getVelocityX();
		float getVelocityY();
		float getVF_i_j();
		float getLF_i_j();
		float getSQF_j();
		string getCV_j();
		int getClusterheadConverge();
		int getClusterhead();
		int getExpirationTime();
		void setNodeID(int id);
		void setGps(float x, float y);
		void setVelocity(float vel_x, float vel_y);
		void setVF_i_j(float vf_i_j);
		void setLF_i_j(float lf_i_j);
		void setSQF_j(float sqf_j);
		void setCV_j(string c_v_j);
		void setClusterheadConverge(int CH_converge);
		void setClusterhead(int CH);
		void setExpirationTime(int expirationTime);
		void setAll(int id, float x, float y, float vel_x, float vel_y, float vf_i_j, float lf_i_j, float sqf_j, string c_v_j, int CH_converge, int CH, int expirationTime);
		friend ostream& operator << (ostream& outs, const NeighborListEntry& aNeighborListEntry);
};


#endif // NEIGHBORLISTENTRY_H
