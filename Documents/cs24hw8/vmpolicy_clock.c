/*============================================================================
 * Implementation of the RANDOM page replacement policy.
 *
 * We don't mind if paging policies use malloc() and free(), just because it
 * keeps things simpler.  In real life, the pager would use the kernel memory
 * allocator to manage data structures, and it would endeavor to allocate and
 * release as little memory as possible to avoid making the kernel slow and
 * prone to memory fragmentation issues.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "vmpolicy.h"


/*============================================================================
 * "Clock" Data Structure
 *
 * This data structure represents a node that will fill our queue to determine
 * which page should be evicted based on a FIFO policy.
 */

 typedef struct loaded_pages_t {
     /* The maximum number of pages that can be resident in memory at once. */
     int max_resident;

     /* The number of pages that are currently loaded.  This can initially be
      * less than max_resident.
      */
     int num_loaded;

     /* integer corresponding to the index where the clock hand is pointing */
     int hand;

     /* This is the array of pages that are actually loaded.  Note that only the
      * first "num_loaded" entries are actually valid.
      */
     page_t pages[];


 } loaded_pages_t;


/*============================================================================
 * Policy Implementation
 */


 /* The list of pages that are currently resident. */
 static loaded_pages_t *loaded;


/* Initialize the policy.  Return nonzero for success, 0 for failure. */
int policy_init(int max_resident) {
    fprintf(stderr, "Using CLOCK eviction policy.\n\n");

    loaded = malloc(sizeof(loaded_pages_t) + max_resident * sizeof(page_t));
    if (loaded) {
        loaded->max_resident = max_resident;
        loaded->num_loaded = 0;
        loaded->hand = 0;
    }

    /* Return nonzero if initialization succeeded. */
    return (loaded != NULL);
}


/* Clean up the data used by the page replacement policy. */
void policy_cleanup(void) {
    free(loaded);
    loaded = NULL;
}


/* This function is called when the virtual memory system maps a page into the
 * virtual address space.  Record that the page is now resident.
 */
void policy_page_mapped(page_t page) {
    assert(loaded->num_loaded < loaded->max_resident);
    /* Make sure mapping is within bounds to created circular array */
    int index = (loaded->num_loaded + loaded->hand) % loaded->max_resident;
    loaded->pages[index] = page;
    loaded->num_loaded++;
}


/* This function is called when the virtual memory system has a timer tick. */
void policy_timer_tick(void) {
    /* Do nothing! */
}


/* Choose a page to evict from the collection of mapped pages.  Then, record
 * that it is evicted.  This is very simple since we are implementing a random
 * page-replacement policy.
 */
page_t choose_and_evict_victim_page(void) {

    page_t victim;

    /* Figure out which page to evict. */

    while(1)
    {
        // If it is accessed move the hand
        if (is_page_accessed(loaded->pages[loaded->hand]))
        {
            clear_page_accessed(loaded->pages[loaded->hand]);
            set_page_permission(loaded->pages[loaded->hand], PAGEPERM_NONE);
            loaded->hand++;
            loaded->hand = (loaded->hand % loaded->max_resident);
        }
        // Otherwise, move the hand then return
        else
        {
          victim = loaded->pages[loaded->hand];
          loaded->hand++;
          loaded->hand = loaded->hand % loaded->max_resident;
          break;
        }
    }


    /* Shrink the collection of loaded pages now, by moving the last page in the
     * collection into the spot that the victim just occupied.
     */
    loaded->num_loaded--;


#if VERBOSE
    fprintf(stderr, "Choosing victim page %u to evict.\n", victim);
#endif

    return victim;
}
