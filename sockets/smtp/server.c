#include "common.h"

void handleSend(int sock_fd, char* msg) {
    if (send(sock_fd, msg, MAX, 0) < 0) {
        printf("Error in Sending %s to clien\n", msg);
        exit(1);
    }
    printf("Sending -> %s\n", msg);

}

void handleRecv(int sock_fd, char* expected, char* resp) {
    char msg[MAX];
    if (recv(sock_fd, msg, MAX, 0) < 0) {
        printf("Error in Receiving %s from clien\n", expected);
        exit(1);
    }
    printf("Client -> %s\n", msg);
    if (strncmp(msg, expected, strlen(expected)) != 0) {
        printf("%s expected from clien\n", expected);
        exit(1);
    }
    handleSend(sock_fd, resp);
}

int main() {
    int s_fd;
    int c_fd;
    struct sockaddr_in addr, caddr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((s_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Cannot create socket\n");
        return 1;
    }

    if((bind(s_fd, (struct sockaddr*) &addr, sizeof(addr))) < 0) {
        printf("Cannot bind socket to address\n");
        return 1;
    }

    if (listen(s_fd, 5) < 0) {
        printf("Cannot listen\n");
        return 1;
    }

    socklen_t len;
    if ((c_fd = accept(s_fd, (struct sockaddr*) &caddr, &len)) < 0) {
        printf("Cannot accept connection\n");
        return 1;
    }

    char msg[MAX];
    if (recv(c_fd, msg, MAX, 0) < 0) {
        printf("Error in Receiving greeting from clien\n");
        return 1;
    }
    printf("Received -> %s\n", msg);

    handleSend(c_fd, "220 127.0.0.1");

    handleRecv(c_fd, "HELO", "250 ok");

    handleRecv(c_fd, "MAIL FROM", "250 ok");

    handleRecv(c_fd, "RCPT TO", "250 ok");

    handleRecv(c_fd, "DATA", "354 go ahead");

    if (recv(c_fd, msg, MAX, 0) < 0) {
        printf("Error in Receiving mail body from clien\n");
        return 1;
    }
    printf("Mail body received:-\n%s\n", msg);

    handleRecv(c_fd, "QUIT", "221 good bye");

    close(c_fd);
    close(s_fd);
}
