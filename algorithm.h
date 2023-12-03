#ifndef ALGORITHM_H
#define ALGORITHM_H

size_t linear_search(void* base, size_t nmemb, size_t size, void* target,
                     int (*compar)(const void*, const void*));

size_t binary_search(void* base, size_t nmemb, size_t size, void* target,
                     int (*compar)(const void*, const void*));

size_t find_kmp(void* text, size_t n, void* pattern, size_t m, size_t size,
               int (*compar)(const void*, const void*));

# endif
