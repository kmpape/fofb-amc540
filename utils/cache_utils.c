#include <stdint.h>
#include <ti/csl/csl_cacheAux.h>

void cache_invalidate (void *ptr, int size)
{
    uint32_t key;
    /* Disable Interrupts */
    key = _disable_interrupts();

    /*  Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

    CACHE_invL1d (ptr, size, CACHE_FENCE_WAIT);
    //CACHE_invL2  (ptr, size, CACHE_FENCE_WAIT);

    /* Reenable Interrupts. */
    _restore_interrupts(key);
}

void cache_writeback (void *ptr, int size)
{
    uint32_t key;
    /* Disable Interrupts */
    key = _disable_interrupts();

    CACHE_wbL1d (ptr, size, CACHE_FENCE_WAIT);
    //CACHE_wbL2  (ptr, size, CACHE_FENCE_WAIT);

    /* Reenable Interrupts. */
    _restore_interrupts(key);
}
