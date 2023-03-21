#include "io.h"
#ifndef SORT_H
#define SORT_H

static inline int fioCmp(const void *, const void *);
static inline int psCmp(const void *, const void *);
static inline int ageCmp(const void *, const void *);
static inline int fioCmpReverse(const void *, const void *);
static inline int psCmpReverse(const void *, const void *);
static inline int ageCmpReverse(const void *, const void *);

int(*cmp(int, int)) (const void *, const  void *);

void swap(void *, void *);

void combSort(void *, size_t, size_t, int(*)(const void *, const void *));
void pairInsertionSort(void *, size_t, size_t, int(*)(const void *, const void *));

void(*choice_sort(int)) (void *, size_t, size_t, int(*) (const void *, const void *));
#endif