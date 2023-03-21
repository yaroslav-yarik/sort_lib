#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/time.h>

#include  "io.h"
#include "generate.h"
#include "sort.h"

int
main(int argc, char *argv[])
{

    srand(time(NULL));
    if (argc != 9) {
        fprintf(stderr, "wrong number of arguments\n");
        exit(2);
    }
    int element_count = strtol(argv[1], NULL, 10);
    int array_count = strtol(argv[2], NULL, 10);
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
    
    struct timeval start, end;
    int len = element_count;
    
    FILE *out = fopen("timing.out", "w");
    
    for(int i = 0; i < array_count; ++i) {
        struct Element **array = generate_array(len);
        char test_file[] = "test3";
        write_array(array, len, test_file);
        gettimeofday(&start, NULL);
        sort(array, len, sizeof(*array), compare);
        gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
        fprintf(out, "%ld\n", micros);
        free_array(array, len);
    }
    fclose(out);
    return 0;
}
