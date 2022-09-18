#include <stdio.h>

int main() {

    int n;
    printf("Enter number of inputs: ");
    scanf("%d", &n);

    int bucket_cap;
    printf("Enter bucket capacity: ");
    scanf("%d", &bucket_cap);

    int output_rate;
    printf("Enter output rate: ");
    scanf("%d", &output_rate);

    int incoming, store = 0;
    while (n != 0) {
        printf("Enter the incoming packet size: ");
        scanf("%d", &incoming);

        if (incoming <= (bucket_cap - store)) {
            store += incoming;
            printf("Bucket byffer size %d out of %d\n", store, bucket_cap);
        } else {
            printf("Droppped %d no of packets\n", incoming - (bucket_cap - store));
            printf("Bucket buffer size %d out of %d\n", store, bucket_cap);
            store = bucket_cap;
        }
        store = store - output_rate;
        if (store < 0) {
            store = 0;
        }
        printf("After ougogin %d packets left out of %d in buffer\n", store, bucket_cap);
        n--;
    }

}
