/*******************************************************************************
 * Copyright (C) 2023 by Salvador Z                                            *
 *                                                                             *
 * This file is part of ELSU                                                   *
 *                                                                             *
 *   Permission is hereby granted, free of charge, to any person obtaining a   *
 *   copy of this software and associated documentation files (the Software)   *
 *   to deal in the Software without restriction including without limitation  *
 *   the rights to use, copy, modify, merge, publish, distribute, sublicense,  *
 *   and/or sell copies ot the Software, and to permit persons to whom the     *
 *   Software is furnished to do so, subject to the following conditions:      *
 *                                                                             *
 *   The above copyright notice and this permission notice shall be included   *
 *   in all copies or substantial portions of the Software.                    *
 *                                                                             *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   *
 *   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARANTIES OF MERCHANTABILITY *
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL   *
 *   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR      *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,     *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE        *
 *   OR OTHER DEALINGS IN THE SOFTWARE.                                        *
 ******************************************************************************/

/**
 * @file sync_thread.c
 * @author Salvador Z
 * @date 26 Mar 2023
 * @brief File for show how-to use pthreads
 *
 * @see https://linux.die.net/man/3/pthread_join
 */

#include <pthread.h>
#include <stdio.h>  /*streams> fopen, fputs*/
#include <stdlib.h> /*NULL (stddef)*/
#include <unistd.h>
#define THREADS_NUM 2
typedef struct thread_args {
  int tid;
} thread_args_t;

int N = 10;
pthread_mutex_t g_mutex;
pthread_cond_t  g_cond;
int const thread_count = THREADS_NUM;
int last[THREADS_NUM] = {0};

/* Prints a char to stderr.  The parameter is received by pthread_create.  Does not return.  */

void *print_N(void *thread_arg) {

  thread_args_t data = (*(thread_args_t *)thread_arg);
  for (int i = 1; i <= N; i++)
  {

    pthread_mutex_lock(&g_mutex);
    if (i > last[(thread_count-1) - data.tid] + 1) {
        pthread_cond_wait(&g_cond, &g_mutex);
    }
    fputc(i-1+'0', stderr);
    last[data.tid] = i-1;
    pthread_cond_signal(&g_cond);
    pthread_mutex_unlock(&g_mutex);

  }
//fputc('\n', stderr);

  return NULL;
}

/* The main program. */
int main() {

  pthread_t     thread_1_id, thread_2_id, thread_3_id;
  thread_args_t thread_1_arg, thread_2_arg, thread_3_arg;

  if (0 != pthread_mutex_init(&g_mutex, NULL))
    return -1;
  
  thread_1_arg.tid = 0;
  /* Create a new thread.  */
  pthread_create(&thread_1_id, NULL, &print_N, &thread_1_arg);

  thread_2_arg.tid = 1;
  /* Create a new thread. */
  pthread_create(&thread_2_id, NULL, &print_N, &thread_2_arg);

  thread_3_arg.tid = 2;
  /* Create a new thread. */
  pthread_create(&thread_3_id, NULL, &print_N, &thread_3_arg);

  /* waiting for the threads*/
  pthread_join(thread_1_id, NULL);
  pthread_join(thread_2_id, NULL);
  pthread_join(thread_3_id, NULL);
  fputc('\n', stderr);
  return 0;
}