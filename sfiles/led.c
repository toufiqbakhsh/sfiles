#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>


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
	if(value >= 0 && value <=31)
	{
		sprintf(direction_path+16, "%s%d%s", "PA", value, "/direction");
		sprintf(value_path+16,"%s%d%s", "PA",value,"/value");
	}else if(value >= 32 && value <=63)
	{
		sprintf(direction_path+16, "%s%d%s", "PA", value-32, "/direction");
                sprintf(value_path+16,"%s%d%s", "PA",value-32,"/value");
	}
	else if(value >=64 && value <= 95)
	{
		sprintf(direction_path+16, "%s%d%s", "PA", value-64, "/direction");
                sprintf(value_path+16,"%s%d%s", "PA",value-64,"/value");
	}
	else 
	{
		sprintf(direction_path+16, "%s%d%s", "PA", value-96, "/direction");
                sprintf(value_path+16,"%s%d%s", "PA",value-96,"/value");
	}

	fd = open(direction_path,O_WRONLY);
	write(fd,"out", 4);
	close(fd);
	fd = open(value_path,O_WRONLY);
	while(count--)
	{
                write(fd,"0",2);
                printf("LED %d ON \n",value);
                sleep(2);

		write(fd,"1",2);
		printf("LED %d OFF \n", value);
		sleep(2);

	}
	close(fd);
}
