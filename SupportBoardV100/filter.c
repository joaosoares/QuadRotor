/*	This module contains functions related to converting the sensors measurement	**
**	into usable data and merging complementary sensors in order to obtain a good	**
**	prediciton of the corrent tilt and angular rate of the robot					**
**	By Paulo Carvalho	V2.00														*/

/* Include Standard Header */
#include <avr/io.h>

/* Include Math Library */
#include <math.h>

/* Make Necessary Definitions */
#define GYROLSB 14.375
#define ACCELLSB 256
#define TIME 0.016

/* Define Level of Trust */
/* Trusts Have to Add to 100 */
#define GYROTRUST 0.95
#define ACCELTRUST 0.05

/* Create Variables */
double tempGyro[3];
double tempAccel[3];
int i;

/* 1 if Negative, 0 Else. 0-3 For Gyro; 4-6 for Accel */
char sign[6] = {0};

/* Filter Function */
void filter(int *ptrAngle,int *ptrRate,int *ptrGyro_Adc,int *ptrAccel_Adc)
{
	/* Create Temporary Variable */
	double tempAngle[3] = {0};

	/* Convert Gyroscope Data */

	/* Check if Data is Positive or Negative */
	for(i = 0; i < 3; i++)
	{
		if(0x8000 & ptrGyro_Adc[i])
			{
				tempGyro[i] = (double)(~ptrGyro_Adc[i]);
				sign[i] = 1;
			}
		else
			{
				tempGyro[i] = (double)(ptrGyro_Adc[i]);
				sign[i] = 0;
			} 
	}
	
	/* Convert ADC Measure into Rate */
	tempGyro[0] /= GYROLSB;	
	tempGyro[1] /= GYROLSB;
	tempGyro[2] /= GYROLSB;
	
	/* To avoid integration Error Zero Very small Measures */
	for(i = 0; i < 3; i++)
	{
		if(tempGyro[i] < 0.2)
		{
			tempGyro[i] = 0;
		}
	}

	/* Reset Timer */
	TCNT2 |= 0x00;	

	/* Integrate to Get Angle */
	tempGyro[0] *= TIME;
	tempGyro[1] *= TIME;
	tempGyro[2] *= TIME;
	
	/* Replace Negative */
	if(sign[0]) 
		tempGyro[0] *= -1.00;
	if(sign[1]) 
		tempGyro[1] *= -1.00;
	if(sign[2]) 
		tempGyro[2] *= -1.00;

	/*********/
	/* Convert Accelerometer Data */
	/* Check if Data is Positive or Negative */
	for(i = 0; i < 3; i++)
	{
		if(0x0200 & ptrAccel_Adc[i])
			{
				tempAccel[i] = (double)(~ptrAccel_Adc[i]);
				sign[i + 3] = 1;
			}
		else
			{
				tempAccel[i] = (double)(ptrAccel_Adc[i]);
				sign[i + 3] = 0;
			} 
	}
	
	/* Convert to Angle (ONLY WORKS FOR SMALL ANGLES)*/
	tempAccel[0] = (atan2(tempAccel[0], tempAccel[2])) * (180.00 / M_PI);
	if(sign[4]) 
		tempAccel[0] *= -1.00;
	tempAccel[1] = (atan2(tempAccel[1], tempAccel[2])) * (180.00 / M_PI);
	if(sign[5]) 
		tempAccel[1] *= -1.00;

	/**********/
	/* Mix Data Taking Trust into Account */
	tempAngle[0] += tempAccel[0] * ACCELTRUST + tempGyro[0] * GYROTRUST;
	tempAngle[1] += tempAccel[1] * ACCELTRUST + tempGyro[1] * GYROTRUST;
	tempAngle[2] += tempGyro[2] * GYROTRUST;

	/* Convert Data back to INT * 100 and return */
	ptrAngle[0] = (int)(tempAngle[0] * 100);
	ptrAngle[1] = (int)(tempAngle[1] * 100);
	ptrAngle[2] = (int)(tempAngle[2] * 100);
}
