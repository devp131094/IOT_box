//******************************************************************************
// * Author: dev
// * File name: Buffer
// * Version : 1.6
// * Functionality :
// * This version includes an overwriting feature which can be controlled my a flag ovw.   Completely compatible with client side socket prog and has been tested with server.
// * If ovw = 0; This mean overwrite is disabled and the buffer will be flushed out when it has been detected to be full.
// * New: A config file functionality is added, the config file has variables that can be changed to directly control the parameters within the main program such as overwite enable/diable, buffer size, timer duration, etc.
// * If ovw = 1; This mean overwirte is enable, a programmable timer is implementated, untill the timer is on and the buffer is full then overwrite takes place in LRU manner. If timer hits 0 then buffer flushes and timer is reset.
//*******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include "buffer.h"
#include "Client.h"
#include "SPI.h"

int i;


int circular_buf_reset(circular_buf_t * cbuf)
{
    int r = -1;

    if(cbuf)
    {
        cbuf->head = 0;
        //printf("%d\n",cbuf->head);
        cbuf->tail = 0;
        //printf("%d\n",cbuf->tail);
        r = 0;
    }

    return r;
}

bool circular_buf_empty(circular_buf_t* cbuf)
{
    return (cbuf && (cbuf->head == cbuf->tail));						// We define empty as head == tail
}

bool circular_buf_full(circular_buf_t* cbuf)
{

    return (cbuf && ((cbuf->head + 1) % cbuf->size) == cbuf->tail);
}


int circular_buf_put_ovw(circular_buf_t * cbuf,unsigned char data[])
{
    int r = -1;

    if(cbuf)
    {
    	strcpy(cbuf->buffer[cbuf->head],data);
    	//**********************************************
    	//printf("OVW Buffer: %s\n",cbuf->buffer[cbuf->head]);
    	//**********************************************
        cbuf->head = (cbuf->head + 1) % cbuf->size;

        if(cbuf->head == cbuf->tail)
        {
            cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        }

        r = 0;
    }

    return r;
}

int circular_buf_put(circular_buf_t * cbuf,unsigned char data[])
{
    int r = -1;
    //printf("Head: %d\n",cbuf->head);
    if(cbuf && !circular_buf_full(cbuf))
    {
        strcpy(cbuf->buffer[cbuf->head],data);

        cbuf->head = (cbuf->head + 1) % cbuf->size;

        if(cbuf->head == cbuf->tail)
        {
            cbuf->tail = (cbuf->tail + 1) % cbuf->size;
        }

        r = 0;
    }

    return r;
}

int circular_buf_get(circular_buf_t * cbuf,unsigned char  data[])
{
    int r = -1;

    if(cbuf && data && !circular_buf_empty(cbuf))
    {
        strcpy(data ,cbuf->buffer[cbuf->tail]);
        cbuf->tail = (cbuf->tail + 1) % cbuf->size;

        r = 0;
    }

    return r;
}

void buffer_init(circular_buf_t * cbuf,struct config * configstruct)
{
	cbuf->size = atoi(configstruct->buffer_size);

	cbuf->ovw = atoi(configstruct->overwrite);			//overwrite flag, 0 if off and 1 if on
	if (cbuf->ovw == 0)
	{
		printf("Overwrite is OFF\n");
	}
	else
	{
		printf("Overwrite is ON\n");
	}

}
/*
void delay_int(int number_of_seconds)
{
	int duration = number_of_seconds;
	int timer = (int)time(NULL);
	int current_time = timer;

	timer =timer + duration;
	printf("timer = %d \n",timer);
	while(current_time <= timer)
	{
		current_time = (int)time(NULL);
	}
}
*/
//Timer intit
int timer_reset(struct config * configstruct)
{
	int duration;
	duration = atoi(configstruct->timer_duration);
	int timer = (int)time(NULL);
	//printf("timer = %d \n",timer);
	timer =timer + duration;
	//printf("timer = %d \n",timer);
	return timer;
}


int buffer(client_UDP * clnt ,circular_buf_t * cbuf ,struct config * configstruct ,char* inp ,int timer)
{

    //struct config configstruct;
    //configstruct = get_config(FILENAME);
	//circular_buf_t cbuf;

	//buffer_init(&cbuf,&configstruct);
	//uint8_t i;
	int j = (int)time(NULL);
	int length_ret;
	int length = (cbuf->size)*100;
	unsigned char data[256];
	unsigned char result[length];
	unsigned char package[length];
	strcpy(package,"");
	char end[2];
	strcpy(end,"// ");


	//**********************************************
	//printf("%s\n",inp);
	//printf("\ntimer = %d \n",timer);
	//printf("j: %d\n",j);
	//printf("%d\n",cbuf->ovw);
	//**********************************************

	//circular_buf_reset(&cbuf); //set head/tail to 0

	if (cbuf->ovw == 0)
	{
		if (!circular_buf_full(cbuf) && timer > j)
		{
			//char inc[10];
			//strcpy(inc,"Hello");
			//**********************************************
			//printf("Input: %s \n",inp);
			//**********************************************
			circular_buf_put(cbuf, inp);
		}
		else
		{
			while(!circular_buf_empty(cbuf))
			{

				circular_buf_get(cbuf, data);


				strcat(package,data);
				strcat(package,end);
				//printf("\n%s\n", data);

				printf("\n count: %d\n",i);
				i++;
			}
			length_ret = encrypt(package,result);
			printf("%d\n",length);
			//printf("\n%s\n", result);
			client(clnt, result,length_ret);
		//timer = timer_reset(&configstruct);
		}
	}
	else
	{

		if (timer > j)
		{
			//**********************************************
			//printf("Input: %s \n",inp);
			//**********************************************
			circular_buf_put_ovw(cbuf, inp);

		}
		else if(timer <= j)
		{
			while(!circular_buf_empty(cbuf))
			{
				circular_buf_get(cbuf, data);

				strcat(package,data);
				strcat(package,end);

				printf("\n count: %d\n",i);
				i++;
			}
			encrypt(package,result, length_ret);
			//printf("\n%s\n", result);
			client(clnt, result, length_ret);
		//timer = timer_reset(&configstruct);
		}

	}



	return 0;
}
