#include <stdio.h>

struct node {
    unsigned dist[20];
    unsigned next[20];
} rt[20];

int main() {
    int nodes, count = 0;
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("\nEnter the cost matrix:-\n");
    for(int i=0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &rt[i].dist[j]);
            rt[i].next[j] = j;
        }
        rt[i].dist[i] = 0;
    }

    do {
        count = 0;
        for(int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                for (int k = 0; k < nodes; k++) {
                    if (rt[i].dist[j] > rt[i].dist[k] + rt[k].dist[j]) {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].next[j] = k;
                        count++;
                    }
                }
            }
        }
    } while(count != 0);

    for (int i = 0; i < nodes; i++) {
        printf("\nFor router %d\n", i+1);
        for (int j=0; j < nodes; j++) {
            printf("\t\nnode %d via %d. Distance %d", j+1, rt[i].next[j]+1, rt[i].dist[j]);
        }
    }
}
