/*
 * buff.h
 *
 *  Created on: Aug 1, 2018
 *      Author: dev
 */

#ifndef BUFF_H_
#define BUFF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>

#define MAXBUF 1024
//*****************************************************************
// * circular_buffer_t: Structure defined for initialization of following parameters.
// * Buffer : Defining a 2D circlar character buffer to store strings with a set length of buffer and width of each element.
// * Ovw: Overwrite parameter, used to determine if buffer will overwrite contents stored within it, 0 for OFF and 1 for ON.
// * Head: Head pointer used to indicate the current location of element next to be pushed out.
// * Tail: Tail pointer used to indicate the current location of element most recently stored.
// * Size: Determines the size of buffer being available to the user for storing, measured in bytes.
//*****************************************************************
typedef struct {
	unsigned char buffer[100][256];
	int ovw;
	size_t head;
	size_t tail;
	size_t size;			 //size of the buffer
} circular_buf_t;



struct config
{
   char buffer_size[MAXBUF];
   char overwrite[MAXBUF];
   char timer_duration[MAXBUF];
};
//*****************************************************************
// * Circular_buf_reset: Function responsible for reseting head and tail pointers back to base of buffer
//*****************************************************************
int circular_buf_reset(circular_buf_t * cbuf);

//*****************************************************************
// * circular_buf_put: Function responsible for storing incoming data into buffer and overwriting stored data in case of buffer overflow
//*****************************************************************
int circular_buf_put_ovw(circular_buf_t * cbuf,unsigned char data[]);
//*****************************************************************
// * circular_buf_put2: Function responsible for storing incoming data into buffer and flushes buffer when overflow occurs.
//*****************************************************************
int circular_buf_put(circular_buf_t * cbuf,unsigned char data[]);

//*****************************************************************
// * circular_buf_get: Function responsible for pushing data out of the buffer as indicated by the head pointer.
//*****************************************************************
int circular_buf_get(circular_buf_t * cbuf,unsigned char * data);

//*****************************************************************
// * circular_buf_empty:  Function indicates if the buffer is empty
//*****************************************************************
bool circular_buf_empty(circular_buf_t* cbuf);

//*****************************************************************
// * circular_buf_fully:  Function indicates if the buffer is full
//*****************************************************************
bool circular_buf_full(circular_buf_t* cbuf);

//*****************************************************************
// * buffer_init:  Function initializes buffer parameters such as overflow flag and buffer available size
//*****************************************************************
void buffer_init(circular_buf_t * cbuf,struct config * configstruct);

//*****************************************************************
// * timer_reset: Function resets the timer to currnet time based on UNIX time.
//*****************************************************************
int timer_reset(struct config * configstruct);

//void delay_int(int number_of_seconds);

#endif /* BUFF_H_ */
