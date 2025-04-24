#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_THREADS 3
void *task(void *arg) {
    int thread_id = *((int *)arg);
    printf("Thread %d started.\n", thread_id);
    sleep(2);  
    printf("Thread %d finished.\n", thread_id);
    free(arg); 
    return NULL;
}
int main() {
    pthread_t threads[NUM_THREADS];
    printf("Main thread: Creating %d threads.\n", NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++) {
        int *thread_id = (int *)malloc(sizeof(int));
        if (thread_id == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1;
        if (pthread_create(&threads[i], NULL, task, thread_id) != 0) {
            perror("Error creating thread");
            free(thread_id);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) 
        pthread_join(threads[i], NULL);
    printf("Main thread: All threads completed.\n");
    return 0;
}