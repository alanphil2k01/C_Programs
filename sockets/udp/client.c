#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 100

int main() {
    char buf[MAX];
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;

    unsigned int len = sizeof(addr);

    bzero(&addr, len);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1) {
        bzero(buf, MAX);
        printf("Enter message: ");
        scanf("%s", buf);
        sendto(client_fd, buf, MAX, 0, (struct sockaddr*) &addr, len);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }

        bzero(buf, MAX);
        recvfrom(client_fd, buf, MAX, 0, (struct sockaddr*) &addr, &len);
        printf("Server sent: %s\n", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }

    }

    close(client_fd);
    printf("Exiting.\n");
}
