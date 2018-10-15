#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sthread.h"
#include "queue.h"

/* This thread function adds three over and over again */
static void add_three(void *n)
{
    int new = *((int*)n);
    while (new <= 1000)
    {
        printf("Adding %d to %d\n", 3, new);

        new += 3;
        sthread_yield();
    }
}
/* This thread function subtracts five over and over again */
static void sub_five(void *n)
{
    int new = *((int*)n);
    while (new >= 0)
    {
        printf("Subtracting %d from %d\n", 2, new);
        new -= 5;
        sthread_yield();
    }
}

/* The function runs these loop functions on separate threads with the
starting value of 600 */
int main()
{
    int n = 600;
    sthread_create(add_three, (void*)&n);
    sthread_create(sub_five, (void*)&n);
    sthread_start();

    return 0;

}
