#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>

#define RUN_TIMES 10000
#define THREAD_CNT 2

int run = 0;

uint64_t get_time() 
{
        struct timespec ts;
        
        clock_gettime(CLOCK_MONOTONIC, &ts);

        return ts.tv_sec * 1e9 + ts.tv_nsec;
}

static inline int execute_one() 
{
        char buf[32];
        int fd;
        int rt;

        fd = open("/sys/devices/system/cpu/cpu0/topology/die_id", O_RDONLY);
        if (fd < 0)
                return -1;
        
        rt = read(fd, buf, 32);
        if (rt < 0)
                return -1;

        rt = close(fd);
        if (rt < 0)
                return -1;
}

static int run_signle_thread() 
{
        int i;
        uint64_t start_time, end_time; 

        start_time = get_time();
        for (i = 0; i < RUN_TIMES; i++) {
                if (execute_one() < 0) {
                        printf("%s \n", strerror(errno));
                        return -1;
                }
        }
        end_time = get_time();

        printf("single: %fms\n", (end_time - start_time)/ 1e6);

        return 0;
}

static void* thread_run(void* args) 
{
        int i;
        uint64_t start_time, end_time; 

        while (!run) {
                sched_yield();
        }

        start_time = get_time();
        for (i = 0; i < RUN_TIMES; i++) {
                if (execute_one() < 0) {
                        printf("%s \n", strerror(errno));
                        return (void*) -1;
                }
        }
        end_time = get_time();

        printf("concur: %fms\n", (end_time - start_time)/ 1e6);

        return (void*) 0;
}

static int run_multiple_thread() 
{
        pthread_t thread_id[THREAD_CNT];
        int i;
        void *retval;

        for (int i = 0; i < THREAD_CNT; i++) {
                pthread_create(&thread_id[i], NULL, thread_run, NULL); 
        }

        run = 1;

        for (int i = 0; i < THREAD_CNT; i++) {
                pthread_join(thread_id[i], &retval);
                if (retval < 0)
                        return -1;
        }

        return 0;
}

int main(int argc, char const *argv[])
{
        int rt;
        int b_run_single, b_run_multiple;
        b_run_single = b_run_multiple = 1;

        if (argc == 2) {
                if (!strcmp(argv[1], "single"))
                        b_run_multiple = 0;

                if (!strcmp(argv[1], "multiple"))
                        b_run_single = 0;
        }

        if (b_run_single) {
                rt = run_signle_thread();
                if (rt < 0)
                        return -1;
        }

        if (b_run_multiple) {
                rt = run_multiple_thread();
                if (rt < 0)
                        return -1;
        }

        return 0;
}
