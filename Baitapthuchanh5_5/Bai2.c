#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10  // Kích thước tối đa của mảng

int a[N];  // Mảng toàn cục
int count = 0;  // Số phần tử hiện có trong mảng

void* producer(void* arg) {
    while (1) {
        int num = rand() % 100 + 1;
        if (count < N) {
            a[count] = num;
            count++;
            printf("Added %d to array a.\n", num);
            printf("Array a now has %d elements.\n", count);
        }
        sleep(1);
    }
}

void* consumer(void* arg) {
    while (1) {
        if (count > 0) {
            int num = a[count - 1]; //lấy số cuối cùng ra khỏi mảng
            count--;
            printf("Removed %d from array a.\n", num);
            printf("Array a now has %d elements.\n", count);
        } else {
            printf("Nothing in array a.\n");
        }
        sleep(1.5);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, &producer, NULL);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
