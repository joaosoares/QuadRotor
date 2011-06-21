/*
 * Jun 20th, 2011
 *
 * Quadrotor Main Board
 * PID Control Functions
 *
 * Code (barely) adapted from Tim Wescott, "PID without a PhD".
 * Available at <http://www.eetimes.com/ContentEETimes/Documents/Embedded.com/2000/f-wescot.pdf>
 *
 */
 
#include "pid.h"

/* Structure of the variable type SPid */
struct PID {
	double dState;			// Last position output
	double iState;			// Integrator state
	double iMax, iMin;		// Maximum and minimum allowable integrator state
	
	double iGain;			// integral gain
	double pGain;			// proportional gain
	double dGain;			// derivative gain
} ;

double UpdatePID(SPid * pid, double error, double position)
{
	double pTerm, iTerm, dTerm;
	
	pTerm = pid->pGain * error; // calculate the proportional term
	
	// calculate the integral state with appropriate limiting
	pid->iState += error;
	if (pid->iState > pid->iMax) pid->iState = pid->iMax;
	else if (pid->iState < pid->iMin) pid->iState = pid->iMin;
	
	iTerm = pid->iGain * pid->iState; // calculate the integral term
	
	dTerm = pid->dGain * (pid->dState - position);
	pid->dState = position;
	
	return pTerm + dTerm + iTerm;
}	
