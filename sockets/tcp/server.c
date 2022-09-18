#include <bits/types/struct_timeval.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define MAX 100

int main() {
    char buf[MAX];
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_fd;

    struct sockaddr_in addr;

    unsigned int len = sizeof(addr);

    bzero(&addr, len);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*) &addr, len) < 0) {
        perror("Couldn't bind socket\n");
        _exit(1);
    }
    listen(server_fd, 5);

    bzero(&addr, len);
    client_fd = accept(server_fd, (struct sockaddr*) &addr, &len);

    while(1) {
        bzero(buf, MAX);
        recv(client_fd, buf, MAX, 0);
        printf("Client sent: %s\n", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }

        bzero(buf, MAX);
        printf("Enter message: ");
        scanf("%s", buf);
        if (!strncmp(buf, "exit", 4)) {
            break;
        }
        send(client_fd, buf, MAX, 0);

    }

    close(server_fd);
    printf("Exiting.\n");
}
