#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#define  GPIO_EN    "/sys/class/gpio/export"
#define  GPIO_DIR   "/sys/class/gpio/PC13/direction"
#define  GPIO_VAL   "/sys/class/gpio/PC13/value"

int main()
{
 int gpio_fd;
 char gpiobuff[30];
 int gpionum = 81;
int count =20;
 gpio_fd = open(GPIO_EN,O_WRONLY);
 if(gpio_fd < 0 ) {
  printf("Unable to open %s",GPIO_EN);
  exit(0);
 } 
 printf("Enabling the GPIO");
 sprintf(gpiobuff,"%d",gpionum);
 write(gpio_fd,gpiobuff,strlen(gpiobuff));
 close(gpio_fd); 
 printf("Configuring GPIO Direction-1 \n");
 gpio_fd = open(GPIO_DIR,0666);
 if(gpio_fd < 0 )
 {
  printf("Unable to open %s",GPIO_DIR);
  exit(0);
 }
 printf("Configurint the GPIO Direction-2");
 write(gpio_fd,"out",3);
 close(gpio_fd);
 gpio_fd = open(GPIO_VAL,0666);
 if(gpio_fd < 0 ) {
  printf("Unable to open %s",GPIO_VAL);
  exit(0);
 } printf("Toggling the GPIO");

 while(count--)
 { 
 write(gpio_fd,"1",1);
  sleep(1);
  write(gpio_fd,"0",1);
  sleep(1);
 } 
close(gpio_fd); 
}
