#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define MAX_HEAP 100

/* Private global varibles */
static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

/*
 * mem_init - Initialize the memory system model
 */
void mem_init(void)
{
    mem_heap = (char *)malloc(MAX_HEAP);
    mem_brk = (char *)mem_heap;
    mem_max_addr = (char *)(mem_heap + MAX_HEAP);
}

/*
 * mem_sbrk = Simple model of the sbrk function. Extends
 * the heap by incr bytes and returns the start address
 * of the new area. In this model, the heap cannot
 * shrunk.
 */
void *mem_sbrk(int incr)
{
    char *old_brk = mem_brk;

    if ( (incr < 0) || ((mem_brk + incr) > mem_max_addr) ) {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed. \
                Ran out of memory...\n");
        return (void *)-1;
    }
    mem_brk += incr;
    return (void *)old_brk;
}
