#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define MAX 100

int main() {
    char buf[MAX];
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;

    unsigned int len = sizeof(addr);

    bzero(&addr, len);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*) &addr, len);

    while(1) {
        bzero(buf, MAX);
        recvfrom(server_fd, buf, MAX, 0, (struct sockaddr*) &addr, &len);
        printf("Client sent: %s\n", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }

        bzero(buf, MAX);
        printf("Enter message: ");
        scanf("%s", buf);
        sendto(server_fd, buf, MAX, 0, (struct sockaddr*) &addr, len);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }

    }

    close(server_fd);
    printf("Exiting.\n");
}

