#include "common.h"
#include <math.h>

int isFault() {
    int r = rand()%10;
    return (r > 8);
}

void sendMSG(int sock_fd, int num) {
    char buf[10];
    bzero(buf, 10);
    strncpy(buf, "MSG: ", 5);
    buf[strlen(buf)] = num + '0';
    printf("Sent -> %s\n", buf);;
    send(sock_fd, &buf, MAX, 0);
}

int main() {
    srand(time(NULL));

    int seq = pow(2, NUM_OF_BITS);
    int w_size = pow(2, NUM_OF_BITS - 1);
    int sf = 0, sn = 0;
    int s_fd, c_fd;
    struct sockaddr_in addr, newAddr;
    socklen_t len;

    s_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(s_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        printf("Could not bind to port %d\n", PORT);
        return 1;
    }

    listen(s_fd, 10);

    c_fd = accept(s_fd, (struct sockaddr*) &addr, &len);

    char msg[50] = "MSG: ";
    char buf[MAX];

    int expected = 1;
    int num_frames = 0;
    int window[w_size];
    memset(window, 0, sizeof(window));
    int f = 0;
    int j;

    while(num_frames <= NUM_OF_FRAMES) {
        f = 0;
        for (sn = sf, j = num_frames; sn != (sf+w_size)%seq; sn=(sn + 1)%seq) {
            if (!window[sn - sf]) {
                f = 1;
                sendMSG(c_fd, sn);
                j++;
            }
        }
        for (int i=0; i<w_size; i++) printf("%d", window[i]);
        printf("\n");
        for (int i = 0; i < w_size; i++) {
            bzero(buf, MAX);
            recv(c_fd, buf, MAX, 0);
            printf("Received -> %s\n", buf);
            int n = buf[strlen(buf) - 1] - '0';
            if (strncmp(buf, "ACK", 3) == 0 && !window[i]) {
                window[i] = 1;
                num_frames++;
            } else if (strncmp(buf, "NAK", 3) == 0 && !window[i]) {
                window[i] = 0;
            }
        }
        for (int i=0; i<w_size; i++) printf("%d", window[i]);
        printf("\n");
        f = 0;
        for (int i=0; i<w_size; i++) {
            if(!window[i]) {
                f=1;
                break;
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

    close(s_fd);
}
