#ifndef CACHE_UTILS_H_
#define CACHE_UTILS_H_

void cache_invalidate (void *ptr, int size);

void cache_writeback (void *ptr, int size);

#endif /* CACHE_UTILS_H_ */
