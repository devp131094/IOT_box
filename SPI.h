/*
 * SPI.h
 *
 *  Created on: Aug 27, 2018
 *      Author: dev
 */



#ifndef SPI_H_
#define SPI_H_

//#include <wiringPi.h>
//#include <mcp3004.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SPI_CHAN 0
#define MY_PIN 12345

int ADC_in(char* result);

void ADC_package(int inp_data, int chan, char* packaged_data);


#endif /* SPI_H_ */
