#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

int sells = 0;
int products = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *processA(void *mess) {
    while(1) {
        pthread_mutex_lock(&mutex);
        while (sells >= products) {
            pthread_cond_wait(&cond, &mutex);
        }
        sells++;
        printf("sells = %d\n", sells);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        usleep(100000); // Để tránh chạy quá nhanh, bạn có thể điều chỉnh giá trị này
    }
    return NULL;
}

void *processB(void *mess) {
    while(1) {
        pthread_mutex_lock(&mutex);
        while (products >= sells + 123) {
            pthread_cond_wait(&cond, &mutex);
        }
        products++;
        printf("products = %d\n", products);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        usleep(100000); // Để tránh chạy quá nhanh, bạn có thể điều chỉnh giá trị này
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t pA, pB;
    pthread_create(&pA, NULL, processA, NULL);
    pthread_create(&pB, NULL, processB, NULL);

    pthread_join(pA, NULL); // Chờ các thread hoàn thành (không bao giờ xảy ra ở đây)
    pthread_join(pB, NULL); // Chờ các thread hoàn thành (không bao giờ xảy ra ở đây)

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
