#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "io.h"
#include "sort.h"


int
main(int argc, char *argv[])
{
    if (argc != 9) {
        fprintf(stderr, "wrong number of arguments\n");
        exit(2);
    }
    char *in_file = argv[1];
    char *out_file = argv[2];
    int algo_num = -1; // 0 - combSort, 1 - pairInsertionSort, 2 - qsort
    int field = -1; // 0 - fio, 1 - psNum, 2 - age
    int direction = -1; // 0 - increasing, 1 - decreasing
    
    char opts[] = "a:f:d:"; // a - algo, f - field, d - direction
    int opt;
    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
        case 'a':
            algo_num = strtol(optarg, NULL, 10);
            break;
        case 'f':
            field = strtol(optarg, NULL, 10);
            break;
        case 'd':
            direction = strtol(optarg, NULL, 10);
            break;
        default:
            fprintf(stderr, "wrong option\n");
            exit(3);
        }
    }
    if (algo_num < 0 || 2 < algo_num || field < 0 || 2 < field || direction < 0 || 1 < direction) {
        fprintf(stderr, "wrong arguments of option\n");
        exit(4);
    }
    int(*compare)(const void *, const void *) = cmp(field, direction);
    void (*sort)(void *, size_t, size_t, int(*) (const void *, const void *)) = choice_sort(algo_num);
    
    int len = 0;
    struct Element **array = init_array(in_file, &len);
    sort(array, len, sizeof(*array), compare);
    write_array(array, len, out_file);
    free_array(array, len);
    return 0;
}
