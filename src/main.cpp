#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include "uartFunc.h"
#include "bleProtocol.h"

#define RECEIVE_BUFFER_SIZE	512

int main(int argc, char **argv)
{
	bool KeepGoing = true;
	int fdUart;	
	int nread;
	unsigned char recBuff[RECEIVE_BUFFER_SIZE];
	
	if( argc != 2 )
	{
		printf("USAGE: uart_transmit UART_PORT\r\n");
		return -1;
	}

	fdUart = uartOpen(argv[1]);
	uartSetSpeed(fdUart, 115200);

	if (uartSetParity(fdUart,8,1,'N') == -1)
	{
		printf("Set Parity Error\n");
		return -1;
	}
	else
	{
		printf("%s connected\r\n", argv[1]);
	}
	
	while (KeepGoing)
	{
		memset(recBuff, 0, RECEIVE_BUFFER_SIZE);
		while((nread = read(fdUart, recBuff, 512))>0)
		{
			printf("Received %d bytes\r\n", nread);
			for(int i=0; i<nread; i++)
			{
				printf("0x%02X", recBuff[i]);
				if( recBuff[i] >= 0x20 && recBuff[i] < 127 )
				{
					printf(" (%c), ", recBuff[i]);
				}
				else
				{
					printf(", ");
				}
			}
			printf("\r\n");
		}
	}

	close(fdUart);
	
	return 0;
}

// end of file
