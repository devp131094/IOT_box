/*
 * SPI.c
 *
 *  Created on: Aug 27, 2018
 *      Author: dev
 */

#include "SPI.h"



void time_inp(char *output)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    sprintf(output, "[%d/%d/%d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}


int ADC_in(char* result)
{
	int x[8],i;
	//float v[8];
	//float k = 3.3/1024;
	char time[50];

	time_inp(time);
	strcat(result,time);
	strcat(result," ");

	for (i=0;i<2;i++)
	{
		x[i] = analogRead (MY_PIN + i ) ;
		
		ADC_package(x[i],i,result);	
		
		//v[i] = k * (float)(x[i]);
	}

	printf("AD ch: = %4d %4d %4d %4d %4d %4d %4d %4d \n",
			x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7]);
	//printf("AD vd: = %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f\n",
			//v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);

	//ADC_package(x[0],0,result);
	
	
	delay(500);
	return 0;
}


void ADC_package(int inp_data, int chan, char* packaged_data)
{
	char inp[10];
	char sensor[10];
	char end[2];
	sprintf(inp,"%d",inp_data);
	strcpy(end,"; ");


	switch(chan)
	{
	case 0 :
		strcpy(sensor,"Trim Pot: ");
		break;
	case 1 :
		strcpy(sensor,"Light: ");
		break;
	}

	strcat(packaged_data,sensor);
	strcat(packaged_data,inp);
	strcat(packaged_data,end);
}

