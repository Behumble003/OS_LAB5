#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 10  // Kích thước tối đa của mảng

int a[N];  // Mảng toàn cục
int count = 0;  // Số phần tử hiện có trong mảng
sem_t semaphore;  // Semaphore để đồng bộ hóa

void* producer(void* arg) {
    while (1) {
        int num = rand() % 100 + 1;
        sem_wait(&semaphore);  // Chờ semaphore
        if (count < N) {
            a[count] = num;
            count++;
            printf("Added %d to array a.\n", num);
            printf("Array a now has %d elements.\n", count);
        }
        sem_post(&semaphore);  // Giải phóng semaphore
        sleep(1);
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&semaphore);  // Chờ semaphore
        if (count > 0) {
            int num = a[count - 1];
            count--;
            printf("Removed %d from array a.\n", num);
            printf("Array a now has %d elements.\n", count);
        } else {
            printf("Nothing in array a.\n");
        }
        sem_post(&semaphore);  // Giải phóng semaphore
        sleep(1.5);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&semaphore, 0, 1);  // Khởi tạo semaphore với giá trị 1

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&semaphore);  // Hủy semaphore

    return 0;
}
