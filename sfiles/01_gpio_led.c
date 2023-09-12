/*********************************************************************************************
 * © 2022 PHYTEC EMBEDDED PVT LTD. - All Rights Reserved. Permission to use, modify, copy, and distribute
 * this source code, object code, or executable code (collectively, Software), is granted only
 * under the terms of a valid written license agreement with PHYTEC. Unauthorized copying
 * or other use of the Software is strictly prohibited.  Software is owned by and constitutes
 * the proprietary works, trade secrets, and copyrights of Embitel or its licensors.
 *
 * For further information, contact PHYTEC EMBEDDED Pvt Ltd.
 *********************************************************************************************/
/*********************************************************************************************/
/*      Application: gpio_led.c
 *
 *      Brief: This application is to control the LEDs states(ON/OFF) using GPIO interface via /sys/fs entries
 *
 *      Author: PHYTEC EMBEDDED PVT LTD
 */
/*********************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include <unistd.h>


char export_path[] = "/sys/class/gpio/export";
char direction_path[] = "/sys/class/gpio/";
char value_path[] = "/sys/class/gpio/";
int count=10;


int main(int argc,char **argv)
{
	int fd;
	int value;
	fd = open(export_path,O_WRONLY);
	value = atoi(argv[1]);
	write(fd,argv[1],strlen(argv[1])+1);
	close(fd);
	if(value>=0 && value <=31)
	{
		sprintf(direction_path+16,"%s%d%s","PA",value,"/direction");
		sprintf(value_path+16,"%s%d%s","PA",value,"/value");
	}
	else if(value>=32 && value <=63)
	{
		sprintf(direction_path+16,"%s%d%s","PB",value-32,"/direction");
		sprintf(value_path+16,"%s%d%s","PB",value-32,"/value");
	}
	else if(value>=64 && value <=95)
	{
		sprintf(direction_path+16,"%s%d%s","PC",value-64,"/direction");
		sprintf(value_path+16,"%s%d%s","PC",value-64,"/value");
	}

	else
	{
		sprintf(direction_path+16,"%s%d%s","PD",value-96,"/direction");
		sprintf(value_path+16,"%s%d%s","PD",value-96,"/value");
	}
	
	fd = open(direction_path,O_WRONLY);
	write(fd,"out",4);
	close(fd);
	fd = open(value_path,O_WRONLY);
	write(fd,"1", 1);
/*	while(count--)
	{
                write(fd,"0",1);
//                printf("LED %d ON \n",value);
                sleep(5);
		write(fd,"1",1);
//		printf("LED %d OFF \n",value);
		sleep(5);
	}*/
	close(fd);
}
