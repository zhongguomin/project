/*
 * receive.c
 *
 * Description：ReceivedatafromSerial_Port
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "math.h"

#define max_buffer_size 100 /*定义缓冲区最大宽度*/

int fd, s;

int open_serial(int k) {
	if ( k == 0) {
		// fd = open("/dev/ttyS0", O_RDWR|O_NOCTTY); /*读写方式打开串口*/
		
		// fd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY); /*读写方式打开串口*/
		fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY |  O_NONBLOCK); /*读写方式打开串口*/
		// fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK); /*读写方式打开串口*/
		
		perror("open/dev/ttyUSB0");
	} else {
		fd = open("/dev/ttyS1", O_RDWR|O_NOCTTY);
		perror("open/dev/ttyS1");
	}

	if (fd == -1) {
		return -1;
	} 

	// if(fcntl(fd, F_SETFL, FNDELAY) < 0) {
	if(fcntl(fd, F_SETFL, 0) < 0) {
		printf("fcntl failed!\n");	
	}
		
	return 0;
}

int main() {
	char hd[max_buffer_size], *rbuf;/*定义接收缓冲区*/
	int flag_close, retv, i, ncount = 0;
	struct termios opt;
	int realdata = 0;

	open_serial(0);

	tcgetattr(fd, &opt);
	cfmakeraw(&opt);

	cfsetispeed(&opt,B9600);/*波特率设置为9600bps*/
	cfsetospeed(&opt,B9600);

	// opt.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
	// opt.c_oflag  &= ~OPOST;   /*Output*/

	//
	opt.c_cc[VTIME] = 31; /* 设置超时15 seconds*/  
	opt.c_cc[VMIN] = 0; /* Update the options and do it NOW */

	tcsetattr(fd,TCSANOW,&opt);
	rbuf="hd";/*数据保存*/

	printf("readyforreceivingdata...\n");
	retv=read(fd,rbuf,1); /*接收数据*/

	if (retv == -1) {
		perror("read");/*读状态标志判断*/
	}

	while(*rbuf !='\n') { /*判断数据是否接收完毕*/
		ncount += 1;
		rbuf++;
		retv=read(fd,rbuf,1);
		if(retv==-1) {
			perror("read");
		}
	}

	printf("Thedatareceivedis:\n");/*输出接收到的数据*/

	for(i=0; i<ncount; i++) {
		printf("%c",hd[i]);
	}

	printf("\n");

	flag_close = close(fd);
	if(flag_close == -1) { /*判断是否成功关闭文件*/
		printf("ClosetheDevicefailur！\n");
	}

	return 0;
}





