#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080
#define MAX 100

int main() {
    char buf[MAX];
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;

    unsigned int len = sizeof(addr);

    bzero(&addr, len);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    connect(client_fd, (struct sockaddr*) &addr, len);

    while(1) {
        bzero(buf, MAX);
        printf("Enter message: ");
        scanf("%s", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }
        send(client_fd, buf, MAX, 0);

        bzero(buf, MAX);
        recv(client_fd, buf, MAX, 0);
        printf("Server sent: %s\n", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }

    }

    close(client_fd);
    printf("Exiting.\n");
}
