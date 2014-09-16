/**
 *  receive_02.c
 *
 *  http://cboard.cprogramming.com/c-programming/98649-serial-port-read-blocking.html
 */

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
         
#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttyS0"
#define FALSE 0
#define TRUE 1
        
      int main() {
         
        printf("Start\n");
         
        int fd, res;
        struct termios oldtio,newtio;
        char buf[255];
         
        fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
        if (fd <0) {
            printf("Failed to open %s", MODEMDEVICE);
        } // if
         
        else {
            printf("Port Opened\n");
            tcgetattr(fd,&oldtio); /* save current port settings */
            bzero(&newtio, sizeof(newtio));
            newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
            newtio.c_iflag = IGNPAR;
            newtio.c_oflag = 0;
             
            // set input mode (non-canonical, no echo,...) */
            newtio.c_lflag = 0;
            newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
            newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */
            tcflush(fd, TCIFLUSH);
            tcsetattr(fd,TCSANOW,&newtio);
 
            res = read(fd,buf,255);   /* returns after 5 chars have been input */
            buf[res]=0;               /* so we can printf... */
            printf("Input: %s\n", buf);
            tcsetattr(fd,TCSANOW,&oldtio);
        } // else */
        printf("Done\n");
        return 0;
      } // main

