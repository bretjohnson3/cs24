/*
 * General implementation of semaphores.
 *
 *--------------------------------------------------------------------
 * Adapted from code for CS24 by Jason Hickey.
 * Copyright (C) 2003-2010, Caltech.  All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#include "sthread.h"
#include "semaphore.h"
#include "queue.h"
#include "glue.h"

/*
 * The semaphore data structure contains an integer representing its value
 * and a queue which will contain blocked threads to ensure fairness.
 */
struct _semaphore {
    int size;
    Queue *q;
};

/************************************************************************
 * Top-level semaphore implementation.
 */

/*
 * Allocate a new semaphore.  The initial value of the semaphore is
 * specified by the argument.
 */
Semaphore *new_semaphore(int init) {

    Semaphore * semp = malloc(sizeof(Semaphore));
    if (semp == NULL)
    {
        printf("Semaphore allocation failed!\n");
        exit(1);
    }
    semp->size = init;

    semp->q = malloc(sizeof(Queue));
    if (semp->q == NULL)
    {
        printf("Queue allocation failed\n");
        exit(1);
    }
    return semp;
}

/*
 * Decrement the semaphore.
 * This operation must be atomic, and it blocks iff the semaphore is zero.
 */
void semaphore_wait(Semaphore *semp) {
    // Initial lock since this operation must be atomic
    __sthread_lock();
    while (semp->size == 0)
    {
        queue_append(semp->q, sthread_current());
        sthread_block();

        // We have to lock again since block calls unlock
        __sthread_lock();
    }

    semp->size--;

    // Unlock since the function has completed
    __sthread_unlock();
}

/*
 * Increment the semaphore.
 * This operation must be atomic.
 */
void semaphore_signal(Semaphore *semp) {
    // Initial lock since this operation must be atomic
    __sthread_lock();
    semp->size++;
    if (!queue_empty(semp->q))
    {
        sthread_unblock(queue_take(semp->q));
    }
    // Unlock since this operation is complete
    __sthread_unlock();
}
