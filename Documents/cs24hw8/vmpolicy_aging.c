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

// Macros for the masks
#define EIGHT 0x80
#define SIXTEEN 0x8000
#define THIRTY_TWO 0x80000000


/*============================================================================
 * "Loaded Pages" Data Structure
 *
 * This data structure records all pages that are currently loaded in the
 * virtual memory, so that we can choose a random page to evict very easily.
 */

typedef struct loaded_pages_t {
    /* The maximum number of pages that can be resident in memory at once. */
    int max_resident;

    /* The number of pages that are currently loaded.  This can initially be
     * less than max_resident.
     */
    int num_loaded;

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
// array for ages
static uint32_t * ages;
// change this to account for different sizes
static int bit_mask = EIGHT;



/* Initialize the policy.  Return nonzero for success, 0 for failure. */
int policy_init(int max_resident) {
    fprintf(stderr, "Using AGING eviction policy.\n\n");

    loaded = malloc(sizeof(loaded_pages_t) + max_resident * sizeof(page_t));
    if (loaded) {
        loaded->max_resident = max_resident;
        loaded->num_loaded = 0;
    }
    ages = malloc(sizeof(uint32_t) * max_resident);
    if (ages == NULL)
    {
        printf("allocation failed! :(\n");
        abort();
    }

    /* Return nonzero if initialization succeeded. */
    return (loaded != NULL);
}


/* Clean up the data used by the page replacement policy. */
void policy_cleanup(void) {
    free(loaded);
    free(ages);
    loaded = NULL;
    ages = NULL;
}


/* This function is called when the virtual memory system maps a page into the
 * virtual address space.  Record that the page is now resident.
 */
void policy_page_mapped(page_t page) {
    assert(loaded->num_loaded < loaded->max_resident);
    loaded->pages[loaded->num_loaded] = page;
    ages[loaded->num_loaded] = bit_mask;
    loaded->num_loaded++;
}


/* This function is called when the virtual memory system has a timer tick. */
void policy_timer_tick(void) {
    for (int i = 0; i < loaded->num_loaded; i++)
    {
        // Shift all ages right
        ages[i] = ages[i] >> 1;
        if (is_page_accessed(loaded->pages[i]))
        {
            // Set bit to 1
            ages[i] = ages[i] ^ bit_mask;
            // clear the permissions and access bit
            clear_page_accessed(loaded->pages[i]);
            set_page_permission(loaded->pages[i], PAGEPERM_NONE);
        }
    }
}


/* Choose a page to evict from the collection of mapped pages.  Then, record
 * that it is evicted.  This is very simple since we are implementing a random
 * page-replacement policy.
 */
page_t choose_and_evict_victim_page(void) {
    int i_victim = 0;
    page_t victim;

    /* Figure out which page to evict. */
    // Evict based on minimum age
    for (int i = 1; i < loaded->num_loaded; i++)
    {
        if (ages[i] < ages[i_victim])
        {
            i_victim = i;
        }
    }
    victim = loaded->pages[i_victim];

    /* Shrink the collection of loaded pages now, by moving the last page in the
     * collection into the spot that the victim just occupied.
     */
    loaded->num_loaded--;
    loaded->pages[i_victim] = loaded->pages[loaded->num_loaded];
    // Also change the ages array appropriately
    ages[i_victim] = ages[loaded->num_loaded];

#if VERBOSE
    fprintf(stderr, "Choosing victim page %u to evict.\n", victim);
#endif

    return victim;
}
