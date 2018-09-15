#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include "Encryption.h"

//const char *string = "The quick brown fox jumped over the lazy dog's back";



void encrypt_MD5(char* string,unsigned char* result)
{
	//int i;
	strcpy((char *)result,"");
	MD5((char *)string, strlen(string), result);

	// output
	/*
	for(i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
	printf("%X", result[i]);
	}
	printf("\n\n");
	*/
}

int encrypt_package(char* string, unsigned char* packet)
{
	int i;
	int length = 0;
	int length_full = 0;
	char ident[1];
	unsigned char lengt[4];
	unsigned char te[4];

	unsigned char tempo[MD5_DIGEST_LENGTH * 2];
	strcpy((char *)tempo,"");
	unsigned char result [MD5_DIGEST_LENGTH];

	encrypt_MD5(string,result);

	for(i = 0; i < MD5_DIGEST_LENGTH; i++)
	{

		sprintf((char *)te,"%X",result[i]);

		strcat((char *)tempo,(char *)te);
		//printf("%d\n",strlen(tempo));
	}

	printf("\n");

	strcpy(ident,"/");
	strcpy((char *)packet,string);
	//printf("%s\n", packet);


	strcat((char *)packet,ident);
	//printf("%s\n", packet);
	strcat((char *)packet,(char *)tempo);

	length = strlen((char *)packet);

	sprintf((char *)lengt,"%d",length);
	strcpy(ident,"//");
	strcat((char *)packet,ident);


	strcat((char *)packet,(char *)lengt);
	strcpy(ident,"-");
	strcat((char *)packet,ident);
	//**********************************************
	printf("%s\n", packet);
	//**********************************************
	//printf("%d\n",strlen(packet));

	length_full = strlen((char *)packet);

	return length_full;

}

int encrypt(char* string,unsigned char* result)
{

	int length;
	//unsigned char result[100];
	//char *string = "The quick brown fox jumped over the lazy dog's back";
	length = encrypt_package(string, result);
	//printf("%s", result);

	return length;
}
