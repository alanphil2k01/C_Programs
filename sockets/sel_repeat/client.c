#include "common.h"
#include <math.h>
#include <time.h>

int isFault() {
    int r = rand()%10;
    return (r > 6);
}

void sendNAK(int sock_fd, int num) {
    char buf[10];
    bzero(buf, 10);
    strncpy(buf, "NAK: ", 5);
    buf[strlen(buf)] = num + '0';
    buf[strlen(buf)] = '\0';
    send(sock_fd, &buf, MAX, 0);
    printf("Sent -> %s\n", buf);
}

void sendACK(int sock_fd, int num) {
    char buf[10];
    bzero(buf, 10);
    strncpy(buf, "ACK: ", 5);
    buf[strlen(buf)] = num + '0';
    buf[strlen(buf)] = '\0';
    send(sock_fd, &buf, MAX, 0);
    printf("Sent -> %s\n", buf);
}

int main() {
    srand(time(NULL));

    int w_size = pow(2, NUM_OF_BITS - 1);
    int window[w_size];
    memset(window, 0, sizeof(window));
    int seq = pow(2, NUM_OF_BITS);
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

    char buf[MAX];

    int expected = 0;
    int num_frames = 0;
    int sf = 0;
    int sn = 0;
    int f = 0;

    while(num_frames <= NUM_OF_FRAMES) {
        for (int i=0; i<w_size; i++) printf("%d", window[i]);
        printf("\n");
        f = 0;
        for (sn = sf; sn != (sf+w_size)%seq; sn=(sn + 1)%seq) {
            if (window[sn - sf]) continue;
            bzero(buf, MAX);
            recv(c_fd, buf, MAX, 0);
            printf("Received -> %s\n", buf);
            int n = buf[strlen(buf) - 1] - '0';
            if (isFault() && !window[n-sf]) {
                printf("The message was corrupted\n");
                window[n-sf] = 0;
            } else if(!window[n-sf]) {
                f = 1;
                window[n-sf] = 1;
                num_frames++;
            }
        }
        for (int i=0; i<w_size; i++) printf("%d", window[i]);
        printf("\n");
        for (int i = 0; i < w_size; i++) {
            if (window[i]) {
                if (f) {
                    sendACK(c_fd, (sf+i)%seq);
                }
            } else {
                sendNAK(c_fd, (sf+i)%seq);
            }
        }
        if (!f) {
            for(int i = 0; i < w_size; i++) {
                window[i] = 0;
            }
            sf = (sf + w_size) % seq;
            printf("new window = [%d, %d)", sf, (sf+w_size)%seq);
        }
    }

    close(c_fd);
}
