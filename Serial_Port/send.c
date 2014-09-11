/**
 * send.c
 * Description：send data to serial_Port
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define max_buffer_size 100 


int open_serial(char* path) {
	int fd = -1;
	if (path == NULL || strlen(path) < 0)	return -1;
	
	fd = open(path, O_RDWR | O_NOCTTY); 
	if (fd < 0) {
		printf("open %s error..!!" , path);
		return -1;
	}
		
	return fd;
}

void close_serial(int fd) {
	if (close(fd) < 0) {
		printf("Close the Device failur！\n");
	}
}

void set_prop(int fd, struct termios opt) {
	tcgetattr(fd, &opt);
	cfmakeraw(&opt);

	cfsetispeed(&opt, B9600);
	cfsetospeed(&opt, B9600);
	tcsetattr(fd, TCSANOW, &opt);
}

void send_data(int fd, char* data, int size) {
	int ret = write(fd, data, size);
	if (ret < 0) {
		printf("write data error..!!");
	}
}

int main(int argc, char* argv[]) {
	int fd = -1;
	struct termios option;
	// serial port
	char path[] = "/dev/ttyS0";
	// send data, end up with '\n'
	char sendBuf[] = "Hello, this is a Serial_Port test data!\n";

	fd = open_serial(path);
	if (fd < 0)	return -1;

	set_prop(fd, option);
	send_data(fd, sendBuf, sizeof(sendBuf));
	close_serial(fd);

	return 0;
}




