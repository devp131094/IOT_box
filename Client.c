/************************************************************************************************
Date: 8/14/18
Program: UDP Client

Description: Manual input of host name and port number for connection establishment between UDP client and server.

**************************************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include "Client.h"

FILE *logfile;



void error(char *);
int cnt = 0;

void UDP_client_init(client_UDP * clnt)
{

	clnt->arguc = 3;

	strcpy(clnt->hostname, "localhost");		//Setting the IP_address

	strcpy(clnt->port_char,"5657");			//Setting the port number

	clnt->address = atoi(clnt->port_char);		//Type casting port_no from ASCII ti int

}

void client(client_UDP * clnt, char data[],int length_ret)
{

	int sock, length, n;
	struct sockaddr_in server;
	struct hostent *hp;
	char buffer[length_ret];

	char hostnm[100];
	strncpy(buffer,data,length_ret);

	//**********************************************
	printf("buffer: %s\n",buffer);

	//**********************************************


	if (clnt->arguc != 3)
	{
		printf("Usage: server port\n");
		exit(1);
	}

	sock= socket(AF_INET, SOCK_DGRAM, 0);					//Defining Internet Family and choosing UDP as protcol

	if (sock < 0)
	{
		error("socket");
	}

	server.sin_family = AF_INET;

	strcpy(hostnm, clnt->hostname);

	hp = gethostbyname(hostnm);


	if (hp == 0)
	{

		error("Unknown host");
	}



	bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	server.sin_port = htons(clnt->address);					//Converting Hostname into network understandable form
	length = sizeof(struct sockaddr_in);					//Length of server address

	n = sendto(sock,buffer,strlen(buffer),0,&server,length);		//function called for sending of data from buffer using UDP to server

	close(sock);
	if (n < 0)
	{
		error("Sendto");
	}
	cnt++;
	//printf("%d",cnt);

	if (cnt < 11)
	{
		logfile = fopen("UDP_inp.txt","a");
		fprintf(logfile,"\nSent data is= ");
		fprintf(logfile,buffer);
		fclose(logfile);
	}
	else
	{
		logfile = fopen("UDP_inp.txt","w");
		fprintf(logfile,"\nSent data is= ");
		fprintf(logfile,buffer);
		fclose(logfile);
		cnt = 0;
	}
}






