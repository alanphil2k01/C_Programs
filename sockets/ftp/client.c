#include "common.h"
#include <sys/time.h>

int main() {
	int s_fd;
	int c_fd;
	struct sockaddr_in addr;
	socklen_t len;

	addr.sin_family = AF_INET;
	addr.sin_port = PORT;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	c_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(c_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		printf("Cannot connect\n");
		return 1;
	}

	char filename[30];
	printf("Enter filename: ");
	scanf("%s", filename);
	send(c_fd, &filename, sizeof(filename), 0);
	printf("Receiving file: %s\n", filename);

    char buf[MAX];
    while (recv(c_fd, buf, MAX, 0) > 0 ) {
        printf("%s", buf);
    }

	close(c_fd);
}
