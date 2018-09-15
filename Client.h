#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define UDP_MAXBUF 1024
//*****************************************************************
// * CLient_UDP: Structure defined for initialization of following parameters.
// * Arguc = Number of arguments required from command line, the requirements on the UDP client is 3
// * Port_char = The port number to which the client will connect for passing UDP packets to the server.
// * Address = Port_char is converted into network understandable format and stored within address
// * Hostname = The IP address of the UDP server
//*****************************************************************

typedef struct {
	int arguc;
	char port_char[UDP_MAXBUF];
	int address;
	char hostname[100];

} client_UDP;


//*****************************************************************
// * UDP_client_init : Function defined for intitalization of UDP client parameters such as port_char and hostname.
// * The input to the function is a pointer to the structure defined for client_UDP
//*****************************************************************
void UDP_client_init(client_UDP * clnt);

//*****************************************************************
// * error: Function to flag errors if any initialization fails
//*****************************************************************

void error(char *);

//*****************************************************************
// * client : Function responsible for setting up connection between server and client through UDP.
// * Responsible for pushing data using UDP to server.
// * Takes in a string of data from the buffer and transmits it susing UDP
//*****************************************************************
void client(client_UDP * clnt, char data[],int length_ret);



