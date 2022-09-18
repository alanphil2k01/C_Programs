#include "common.h"
#include <math.h>

int isFault() {
    int r = rand()%10;
    return (r>7);
}

int main() {
    srand(time(NULL));

    int w_size = 1;
    int seq = pow(2, NUM_OF_BITS);
    int sf = 0, sn = 0;
    int c_fd;
    struct sockaddr_in addr, newAddr;
    socklen_t len;

    c_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(c_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        printf("Could not connect to server %d\n", PORT);
        return 1;
    }

    char msg[50] = "ACK: ";
    char buf[MAX];

    int expected = 0;
    int num_frames = 0;
    while(num_frames < NUM_OF_FRAMES) {
        if (recv(c_fd, &buf, MAX, 0)) {
            printf("Received %s\n", buf);
            int n = buf[strlen(buf) - 1] - '0';
            if (n == expected) {
                printf("Received %s\n", msg);
                expected = (expected + 1) % seq;
                bzero(buf, MAX);
                strncpy(buf, msg, 5);
                buf[strlen(buf)] = expected + '0';
                buf[strlen(buf)] = '\0';
                send(c_fd, &buf, MAX, 0);
                num_frames++;
                printf("Sent -> %s\n", buf);
            } else {
                printf("Expected %d, got %d\n", expected, n);
            }
        }
        usleep(800);
        printf("-------------------------------------------\n");
    }

    close(c_fd);
}
