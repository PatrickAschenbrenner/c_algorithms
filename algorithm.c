#include <stdlib.h>

size_t linear_search(void* base, size_t nmemb, size_t size, void* target,
                     int (*compar)(const void*, const void*)) {
    int cmp;
    for (size_t i = 0; i < nmemb; i++) {
        cmp = compar((char*)base + i*size, target);
        if (cmp == 0) return i;
    }
    return -1;
}

size_t binary_search(void* base, size_t nmemb, size_t size, void* target,
                     int (*compar)(const void*, const void*)) {
    size_t left = 0;
    size_t right = nmemb - 1;
    size_t mid;
    int cmp;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        cmp = compar((char*)base + mid*size, target);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void compute_fail_kmp(void* pattern, size_t m, size_t* fail, size_t size,
                    int (*compar)(const void*, const void*)) {
    size_t j = 1, k = 0;
    while (j < m) {
        if (compar((char*)pattern + j*size, (char*)pattern + k*size) == 0) {
            fail[j] = k + 1;
            j++;
            k++;
        } else if (k > 0) {
            k = fail[k - 1];
        } else {
            j++;
        }
    }
}

size_t find_kmp(void* text, size_t n, void* pattern, size_t m, size_t size,
               int (*compar)(const void*, const void*)) {
    if (m == 0) return 0;
    size_t* f = calloc(m, sizeof(size_t));
    compute_fail_kmp(pattern, m, f, size, compar);
    size_t j=0, k=0;
    while (j < n) {
        if (compar((char*)text + j*size, (char*)pattern + k*size) == 0) {
            if (k == m - 1) {
                free(f);
                return j - k;
            }
            j++;
            k++;
        } else if (k > 0) {
            k = f[k - 1];
        } else {
            j++;
        }
    }
    free(f);
    return -1;
}
