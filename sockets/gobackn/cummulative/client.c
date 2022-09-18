#include "common.h"
#include <math.h>

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

    struct timeval timeout = { 2, 0 };
    setsockopt(c_fd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));

    char msg[50] = "ACK: ";
    char buf[MAX];
    int f = 0;

    int expected = 0;
    int num_frames = 0;
    while(num_frames < NUM_OF_FRAMES) {
        bzero(buf, MAX);
        if (recv(c_fd, &buf, MAX, 0) > 0) {
            int n = buf[strlen(buf) - 1] - '0';
            if (n == expected) {
                f = 1;
                printf("Received %s\n", buf);
                num_frames++;
                expected = (expected + 1)%seq;
            } else {
                if (f) {
                    bzero(buf, MAX);
                    strncpy(buf, msg, 5);
                    buf[strlen(buf)] = expected + '0';
                    buf[strlen(buf)] = '\0';
                    send(c_fd, &buf, MAX, 0);
                    printf("Sent -> %s\n", buf);
                    f = 0;
                }
                printf("Expected %d, got %d\n", expected, n);
            }
        } else if (f) {
            bzero(buf, MAX);
            strncpy(buf, msg, 5);
            buf[strlen(buf)] = expected + '0';
            buf[strlen(buf)] = '\0';
            send(c_fd, &buf, MAX, 0);
            printf("Sent -> %s\n", buf);
            f = 0;
        }
        printf("-------------------------------------------\n");
        usleep(100*1000);
    }

    close(c_fd);
}
