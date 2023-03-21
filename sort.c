#include "io.h"

static inline int
fioCmp(const void *fir, const void *sec)
{
    return strcmp((*(struct Element**)fir)->fio, (*(struct Element**)sec)->fio);
}

static inline int
psCmp(const void *fir, const void *sec)
{
    return strcmp((*(struct Element**)fir)->psNum, (*(struct Element**)sec)->psNum);
}

static inline int
ageCmp(const void *fir, const void *sec)
{
    return (*(struct Element**)fir)->age - (*(struct Element**)sec)->age;
}

static inline int
fioCmpReverse(const void *fir, const void *sec)
{
    return -1 * strcmp((*(struct Element**)fir)->fio, (*(struct Element**)sec)->fio);
}

static inline int
psCmpReverse(const void *fir, const void *sec)
{
    return -1 * strcmp((*(struct Element**)fir)->psNum, (*(struct Element**)sec)->psNum);
}

static inline int
ageCmpReverse(const void *fir, const void *sec)
{
    return -1 * ((*(struct Element**)fir)->age - (*(struct Element**)sec)->age);
}

int(*cmp(int field, int direction))
(const void *, const  void *)
{
    int (*funcs[6])(const void *, const  void *) = {
        fioCmp,
        fioCmpReverse,
        psCmp,
        psCmpReverse,
        ageCmp,
        ageCmpReverse,
    };
    return funcs[field * 2 + direction];
}

void
swap(void *fir, void *sec, size_t size)
{
    char *first = fir;
    char *second = sec;
    do {
        char tmp = *first;
        *first++ = *second;
        *second++ = tmp;
    } while (--size);
}

void
combSort(void *array, size_t count, size_t size, int(*cmp)(const void *, const void *))
{
    double factor = 1.2473304;
    int step = count - 1;
    while (step >= 1) {
        for(int i = 0; i + step < count; i++) {
            if (cmp(array + i * size, array + (i + step) * size) > 0) {
                swap(array + i * size, array + (i + step) * size, size);
            }
        }
        step /= factor;
    }
}

void
pairInsertionSort(void *array, size_t count, size_t size, int(*cmp)(const void *, const void *))
{
    char *key1 = calloc(size, sizeof(*key1));
    char *key2 = calloc(size, sizeof(*key2));
    for (int i = 0; i < count / 2 * 2; i += 2) {
        swap(key1, array + i * size, size);
        swap(key2, array + (i + 1) * size, size);
        if (cmp(key1, key2) < 0) {
            swap(key1, key2, size);
        }
        int j = i - 1;
        while (j >= 0 && cmp(array + j * size, key1) > 0) {
            swap(array + (j + 2) * size, array + j * size, size);
            --j;
        }
        swap(array + (j + 2) * size, key1, size);
        while (j >= 0 && cmp(array + j * size, key2) > 0) {
            swap(array + (j + 1) * size, array + j * size, size);
            --j;
        }
        swap(array + (j + 1) * size, key2, size);
    }
    if (count % 2) {
        swap(key1, array + (count - 1) * size, size);
        int i = count - 2;
        while (i >= 0 && cmp(array + i * size, key1) > 0) {
            swap(array + (i + 1) * size, array + i * size, size);
            --i;
        }
        swap(array + (i + 1) * size, key1, size);
    }
    free(key1);
    free(key2);
}

void(*choice_sort(int algo_num))
(void *, size_t, size_t, int(*) (const void *, const void *))
{
    void (*funcs[3])(void *, size_t,  size_t,  int (*)(const void *, const void *)) = {
        combSort,
        pairInsertionSort,
        qsort,
    };
    return funcs[algo_num];
}