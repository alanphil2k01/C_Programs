#include "common.h"
#include <math.h>

int isFault() {
    int r = rand()%10;
    return (r>7);
}

int main() {
    srand(time(NULL));

    int seq = pow(2, NUM_OF_BITS);
    int w_size = pow(2, NUM_OF_BITS) - 1;
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
    struct timeval timeout = { 5, 0 };
    setsockopt(c_fd, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout));

    char msg[50] = "MSG: ";
    char buf[MAX];

    int expected = 1;
    int frames_success = 0;
    while(frames_success < NUM_OF_FRAMES) {
        for (int i = sf, j = frames_success; i != (sf + w_size)%seq && j < NUM_OF_FRAMES; i=(i+1)%seq, j++) {
            bzero(buf, MAX);
            strncpy(buf, msg, 5);
            buf[strlen(buf)] = i + '0';
            if(isFault()) {
                continue;
            }
            printf("Sent: %s\n", buf);;
            send(c_fd, &buf, MAX, 0);
        }
        while(1) {
            bzero(buf, MAX);
            int m_len = recv(c_fd, &buf, MAX, 0);
            if (m_len > 0) {
                printf("Received %s\n", buf);
                char c = buf[strlen(buf) - 1];
                int n = c - '0';
                if (n == expected) {
                    sf = (sf + 1) % seq;
                    expected = (expected + 1) % seq;
                    frames_success++;
                    if (frames_success < NUM_OF_FRAMES) {
                        bzero(buf, MAX);
                        strncpy(buf, msg, 5);
                        buf[strlen(buf)] = ((sf + w_size - 1)%seq) + '0';
                        if(isFault()) {
                            continue;
                        }
                        printf("Sent -> %s\n", buf);;
                        send(c_fd, &buf, MAX, 0);
                    } else {
                        break;
                    }
                    continue;
                } else {
                    break;
                }
            } else {
                printf("Did not receive ACK for: %d\n", expected);
                printf("Resending from sequence number %d\n", sf);
                break;
            }
        }
    }

    close(s_fd);
}
