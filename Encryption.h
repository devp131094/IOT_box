/*
 * Encryption.h
 *
 *  Created on: Aug 21, 2018
 *      Author: dev
 */

#ifndef ENCRYPTION_H_
#define ENCRYPTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

void encrypt_MD5(char* string,unsigned char* result);

int encrypt_package(char* string, unsigned char * packet);

int encrypt(char* string,unsigned char* result);

#endif /* ENCRYPTION_H_ */
