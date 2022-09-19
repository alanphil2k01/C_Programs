#include <stdio.h>

int main() {
    int dist[20] = {0};
    int seen[20] = {0};
    int prev[20] = {0};
    int cost_mat[20][20] = {0};

    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        cost_mat[i][i] = 0;
        for (int j = i+1; j < n; j++) {
            printf("%d to %d: ", i, j);
            scanf("%d", &cost_mat[i][j]);
            cost_mat[j][i] = cost_mat[i][j];
            if (cost_mat[i][j] < 0) {
                cost_mat[i][j] = 1000;
                cost_mat[j][i] = 1000;
            }
        }
    }
    printf("The cost matrix is:-\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", cost_mat[i][j]);
        }
        printf("\n");
    }

    int src;
    printf("Enter source router: ");
    scanf("%d", &src);

    for (int i = 0; i < n; i++) {
        dist[i] = cost_mat[src][i];
        prev[i] = src;
    }
    seen[src] = 1;

    int min;
    int v;
    for (int i = 0; i < n; i++) {
        min = 1000;
        for (int w = 0; w < n; w++) {
            if (!seen[w]) {
                if (dist[w] < min) {
                    v = w;
                    min = dist[w];
                }
            }
        }
        seen[v] = 1;
        for (int w = 0; w < n; w++) {
            if (!seen[w]) {
                if (dist[w] > min + cost_mat[v][w]) {
                    dist[w] = min + cost_mat[v][w];
                    prev[w] = v;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        printf("\n%d => %d: Path taken: %d", src, i, i);
        int w = i;
        while (w != src) {
            printf("<-%d", prev[w]);
            w = prev[w];
        }
        printf("\nshortest path cost: %d", dist[i]);
    }
    printf("\n");
}
