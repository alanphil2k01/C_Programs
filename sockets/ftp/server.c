#include "common.h"
#include <stdio.h>
#include <sys/time.h>

int main() {
    int s_fd;
	int c_fd;
	struct sockaddr_in addr, caddr;
	socklen_t len;

	addr.sin_family = AF_INET;
	addr.sin_port = PORT;
	addr.sin_addr.s_addr = INADDR_ANY;

	s_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(s_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		printf("Cannot bind\n");
		return 1;
	}

	listen(s_fd, 5);

	c_fd = accept(s_fd, (struct sockaddr*) &caddr, &len);

	char filename[30];
	recv(c_fd, &filename, sizeof(filename), 0);
	printf("Sending file: %s\n", filename);

	FILE *fd = fopen(filename, "r");
	char *buf = malloc(sizeof(char)*MAX);

	while (fgets(buf, MAX, fd) != NULL) {
        send(c_fd, buf, MAX, 0);
	}

	fclose(fd);
	close(s_fd);
	close(c_fd);
}
