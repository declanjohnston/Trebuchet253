#ifndef PID_h	
#define PID_h

// include types & constants of Wiring core API
//#include "WConstants.h"
#include "motor.h"

class PID
{
	public:
		//constructor
		PID(motorClass motorIn);

		void init(int derivative, float integral, int proportional, int gain, int setSpeed, int motorLeft, int motorRight);

		void run(int xpos);
		
		void tank(int xpos);
		
		void stop();

	private:
		motorClass motor;
		int state;
    	int D;
		float I;
		int G;
		int P;
    	byte count;
    	int Speed;
    	int lstate;
   		int recerr;
    	int q;
    	int m;
    	int p;
    	int d;
		int rightMotor;
		int leftMotor;
    	int cor;
		float i;
};
#endif