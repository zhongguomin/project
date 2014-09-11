/*
 * receive.c
 * Description：Receive data from Serial_Port
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

#define max_buffer_size 100


int open_serial() {
	int fd = -1;

	fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
	//fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);
		
	if (fd < 0) {
		perror("open /dev/ttyUSB0");
		return -1;
	} 

	/*
	if (fcntl(fd, F_SETFL, FNDELAY) < 0) {
	//if(fcntl(fd, F_SETFL, 0) < 0) {
		printf("fcntl failed!\n");	
	}
	*/
		
	return fd;
}

int close_serial(int fd) {
	int ret = -1;
	ret = close(fd);
	if (ret < 0) {
		printf("Closec the Device failur！\n");
		return -1;
	}

	return 0;
}

void set_prop(int fd, struct termios opt) {
	tcgetattr(fd, &opt);
	cfmakeraw(&opt);

	cfsetispeed(&opt, B9600);
	cfsetospeed(&opt, B9600);

	// opt.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  // Input
	// opt.c_oflag  &= ~OPOST;   // Output

	// opt.c_cc[VTIME] = 31; // set timeout 15 seconds
	// opt.c_cc[VMIN] = 0; // Update the options and do it NOW 

	tcsetattr(fd, TCSANOW, &opt);
}

void read_data(int fd) {
	char hd[max_buffer_size], *rbuf;
	int retv, i, ncount = 0;
	int realdata = 0;
	
	rbuf = hd;
	retv = read(fd, rbuf, 1);

	if (retv == -1) {
		perror("read ");
		return;
	}

	while(*rbuf !='\n') {
		ncount += 1;
		rbuf++;

		retv = read(fd, rbuf, 1);
		if(retv == -1) {
			perror("read retv .. ");
		}
	}

	for(i=0; i<ncount; i++) {
		printf("%c", hd[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	int fd = -1;
	struct termios opt;

	fd = open_serial();
	if (fd == -1)	return -1;

	set_prop(fd, opt);
	read_data(fd);
	close_serial(fd);

	return 0;
}


