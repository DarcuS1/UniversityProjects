#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "a2_helper.h"
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUM_THREADS_5 4
#define NUM_THREADS_3 36
#define CONC_THREADS 4
#define NUM_THREADS_8 6

sem_t sem_t5_1;
sem_t sem_t5_2;
sem_t *sem_t5_3;
sem_t *sem_t8_2;
sem_t *sem_t8_5;
sem_t sem;

void *thread_func3(void *arg)
{
    int tid = *(int *)arg;
    info(BEGIN, 3, tid);
    info(END, 3, tid);

    pthread_exit(NULL);
}

void *thread_func3_12(void *arg)
{
    int tid = *(int *)arg;
    sem_wait(&sem);
    info(BEGIN, 3, tid);
    info(END, 3, tid);
    sem_post(&sem);
    pthread_exit(NULL);
}

void *thread_func5(void *arg)
{
    int tid = *(int *)arg;
    info(BEGIN, 5, tid);
    info(END, 5, tid);

    pthread_exit(NULL);
}

void *thread_func5_3(void *arg)
{
    int tid = *(int *)arg;
    sem_wait(sem_t8_2);
    info(BEGIN, 5, tid);
    info(END, 5, tid);

    pthread_exit(NULL);
}

void *thread_func8(void *arg)
{
    int tid = *(int *)arg;
    info(BEGIN, 8, tid);
    info(END, 8, tid);

    pthread_exit(NULL);
}

void *thread_func8_2(void *arg)
{
    int tid = *(int *)arg;
    info(BEGIN, 8, tid);
    info(END, 8, tid);
    sem_post(sem_t8_2);
    pthread_exit(NULL);
}

void *thread_func8_5(void *arg)
{
    int tid = *(int *)arg;
    sem_wait(sem_t8_5);
    info(BEGIN, 8, tid);
    info(END, 8, tid);

    pthread_exit(NULL);
}

void *thread_func5_1(void *arg)
{
    sem_wait(&sem_t5_2);
    int tid = *(int *)arg;
    info(BEGIN, 5, tid);
    info(END, 5, tid);
    sem_post(&sem_t5_1);
    pthread_exit(NULL);
}

void *thread_func5_2(void *arg)
{
    int tid = *(int *)arg;
    info(BEGIN, 5, tid);
    sem_post(&sem_t5_2);
    sem_wait(&sem_t5_1);
    info(END, 5, tid);
    pthread_exit(NULL);
}

int main()
{
    int pid2, pid4, pid3, pid5, pid7, pid6, pid8, pid9;
    pthread_t threads3[NUM_THREADS_3];
    pthread_t threads5[NUM_THREADS_5];
    pthread_t threads8[NUM_THREADS_8];

    int tids3[NUM_THREADS_3] = {0};
    int tids5[NUM_THREADS_5] = {0};
    int tids8[NUM_THREADS_8] = {0};

    sem_init(&sem_t5_1, 0, 0);
    sem_init(&sem_t5_2, 0, 0);

    init();

    info(BEGIN, 1, 0);

    pid2 = fork();
    if (pid2 == 0)
    {
        info(BEGIN, 2, 0);

        pid3 = fork();
        if (pid3 == 0)
        {
            info(BEGIN, 3, 0);

            pid6 = fork();
            if (pid6 == 0)
            {
                info(BEGIN, 6, 0);
                info(END, 6, 0);
                exit(0);
            }
            if (pid6 == -1)
            {
                exit(pid6);
            }

            waitpid(pid6, NULL, 0);

            sem_init(&sem, 0, CONC_THREADS);

            for (int i = 0; i < NUM_THREADS_3; i++)
            {
                tids3[i] = i + 1;
                if (pthread_create(&threads3[i], NULL, thread_func3, &tids3[i]) < 0)
                {
                    exit(-1);
                }

                if ((i + 1) % CONC_THREADS == 0)
                {
                    int j, ok = 0;
                    for (j = i - CONC_THREADS + 1; j <= i; j++)
                    {
                        if (j == 11)
                        {
                            ok = 1;
                        }
                    }
                    if (ok == 1)
                    {
                        pthread_join(threads3[11], NULL);
                        ok = 0;
                    }
                    for (j = i - CONC_THREADS + 1; j <= i; j++)
                    {
                        if (j == 11)
                        {
                            ok = 0;
                        }
                        else
                        {

                            pthread_join(threads3[j], NULL);
                        }
                    }
                }
            }
            int ok2 = 0;
            for (int i = NUM_THREADS_3 - (NUM_THREADS_3 % CONC_THREADS); i < NUM_THREADS_3; i++)
            {
                if (i == 11)
                {
                    ok2 = 1;
                }
            }
            if (ok2 == 1)
            {
                pthread_join(threads3[11], NULL);
                ok2 = 0;
            }
            for (int i = NUM_THREADS_3 - (NUM_THREADS_3 % CONC_THREADS); i < NUM_THREADS_3; i++)
            {
                if (i == 11)
                {
                    ok2 = 0;
                }
                else
                {
                    pthread_join(threads3[i], NULL);
                }
            }

            sem_destroy(&sem);
            info(END, 3, 0);
            exit(0);
        }
        if (pid3 == -1)
        {
            exit(pid3);
        }

        pid5 = fork();
        if (pid5 == 0)
        {

            info(BEGIN, 5, 0);

            sem_t8_2 = sem_open("t8-2", O_CREAT, S_IRUSR | S_IWUSR, 0);
            sem_t8_5 = sem_open("t8-5", O_CREAT, S_IRUSR | S_IWUSR, 0);
            sem_t5_3 = sem_open("t5-3", O_CREAT, S_IRUSR | S_IWUSR, 0);

            pid8 = fork();
            if (pid8 == 0)
            {
                info(BEGIN, 8, 0);

                sem_t8_2 = sem_open("t8-2", 0);
                sem_t8_5 = sem_open("t8-5", 0);
                sem_t5_3 = sem_open("t5-3", 0);

                pid9 = fork();
                if (pid9 == 0)
                {
                    info(BEGIN, 9, 0);
                    info(END, 9, 0);
                    exit(0);
                }
                if (pid9 == -1)
                {
                    exit(pid9);
                }

                waitpid(pid9, NULL, 0);

                tids8[1] = 1;
                if (pthread_create(&threads8[1], NULL, thread_func8, &tids8[1]) < 0)
                {
                    exit(-1);
                }
                tids8[2] = 2;
                if (pthread_create(&threads8[2], NULL, thread_func8_2, &tids8[2]) < 0)
                {
                    exit(-1);
                }
                pthread_join(threads8[2], NULL);

                tids8[3] = 3;
                if (pthread_create(&threads8[3], NULL, thread_func8, &tids8[3]) < 0)
                {
                    exit(-1);
                }
                tids8[4] = 4;
                if (pthread_create(&threads8[4], NULL, thread_func8, &tids8[4]) < 0)
                {
                    exit(-1);
                }
                tids8[5] = 5;
                if (pthread_create(&threads8[5], NULL, thread_func8_5, &tids8[5]) < 0)
                {
                    exit(-1);
                }
                tids8[6] = 6;
                if (pthread_create(&threads8[6], NULL, thread_func8, &tids8[6]) < 0)
                {
                    exit(-1);
                }

                for (int i = 1; i <= NUM_THREADS_8; i++)
                {
                    if (i != 2)
                    {
                        pthread_join(threads8[i], NULL);
                    }
                }

                info(END, 8, 0);

                exit(0);
            }
            if (pid8 == -1)
            {
                exit(pid8);
            }

            tids5[1] = 1;
            if (pthread_create(&threads5[1], NULL, thread_func5_1, &tids5[1]) < 0)
            {
                exit(-1);
            }

            tids5[2] = 2;
            if (pthread_create(&threads5[2], NULL, thread_func5_2, &tids5[2]) < 0)
            {
                exit(-1);
            }

            tids5[3] = 3;
            if (pthread_create(&threads5[3], NULL, thread_func5_3, &tids5[3]) < 0)
            {
                exit(-1);
            }
            pthread_join(threads5[3], NULL);
            sem_post(sem_t8_5);

            tids5[4] = 4;
            if (pthread_create(&threads5[4], NULL, thread_func5, &tids5[4]) < 0)
            {
                exit(-1);
            }

            for (int i = 1; i <= NUM_THREADS_5; i++)
            {
                if (i != 3)
                {
                    pthread_join(threads5[i], NULL);
                }
            }

            waitpid(pid8, NULL, 0);

            info(END, 5, 0);

            exit(0);
        }
        if (pid5 == -1)
        {
            exit(pid5);
        }

        pid7 = fork();
        if (pid7 == 0)
        {
            info(BEGIN, 7, 0);
            info(END, 7, 0);
            exit(0);
        }
        if (pid7 == -1)
        {
            exit(pid7);
        }

        waitpid(pid3, NULL, 0);
        waitpid(pid5, NULL, 0);
        waitpid(pid7, NULL, 0);

        info(END, 2, 0);
        exit(0);
    }
    if (pid2 == -1)
    {
        exit(pid2);
    }

    pid4 = fork();
    if (pid4 == 0)
    {
        info(BEGIN, 4, 0);
        info(END, 4, 0);
        exit(0);
    }
    if (pid4 == -1)
    {
        exit(pid4);
    }

    waitpid(pid2, NULL, 0);
    waitpid(pid4, NULL, 0);
    sem_destroy(&sem_t5_1);
    sem_destroy(&sem_t5_2);
    sem_close(sem_t5_3);
    sem_close(sem_t8_2);
    sem_close(sem_t8_5);
    sem_unlink("t8-2");
    sem_unlink("t8-5");
    sem_unlink("t5-3");

    info(END, 1, 0);
    return 0;
}

