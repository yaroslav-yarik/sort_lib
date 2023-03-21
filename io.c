#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element
{
    char *fio;
    char psNum[7];
    int age;
};

static inline int
is_capital(char letter)
{
    return ('A' <= letter && letter <= 'Z');
}

static inline int
is_lowercase(char letter)
{
    return ('a' <= letter && letter <= 'z');
}

static inline int
is_number(char letter)
{
    return ('0' <= letter && letter <= '9');
}

int
fio_check(char *fio)
// correct if 3 word, first letter of every word is capital, other letters are lowercase
// return 0 - correct, 1 - incorrect
{
    int word_count = 0;
    int i = 0;
    while (fio[i] != '\0') {
        if (!is_capital(fio[i])) {
            return 1;
        }
        ++i;
        for(; fio[i] != '\0' && fio[i] != ' '; ++i) {
            if (!is_lowercase(fio[i])) {
                return 1;
            }
        }
        ++word_count;
        while (fio[i] == ' ') {
            i++;
        }
    }
    if (word_count != 3) {
        return 1;
    }
    return 0;
}

int
psNum_check(char *psNum)
// correct format: "XXX-YYY" where X - capital letter, Y - number
// return 0 - correct, 1 - incorrect
{
    if (strlen(psNum) != 7) {
        return 1;
    }
    for (int i = 0; i < 3; ++i) {
        if (!is_capital(psNum[i])) {
            return 1;
        }
    }
    if (psNum[3] != '-') {
        return 1;
    }
    for (int i = 4; i < 7; ++i) {
        if (!is_number(psNum[i])) {
            return 1;
        }
    }
    return 0;
}

int
age_check(int age)
// correct value: more or equal 18 and less or equal 100
// return 0 - correct, 1 - incorrect
{
    return (age < 18 || 100 < age);
}

char*
read_line(FILE *fin)
{
    int len = 101;
    char *res = calloc(len, sizeof(*res));
    int flag = 0;
    while ((flag = fscanf(fin, "%100[^\n]", res + len - 101)) == 1) {
        len += 100;
        res = realloc(res, len * sizeof(*res));
    }
    if (flag == -1) {
        free(res);
        return NULL;
    }
    res = realloc(res, (strlen(res) + 1) * sizeof(*res));
    fscanf(fin, "%*c");
    return res;
}

struct Element*
init_elem(FILE *fin, int *flag)
// flag: 0 - correct, 1 - EOF, 2 - incorrect data, 3 - invalid file format
{
    struct Element *elem = calloc(1, sizeof(*elem));
    if (!(elem->fio = read_line(fin))) {
        *flag = 1;
        free(elem);
        return NULL;
    } else if (!fscanf(fin, "%s", elem->psNum) || !fscanf(fin, "%d", &(elem->age))) {
        *flag = 3;
        free(elem->fio);
        free(elem);
        return NULL;
    }
    fscanf(fin, "%*c");
    if (fio_check(elem->fio) || psNum_check(elem->psNum) || age_check(elem->age)) {
        *flag = 2;
        free(elem->fio);
        free(elem);
        return NULL;
    }
    *flag = 0;
    return elem;
}
static inline void
free_elem(struct Element *elem)
{
    free(elem->fio);
    free(elem);
}

void
free_array(struct Element **array, int len)
{
    for(int i = 0; i < len; ++i) {
        free_elem(array[i]);
    }
    free(array);
}

struct Element**
init_array(char *inFile, int *len)
{
    FILE *fin = fopen(inFile, "r");
    *len = 0;
    int mem = 4;
    struct Element **array = calloc(mem, sizeof(*array));
    int elem_flag = 0;
    do {
        array[*len] = init_elem(fin, &elem_flag);
        switch (elem_flag) {
        case 0:
            (*len)++;
            break;
        case 1:
            break;
        case 2:
            fprintf(stderr, "incorrect data\n");
            break;
        case 3:
            fprintf(stderr, "invalid file format\n");
            free_array(array, *len);
            *len = 0;
            array = NULL;
            fclose(fin);
            exit(1);
        }
        if (*len >= mem) {
            mem *= 2;
            array  = realloc(array, mem * sizeof(*array));
        }
    } while (elem_flag != 1);
    array = realloc(array, (*len) * sizeof(*array));
    fclose(fin);
    return array;
}

void
write_elem(struct Element *elem, FILE *fout)
{
    char sep[] = " ";
    char *word = strtok(elem->fio, sep);
    while (word) {
        fprintf(fout, "%s ", word);
        word = strtok(NULL, sep);
    }
    fprintf(fout, "\n");
    fprintf(fout, "%s\n", elem->psNum);
    fprintf(fout, "%d\n", elem->age);
}

void
write_array(struct Element **array, int len, char *outFile)
{
    FILE *fout = fopen(outFile, "w");
    for(int i = 0; i < len; ++i) {
        write_elem(array[i], fout);
    }
    fclose(fout);
}
