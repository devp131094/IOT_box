
#include "Client.h"
#include "buffer.h"
#include "Encryption.h"
#include "SPI.h"



#define FILENAME "config.conf"
#define DELIM "="


struct config get_config(char *filename)
{
        struct config configstruct;
        FILE *file = fopen (filename, "r");

        if (file != NULL)
        {
                char line[MAXBUF];
                int i = 0;

                while(fgets(line, sizeof(line), file) != NULL)
                {
                        char *cfline;
                        cfline = strstr((char *)line,DELIM);
                        cfline = cfline + strlen(DELIM);

                        if (i == 0){
                                memcpy(configstruct.buffer_size,cfline,strlen(cfline));
                                //printf("%s",configstruct.imgserver);
                        } else if (i == 1){
                                memcpy(configstruct.overwrite,cfline,strlen(cfline));
                                //printf("%s",configstruct.overwrite);
                        } else if (i == 2){
                                memcpy(configstruct.timer_duration,cfline,strlen(cfline));
                                //printf("%s",configstruct.timer_duration);
			}

                        i++;
                } // End while
                fclose(file);
        } // End if file



        return configstruct;

}


int main()
{
	char data[100];							//Array for transfering data between ADC after packaging and buffer for storage
	int timer;
	
	
	wiringPiSetup() ;
	mcp3004Setup (MY_PIN, SPI_CHAN); // 3004 and 3008 are the same 4/8 channels




   	struct config configstruct;				//Definations for using the config file and loading it into the structure config
    	configstruct = get_config(FILENAME);

	circular_buf_t cbuf;
	client_UDP clnt;

	UDP_client_init(&clnt);					//UDP client initialization

	buffer_init(&cbuf,&configstruct);		//buffer initialization
	circular_buf_reset(&cbuf); 				//set head/tail to 0

	timer = timer_reset(&configstruct);


	while(1)
	{
		strcpy(data,"");
		ADC_in(data);

		buffer(&clnt, &cbuf, &configstruct ,data ,timer);
		if(circular_buf_empty(&cbuf))
		{
			timer = timer_reset(&configstruct);
		}
	}
}
