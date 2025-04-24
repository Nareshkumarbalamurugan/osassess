#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
int counter = 0;
pthread_mutex_t lock;
int num_threads, iterations; 
void *task(void *arg) {
    int thread_id = *((int *)arg);
    free(arg);
    for (int i = 0; i < iterations; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        printf("Thread %d: Incremented counter to %d\n", thread_id, counter);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}
int main() {
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    printf("Enter the number of iterations per thread: ");
    scanf("%d", &iterations);
    pthread_t threads[num_threads];
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }
    for (int i = 0; i < num_threads; i++) {
        int *thread_id = (int *)malloc(sizeof(int));
        if (thread_id == NULL) {
            perror("Failed to allocate memory");
            return 1;
        }
        *thread_id = i + 1;
        pthread_create(&threads[i], NULL, task, thread_id);
    }
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
    pthread_mutex_destroy(&lock);
    printf("Final Counter Value: %d\n", counter);
    return 0;
}