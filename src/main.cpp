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
	unsigned char cmdBuff[RECEIVE_BUFFER_SIZE];		
	unsigned char receiveBuffer[RECEIVE_BUFFER_SIZE];
	int receiveIndex = 0;
	int cmdSize;
	NaviStr naviInfo;
	BLE_COMMANDS cmd;
	
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
		while((nread = read(fdUart, recBuff, 512))>0)
		{
			printf("Received %d bytes\r\n", nread);
			
			if( nread+receiveIndex >= RECEIVE_BUFFER_SIZE )
			{
				printf("receiver buffer overflow. it must be something wrong.\r\n");
				// TODO...
				receiveIndex = 0;
			} 

			memcpy(receiveBuffer+receiveIndex, recBuff, nread); 
			receiveIndex += nread;
			
			#if 0
			// for debug test
			for(int i=0; i<receiveIndex; i++)
			{
				printf("%02X, ", receiveBuffer[i]);
			}
			printf("\r\n");
			
			receiveIndex = 0;
			#endif
			
			cmdSize = bleCheckCommand(recBuff, receiveIndex, cmdBuff);
			
			if( cmdSize > 0 )
			{
				#if 1
				// for debug test
				for(int i=0; i<cmdSize; i++)
				{
					printf("%02X, ", cmdBuff[i]);
				}
				printf("\r\n");
				#endif
				
				cmd = bleGetCommand(cmdBuff);
				printf("Command=%d\r\n", cmd);
				switch( cmd )
				{
					case COMMAND_NAVI_DIRECTION:
						bleNaviReconstruct(cmdBuff, &naviInfo);
						printf("distance=%d, direction=%d\r\n", naviInfo.distance, naviInfo.direction);
						break;
						
					default:
						printf("Uknown command (%d)\r\n", cmd);
						break;
				}
			}
		}
	}

	close(fdUart);
	
	return 0;
}

// end of file

