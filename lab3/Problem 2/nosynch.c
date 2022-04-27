#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#include<unistd.h>

#define COUNT_LIMIT 20
#define NUM_THREADS 3
#define TCOUNT 100

int count = 10;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *inc_count(void *tid){
    int i;
    long my_id = (long) tid;
    for(i = 0; i < TCOUNT; i++){
        // pthread_mutex_lock(&count_mutex);
        count++;
        if(count == COUNT_LIMIT){
            printf("inc_count(): thread %ld, count = %d, threshhold reached.\n", my_id, count);
            // pthread_cond_signal(&count_threshold_cv);
            printf("Just sent signal \n");
        }

        printf("inc_count(): thread %ld, count = %d, unlocking mutex\n", my_id, count);
        // pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *watch_count(void *tid){
    long my_id = (long) tid;
    printf("Starting watch_count(): thread %ld\n", my_id);

    // pthread_mutex_lock(&count_mutex);
    while(count < COUNT_LIMIT){
        printf("watch_count(): thread %ld, count = %d, waiting...\n", my_id, count);
        // pthread_cond_wait(&count_threshold_cv, &count_mutex);
        printf("watch_count(): thread %ld. Count = %d\n", my_id, count);
        printf("watch_count(): thread %ld Updating the count value...\n", my_id);
        count+=80;
        printf("watch_count(): thread %ld count now = %d\n", my_id, count);
    }

    printf("watch_count(): thread %ld. Unlocking mutex. \n", my_id);
    // pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    int i, rc;
    pthread_t p1,p2,p3;
    long t1 = 1, t2 = 2, t3 = 3;
    pthread_attr_t attr;

    printf("main: begin\n");
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold_cv, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_create(&p1, &attr, watch_count, (void*)t1);
    pthread_create(&p2, &attr, inc_count, (void *)t2);
    pthread_create(&p3, &attr, inc_count, (void *)t3);

    rc = pthread_join(p1, NULL);    assert(rc == 0);
    rc = pthread_join(p2, NULL);    assert(rc == 0);
    rc = pthread_join(p3, NULL);    assert(rc == 0);

    printf("main: finish, final count = %d\n", count);

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    pthread_exit(NULL);

    return 0;
}

/*
main: begin
inc_count(): thread 3, count = 11, unlocking mutex
inc_count(): thread 2, count = 12, unlocking mutex
Starting watch_count(): thread 1
watch_count(): thread 1, count = 12, waiting...
inc_count(): thread 3, count = 13, unlocking mutex
inc_count(): thread 2, count = 14, unlocking mutex
inc_count(): thread 3, count = 15, unlocking mutex
inc_count(): thread 2, count = 16, unlocking mutex
inc_count(): thread 3, count = 17, unlocking mutex
inc_count(): thread 2, count = 18, unlocking mutex
inc_count(): thread 3, count = 19, unlocking mutex
inc_count(): thread 2, count = 20, threshhold reached.
Just sent signal 
inc_count(): thread 2, count = 20, unlocking mutex
watch_count(): thread 1. Count = 20
watch_count(): thread 1 Updating the count value...
watch_count(): thread 1 count now = 100
watch_count(): thread 1. Unlocking mutex. 
inc_count(): thread 3, count = 101, unlocking mutex
inc_count(): thread 2, count = 102, unlocking mutex
inc_count(): thread 3, count = 103, unlocking mutex
inc_count(): thread 2, count = 104, unlocking mutex
inc_count(): thread 3, count = 105, unlocking mutex
inc_count(): thread 2, count = 106, unlocking mutex
inc_count(): thread 2, count = 107, unlocking mutex
inc_count(): thread 3, count = 108, unlocking mutex
inc_count(): thread 2, count = 109, unlocking mutex
inc_count(): thread 3, count = 110, unlocking mutex
inc_count(): thread 3, count = 111, unlocking mutex
inc_count(): thread 2, count = 112, unlocking mutex
inc_count(): thread 2, count = 113, unlocking mutex
inc_count(): thread 3, count = 114, unlocking mutex
inc_count(): thread 3, count = 115, unlocking mutex
inc_count(): thread 2, count = 116, unlocking mutex
inc_count(): thread 2, count = 117, unlocking mutex
inc_count(): thread 3, count = 118, unlocking mutex
inc_count(): thread 3, count = 119, unlocking mutex
inc_count(): thread 2, count = 120, unlocking mutex
inc_count(): thread 2, count = 121, unlocking mutex
inc_count(): thread 3, count = 122, unlocking mutex
inc_count(): thread 3, count = 123, unlocking mutex
inc_count(): thread 2, count = 124, unlocking mutex
inc_count(): thread 2, count = 125, unlocking mutex
inc_count(): thread 3, count = 126, unlocking mutex
inc_count(): thread 3, count = 127, unlocking mutex
inc_count(): thread 2, count = 128, unlocking mutex
inc_count(): thread 3, count = 129, unlocking mutex
inc_count(): thread 2, count = 130, unlocking mutex
inc_count(): thread 3, count = 131, unlocking mutex
inc_count(): thread 2, count = 132, unlocking mutex
inc_count(): thread 2, count = 133, unlocking mutex
inc_count(): thread 3, count = 134, unlocking mutex
inc_count(): thread 3, count = 135, unlocking mutex
inc_count(): thread 2, count = 136, unlocking mutex
inc_count(): thread 2, count = 137, unlocking mutex
inc_count(): thread 3, count = 138, unlocking mutex
inc_count(): thread 2, count = 139, unlocking mutex
inc_count(): thread 3, count = 140, unlocking mutex
inc_count(): thread 2, count = 141, unlocking mutex
inc_count(): thread 3, count = 142, unlocking mutex
inc_count(): thread 2, count = 143, unlocking mutex
inc_count(): thread 3, count = 144, unlocking mutex
inc_count(): thread 2, count = 145, unlocking mutex
inc_count(): thread 3, count = 146, unlocking mutex
inc_count(): thread 2, count = 147, unlocking mutex
inc_count(): thread 3, count = 148, unlocking mutex
inc_count(): thread 2, count = 149, unlocking mutex
inc_count(): thread 3, count = 150, unlocking mutex
inc_count(): thread 2, count = 151, unlocking mutex
inc_count(): thread 3, count = 152, unlocking mutex
inc_count(): thread 2, count = 153, unlocking mutex
inc_count(): thread 3, count = 154, unlocking mutex
inc_count(): thread 2, count = 155, unlocking mutex
inc_count(): thread 3, count = 156, unlocking mutex
inc_count(): thread 2, count = 157, unlocking mutex
inc_count(): thread 3, count = 158, unlocking mutex
inc_count(): thread 2, count = 159, unlocking mutex
inc_count(): thread 3, count = 160, unlocking mutex
inc_count(): thread 2, count = 161, unlocking mutex
inc_count(): thread 3, count = 162, unlocking mutex
inc_count(): thread 2, count = 163, unlocking mutex
inc_count(): thread 3, count = 164, unlocking mutex
inc_count(): thread 2, count = 165, unlocking mutex
inc_count(): thread 3, count = 166, unlocking mutex
inc_count(): thread 2, count = 167, unlocking mutex
inc_count(): thread 3, count = 168, unlocking mutex
inc_count(): thread 2, count = 169, unlocking mutex
inc_count(): thread 3, count = 170, unlocking mutex
inc_count(): thread 2, count = 171, unlocking mutex
inc_count(): thread 3, count = 172, unlocking mutex
inc_count(): thread 2, count = 173, unlocking mutex
inc_count(): thread 3, count = 174, unlocking mutex
inc_count(): thread 2, count = 175, unlocking mutex
inc_count(): thread 3, count = 176, unlocking mutex
inc_count(): thread 2, count = 177, unlocking mutex
inc_count(): thread 3, count = 178, unlocking mutex
inc_count(): thread 2, count = 179, unlocking mutex
inc_count(): thread 3, count = 180, unlocking mutex
inc_count(): thread 2, count = 181, unlocking mutex
inc_count(): thread 3, count = 182, unlocking mutex
inc_count(): thread 2, count = 183, unlocking mutex
inc_count(): thread 3, count = 184, unlocking mutex
inc_count(): thread 2, count = 185, unlocking mutex
inc_count(): thread 3, count = 186, unlocking mutex
inc_count(): thread 2, count = 187, unlocking mutex
inc_count(): thread 3, count = 188, unlocking mutex
inc_count(): thread 2, count = 189, unlocking mutex
inc_count(): thread 3, count = 190, unlocking mutex
inc_count(): thread 2, count = 191, unlocking mutex
inc_count(): thread 3, count = 192, unlocking mutex
inc_count(): thread 2, count = 193, unlocking mutex
inc_count(): thread 3, count = 194, unlocking mutex
inc_count(): thread 2, count = 195, unlocking mutex
inc_count(): thread 3, count = 196, unlocking mutex
inc_count(): thread 2, count = 197, unlocking mutex
inc_count(): thread 3, count = 198, unlocking mutex
inc_count(): thread 2, count = 199, unlocking mutex
inc_count(): thread 3, count = 200, unlocking mutex
inc_count(): thread 2, count = 201, unlocking mutex
inc_count(): thread 3, count = 202, unlocking mutex
inc_count(): thread 2, count = 203, unlocking mutex
inc_count(): thread 3, count = 204, unlocking mutex
inc_count(): thread 2, count = 205, unlocking mutex
inc_count(): thread 3, count = 206, unlocking mutex
inc_count(): thread 2, count = 207, unlocking mutex
inc_count(): thread 3, count = 208, unlocking mutex
inc_count(): thread 2, count = 209, unlocking mutex
inc_count(): thread 3, count = 210, unlocking mutex
inc_count(): thread 2, count = 211, unlocking mutex
inc_count(): thread 3, count = 212, unlocking mutex
inc_count(): thread 2, count = 213, unlocking mutex
inc_count(): thread 3, count = 214, unlocking mutex
inc_count(): thread 2, count = 215, unlocking mutex
inc_count(): thread 3, count = 216, unlocking mutex
inc_count(): thread 2, count = 217, unlocking mutex
inc_count(): thread 3, count = 218, unlocking mutex
inc_count(): thread 2, count = 219, unlocking mutex
inc_count(): thread 3, count = 220, unlocking mutex
inc_count(): thread 2, count = 221, unlocking mutex
inc_count(): thread 3, count = 222, unlocking mutex
inc_count(): thread 2, count = 223, unlocking mutex
inc_count(): thread 3, count = 224, unlocking mutex
inc_count(): thread 2, count = 225, unlocking mutex
inc_count(): thread 3, count = 226, unlocking mutex
inc_count(): thread 2, count = 227, unlocking mutex
inc_count(): thread 3, count = 228, unlocking mutex
inc_count(): thread 2, count = 229, unlocking mutex
inc_count(): thread 3, count = 230, unlocking mutex
inc_count(): thread 2, count = 231, unlocking mutex
inc_count(): thread 3, count = 232, unlocking mutex
inc_count(): thread 2, count = 233, unlocking mutex
inc_count(): thread 3, count = 234, unlocking mutex
inc_count(): thread 2, count = 235, unlocking mutex
inc_count(): thread 3, count = 236, unlocking mutex
inc_count(): thread 2, count = 237, unlocking mutex
inc_count(): thread 3, count = 238, unlocking mutex
inc_count(): thread 2, count = 239, unlocking mutex
inc_count(): thread 3, count = 240, unlocking mutex
inc_count(): thread 2, count = 241, unlocking mutex
inc_count(): thread 3, count = 242, unlocking mutex
inc_count(): thread 2, count = 243, unlocking mutex
inc_count(): thread 3, count = 244, unlocking mutex
inc_count(): thread 2, count = 245, unlocking mutex
inc_count(): thread 3, count = 246, unlocking mutex
inc_count(): thread 2, count = 247, unlocking mutex
inc_count(): thread 3, count = 248, unlocking mutex
inc_count(): thread 2, count = 249, unlocking mutex
inc_count(): thread 3, count = 250, unlocking mutex
inc_count(): thread 2, count = 251, unlocking mutex
inc_count(): thread 3, count = 252, unlocking mutex
inc_count(): thread 2, count = 253, unlocking mutex
inc_count(): thread 3, count = 254, unlocking mutex
inc_count(): thread 2, count = 255, unlocking mutex
inc_count(): thread 3, count = 256, unlocking mutex
inc_count(): thread 2, count = 257, unlocking mutex
inc_count(): thread 3, count = 258, unlocking mutex
inc_count(): thread 2, count = 259, unlocking mutex
inc_count(): thread 3, count = 260, unlocking mutex
inc_count(): thread 2, count = 261, unlocking mutex
inc_count(): thread 3, count = 262, unlocking mutex
inc_count(): thread 2, count = 263, unlocking mutex
inc_count(): thread 3, count = 264, unlocking mutex
inc_count(): thread 2, count = 265, unlocking mutex
inc_count(): thread 3, count = 266, unlocking mutex
inc_count(): thread 2, count = 267, unlocking mutex
inc_count(): thread 3, count = 268, unlocking mutex
inc_count(): thread 2, count = 269, unlocking mutex
inc_count(): thread 3, count = 270, unlocking mutex
inc_count(): thread 2, count = 271, unlocking mutex
inc_count(): thread 3, count = 272, unlocking mutex
inc_count(): thread 2, count = 273, unlocking mutex
inc_count(): thread 3, count = 274, unlocking mutex
inc_count(): thread 2, count = 275, unlocking mutex
inc_count(): thread 3, count = 276, unlocking mutex
inc_count(): thread 2, count = 277, unlocking mutex
inc_count(): thread 3, count = 278, unlocking mutex
inc_count(): thread 2, count = 279, unlocking mutex
inc_count(): thread 3, count = 280, unlocking mutex
inc_count(): thread 2, count = 281, unlocking mutex
inc_count(): thread 3, count = 282, unlocking mutex
inc_count(): thread 2, count = 283, unlocking mutex
inc_count(): thread 3, count = 284, unlocking mutex
inc_count(): thread 2, count = 285, unlocking mutex
inc_count(): thread 3, count = 286, unlocking mutex
inc_count(): thread 2, count = 287, unlocking mutex
inc_count(): thread 3, count = 288, unlocking mutex
inc_count(): thread 2, count = 289, unlocking mutex
inc_count(): thread 3, count = 290, unlocking mutex
main: finish, final count = 290
*/
