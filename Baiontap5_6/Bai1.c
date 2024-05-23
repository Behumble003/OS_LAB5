#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int x1, x2, x3, x4, x5, x6;
int w = -1, v = -1, y = -1, z = -1, ans;
pthread_mutex_t mutex;
pthread_cond_t cond_w, cond_v, cond_y, cond_z, cond_y_final, cond_z_final;

void *compute_w(void *arg) {
    pthread_mutex_lock(&mutex);
    w = x1 * x2;
    printf("w = %d\n", w);
    pthread_cond_broadcast(&cond_w); // Báo hiệu rằng w đã được tính xong
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *compute_v(void *arg) {
    pthread_mutex_lock(&mutex);
    v = x3 * x4;
    printf("v = %d\n", v);
    pthread_cond_broadcast(&cond_v); // Báo hiệu rằng v đã được tính xong
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *compute_y(void *arg) {
    pthread_mutex_lock(&mutex);
    while (v == -1) { // Đợi cho đến khi v được tính xong
        pthread_cond_wait(&cond_v, &mutex);
    }
    y = v * x5;
    printf("y = %d\n", y);
    pthread_cond_signal(&cond_y); // Báo hiệu rằng y đã được tính xong
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *compute_z(void *arg) {
    pthread_mutex_lock(&mutex);
    while (v == -1) { // Đợi cho đến khi v được tính xong
        pthread_cond_wait(&cond_v, &mutex);
    }
    z = v * x6;
    printf("z = %d\n", z);
    pthread_cond_signal(&cond_z); // Báo hiệu rằng z đã được tính xong
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *compute_final_y(void *arg) {
    pthread_mutex_lock(&mutex);
    while (w == -1 || y == -1) { // Đợi cho đến khi w và y được tính xong
        pthread_cond_wait(&cond_w, &mutex);
        pthread_cond_wait(&cond_y, &mutex);
    }
    y = w * y;
    printf("final y = %d\n", y);
    pthread_cond_signal(&cond_y_final); // Báo hiệu rằng final y đã được tính xong
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *compute_final_z(void *arg) {
    pthread_mutex_lock(&mutex);
    while (w == -1 || z == -1) { // Đợi cho đến khi w và z được tính xong
        pthread_cond_wait(&cond_w, &mutex);
        pthread_cond_wait(&cond_z, &mutex);
    }
    z = w * z;
    printf("final z = %d\n", z);
    pthread_cond_signal(&cond_z_final); // Báo hiệu rằng final z đã được tính xong
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *compute_ans(void *arg) {
    pthread_mutex_lock(&mutex);
    while (y == -1 || z == -1) { // Đợi cho đến khi y và z được tính xong
        pthread_cond_wait(&cond_y_final, &mutex);
        pthread_cond_wait(&cond_z_final, &mutex);
    }
    ans = y + z;
    printf("ans = %d\n", ans);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t th_v, th_w, th_y, th_z, th_final_y, th_final_z, th_ans;

    // Khởi tạo các mutex và condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_w, NULL);
    pthread_cond_init(&cond_v, NULL);
    pthread_cond_init(&cond_y, NULL);
    pthread_cond_init(&cond_z, NULL);
    pthread_cond_init(&cond_y_final, NULL);
    pthread_cond_init(&cond_z_final, NULL);

    // Gán giá trị cho các biến
    x1 = 1; x2 = 2; x3 = 3; x4 = 4; x5 = 5; x6 = 6;

    // Tạo các thread
    pthread_create(&th_v, NULL, compute_v, NULL);
    pthread_create(&th_w, NULL, compute_w, NULL);
    pthread_create(&th_y, NULL, compute_y, NULL);
    pthread_create(&th_z, NULL, compute_z, NULL);
    pthread_create(&th_final_y, NULL, compute_final_y, NULL);
    pthread_create(&th_final_z, NULL, compute_final_z, NULL);
    pthread_create(&th_ans, NULL, compute_ans, NULL);

    // Chờ các thread hoàn thành
    pthread_join(th_v, NULL);
    pthread_join(th_w, NULL);
    pthread_join(th_y, NULL);
    pthread_join(th_z, NULL);
    pthread_join(th_final_y, NULL);
    pthread_join(th_final_z, NULL);
    pthread_join(th_ans, NULL);

    // Hủy mutex và condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_w);
    pthread_cond_destroy(&cond_v);
    pthread_cond_destroy(&cond_y);
    pthread_cond_destroy(&cond_z);
    pthread_cond_destroy(&cond_y_final);
    pthread_cond_destroy(&cond_z_final);


    return 0;
}
