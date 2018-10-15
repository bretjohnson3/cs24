/*! \file
 * Implementation of a simple memory allocator.  The allocator manages a small
 * pool of memory, provides memory chunks on request, and reintegrates freed
 * memory back into the pool.
 *
 * Adapted from Andre DeHon's CS24 2004, 2006 material.
 * Copyright (C) California Institute of Technology, 2004-2010.
 * All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "myalloc.h"


/*!
 * These variables are used to specify the size and address of the memory pool
 * that the simple allocator works against.  The memory pool is allocated within
 * init_myalloc(), and then myalloc() and free() work against this pool of
 * memory that mem points to.
 */
int MEMORY_SIZE;
unsigned char *mem;


static unsigned char *freeptr;

/* global variable for the size of the header */
#define HEAD_SIZE sizeof(int)

/*!
 * This function initializes both the allocator state, and the memory pool.  It
 * must be called before myalloc() or myfree() will work at all.
 *
 * Note that we allocate the entire memory pool using malloc().  This is so we
 * can create different memory-pool sizes for testing.  Obviously, in a real
 * allocator, this memory pool would either be a fixed memory region, or the
 * allocator would request a memory region from the operating system (see the
 * C standard function sbrk(), for example).
 */
void init_myalloc() {

    /*
     * Allocate the entire memory pool, from which our simple allocator will
     * serve allocation requests.
     */
    mem = (unsigned char *) malloc(MEMORY_SIZE);
    if (mem == 0) {
        fprintf(stderr,
                "init_myalloc: could not get %d bytes from the system\n",
		MEMORY_SIZE);
        abort();
    }
    /* Set freeptr to beginning of chunk of memory */
    freeptr = mem;
    // init the first head to the size of the memory chunk less the header size
    *(int *)freeptr = MEMORY_SIZE - HEAD_SIZE;
}


/*!
 * Attempt to allocate a chunk of memory of "size" bytes.  Return 0 if
 * allocation fails. Uses the best fit method to find a block. My method
 * searches for the smallest block that is big enough and then allocates it.
 * Note: Headers are ints with positive indicating available and negative
 * indicating allocated.
 */
unsigned char *myalloc(int size) {

    freeptr = mem;
    // variables for the best fit location and the size of the location
    unsigned char* best;
    int best_differential = MEMORY_SIZE;

    while (freeptr < mem + MEMORY_SIZE){
        // the size of the preceding block given by the header
        int space = *(int *)(freeptr);
        // check if the space is large enough for the desired allocation
      if (space > size + HEAD_SIZE)
      {
          // check if the space is smaller than the current best space
          if (space < best_differential && space > 0)
          {
              // if it's the best space of memory, update variables accordingly
              best_differential = space;
              best = freeptr;
          }
      }
      // move the pointer to the next header
      freeptr += HEAD_SIZE + abs(*(int*)(freeptr));
    }

    // if a block was found for allocation
    if (MEMORY_SIZE > best_differential)
    {
        // Set the header accordingly
        *((int*) (best + HEAD_SIZE + size)) = *(int*)(best) - HEAD_SIZE - size;
        *(int*)(best) = -1 * size;
        // return pointer to the allocated block
        return best + HEAD_SIZE;
    }
    // If not found, print a useful message
    else
    {
        fprintf(stderr, "myalloc: cannot service request of size %d with"
              " %lx bytes allocated\n", size, (freeptr - mem));
        return (unsigned char *) 0;
    }
}


/*!
 * Free a previously allocated pointer.  oldptr should be an address returned by
 * myalloc().
 */
void myfree(unsigned char *oldptr) {
  // init freeptr to beginning of memory
  freeptr = mem;
  /* change the header of the block to deallocate to a positive int which is
  * deallocating the block in constant time */
  *(int*)(oldptr - HEAD_SIZE) = abs(*(int*)(oldptr - HEAD_SIZE));

  while (freeptr < mem + MEMORY_SIZE)
  {
      if (*(int*)(freeptr)>0)
      {
          // value of next header
          int next_header = *(int*)(freeptr + *(int*)(freeptr) + HEAD_SIZE);
          // check if the next header indicates an allocated block
          if (next_header > 0 && freeptr + *(int*)(freeptr) + HEAD_SIZE < mem +
            MEMORY_SIZE)
          {
          *(int*)(freeptr) = HEAD_SIZE + *(int*)(freeptr) + next_header;
          continue;
          }
      }
      // move the freeptr to next header
      freeptr += HEAD_SIZE + abs(*(int*)(freeptr));
  }
}

/*!
 * Clean up the allocator state.
 * All this really has to do is free the user memory pool. This function mostly
 * ensures that the test program doesn't leak memory, so it's easy to check
 * if the allocator does.
 */
void close_myalloc() {
    free(mem);
}
