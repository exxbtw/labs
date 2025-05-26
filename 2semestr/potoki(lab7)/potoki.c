#include <stdio.h>
#include <unistd.h>    //sleep
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NOF_THREADS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int turn = 0; //0 — main, 1 — thread

void kill(void *a){
    printf("Dead %s\n", (char*)a);
}

void* routine_sync(void *a) {
    pthread_t tid = pthread_self();
    pthread_cleanup_push(kill, a);

    for(int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) pthread_cond_wait(&cond, &mutex); //пока оч не дошла
        printf("%s hello from slave thread %p\n", (char*) a, tid);
        turn = 0;
        pthread_cond_signal(&cond); //сигнал родительскому
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    pthread_cleanup_pop(1);
    return NULL;
}

void* sleepsort_routine(void* arg) {
    int val = *(int*)arg;
    usleep(val * 1000);
    printf("%d ", val);
    fflush(stdout);
    free(arg);
    return NULL;
}

void SleepSort(int *sort, int len){
    pthread_t tid[len];
    for(int i = 0; i < len; i++){
        int *val = malloc(sizeof(int));
        *val = sort[i];
        pthread_create(&tid[i], NULL, sleepsort_routine, val);
    }
    for(int i = 0; i < len; i++){
        pthread_join(tid[i], NULL);
    }
    printf("\n");
}

//перемножение с pthread
typedef struct {
    int id;
    int start_row; //диапазон строк
    int end_row;
    int **A, **B, **C;
    int N;
} ThreadData;

void *matrix_routine(void *arg) {
    ThreadData *data = (ThreadData*) arg; 
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->N; j++) {
            data->C[i][j] = 0;
            for (int k = 0; k < data->N; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
}

void fill_matrix(int **mat, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[i][j] = 1;
}

void print_matrix(int **mat, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    //синхронный вывод
    char str[] = ">>>"; 
    pthread_t sync_thread;
    pthread_create(&sync_thread, NULL, routine_sync, str);
//Для основного
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 0) pthread_cond_wait(&cond, &mutex);
        printf("%s hello from main thread %p\n", str, pthread_self());
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_join(sync_thread, NULL);

    //перемножение матриц NxN
    if (argc != 3) {
        printf("Usage: %s N num_threads\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]); //преобразуется строковый аргумент в число N(размер кв матриц)
    int num_threads = atoi(argv[2]);

    int **A = malloc(N * sizeof(int*));
    int **B = malloc(N * sizeof(int*));
    int **C = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
    }

    fill_matrix(A, N);
    fill_matrix(B, N);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int rows_per_thread = N / num_threads;
    int extra = N % num_threads;
    int current_row = 0;

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_threads; i++) {
        int rows = rows_per_thread + (i < extra ? 1 : 0);
        thread_data[i] = (ThreadData){i, current_row, current_row + rows, A, B, C, N};
        pthread_create(&threads[i], NULL, matrix_routine, &thread_data[i]);
        current_row += rows;
    }

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000.0 +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

    printf("Matrix multiplication completed. Time: %.2f ms\n", elapsed);

    if (N <= 5) {
        printf("Matrix A:\n"); print_matrix(A, N);
        printf("Matrix B:\n"); print_matrix(B, N);
        printf("Matrix C:\n"); print_matrix(C, N);
    }

    for (int i = 0; i < N; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);

    printf("Sleepsort:\n");
    int numbers[] = {33, 15, 50, 23, 46};
    SleepSort(numbers, 5);

    return 0;
}
