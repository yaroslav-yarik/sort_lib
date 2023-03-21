#include <time.h>
#include "io.h"

static inline char
generate_capital(void)
{
    return 'A' + rand() % ('Z' - 'A' + 1);
}

static inline char
generate_lowercase(void)
{
    return 'a' + rand() % ('z' - 'a' + 1);
}

static inline char
generate_number(void)
{
    return '0' + rand() % ('9' - '0' + 1);
}

char *
generate_fio(void)
{
    size_t name_len = 1 + rand() % 20;
    size_t surname_len = 1 + rand() % 20; 
    size_t patronymic_len = 1 + rand() % 20;
    
    char *fio = calloc(name_len + surname_len + patronymic_len + 3, sizeof(*fio));
    int index = 0;
    fio[index++] = generate_capital();
    for(int i = 1; i < name_len; ++i) {
        fio[index++] = generate_lowercase();
    }
    fio[index++] = ' ';
    fio[index++] = generate_capital();
    for(int i = 1; i < surname_len; ++i) {
        fio[index++] = generate_lowercase();
    }
    fio[index++] = ' ';
    fio[index++] = generate_capital();
    for(int i = 1; i < patronymic_len; ++i) {
        fio[index++] = generate_lowercase();
    }
    return fio;
}

struct Element *
generate_element(void)
{
    struct Element *elem = calloc(1, sizeof(*elem));
    elem->fio = generate_fio();
    for(int i = 0; i < 3; ++i) {
        elem->psNum[i] = generate_capital();
    }
    elem->psNum[3] = '-';
    for(int i = 4; i < 7; ++i) {
        elem->psNum[i] = generate_number();
    }
    elem->age = 18 + rand() % (100 - 18 + 1);
    return elem;
}

struct Element **
generate_array(int len)
{
    struct Element **array = calloc(len, sizeof(*array));
    for(int i = 0; i < len; ++i) {
        array[i] = generate_element();
    }
    return array;
}