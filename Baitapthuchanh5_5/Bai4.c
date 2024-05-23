#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t mutex;

void *processA(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("ProcessA: %d\n", x);
        pthread_mutex_unlock(&mutex);
        usleep(100000); // Sleep for 100ms
    }
    return NULL;
}

void *processB(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("ProcessB: %d\n", x);
        pthread_mutex_unlock(&mutex);
        usleep(150000); // Sleep for 150ms
    }
    return NULL;
}

int main()
{
    pthread_t pA, pB;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pA, NULL, processA, NULL);
    pthread_create(&pB, NULL, processB, NULL);

    pthread_join(pA, NULL);
    pthread_join(pB, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
