#include "common.h"

void handleSend(int sock_fd, char* msg, char *expected) {
    if (send(sock_fd, msg, MAX, 0) < 0) {
        printf("Error in Sending %s to clien\n", msg);
        exit(1);
    }
    printf("Sending -> %s\n", msg);
    char buf[MAX];
    if (recv(sock_fd, buf, MAX, 0) < 0) {
        printf("Error in Receiving %s from server\n", expected);
        exit(1);
    }
    printf("Received -> %s\n", buf);
    if (strncmp(buf, expected, strlen(expected)) != 0) {
        printf("%s expected from server\n", expected);
        exit(1);
    }
}

int main() {
    int c_fd;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Cannot create socket\n");
        return 1;
    }

    if((connect(c_fd, (struct sockaddr*) &addr, sizeof(addr))) < 0) {
        printf("Cannot bind socket to address\n");
        return 1;
    }

    char in[50], msg[MAX];

    handleSend(c_fd, "hi", "220");

    handleSend(c_fd, "HELO", "250");

    printf("Enter from email address: ");
    scanf("%s", in);
    strcpy(msg, "MAIL FROM ");
    strcat(msg, in);
    handleSend(c_fd, msg, "250");

    printf("Enter to email address: ");
    scanf("%s", in);
    strcpy(msg, "RCPT TO ");
    strcat(msg, in);
    handleSend(c_fd, msg, "250");

    handleSend(c_fd, "DATA", "354");

    printf("Enter mail data to be sent:-\n");
    bzero(&msg, sizeof(msg));
    int i = 0;
    while (1) {
        char c = getchar();
        if (c == '$') {
            msg[i] = '\0';
            break;
        }
        if (c == '\0') {
            continue;
        }
        msg[i++] = c;
    }
    if (send(c_fd, msg, MAX, 0) < 0) {
        printf("Error in Sending mail body to clien\n");
        exit(1);
    }
    printf("Sending mail body\n");

    handleSend(c_fd, "QUIT", "221");

    close(c_fd);
}
