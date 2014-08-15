/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char *str_1 = "iios/12DDWDFF@122";
    char buf[24];
    sscanf(str_1, "%*[^/]/%[^@]", buf);
    printf("[%s] => %s\n", str_1, buf);

	char *str_2 = "/dev/block/vold/93:72 /mnt/sdcard";
	char device_path[256];
	char mount_path[256];
	sscanf(str_2, "%255s %255s\n", device_path, mount_path);
	printf("[%s] => %s %s\n", str_2, device_path, mount_path);
	
	char *str_3 = "/dev/block/vold/93:72";
	int major = 0, minor = 0;
	sscanf(str_3, "/%*[^/]/%*[^/]/%*[^/]/%d:%d", &major, &minor);
	printf("[%s] => %d %d\n", str_3, major, minor);

	char *str_4 = "  93       72    4734976 nandj";
	int p_major = 0, p_minor = 0;
	sscanf(str_4, "%d %d", &p_major, &p_minor);
	printf("[%s] => %d %d\n", str_4, p_major, p_minor);


	// 
	FILE *fp = NULL;
	char line[1024];
	int m_major = 0, m_minor = 0;
    if (!(fp = fopen("/proc/partitions", "r"))) {
        return -1;
    }

    // line: 93       72    4734976 nandj
	printf("-----------------\n");
    while(fgets(line, sizeof(line), fp)) {
        line[strlen(line)-1] = '\0';
        sscanf(line, "%d %d", &m_major, &m_minor);
        printf("%d %d\n", m_major, m_minor);
    }
	printf("-----------------\n");

	fclose(fp);
	fp = NULL;

	return 0;
}
