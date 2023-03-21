#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef IO_H
#define IO_H
struct Element
{
    char *fio;
    char psNum[7];
    int age;
};


static inline int is_capital(char letter);
static inline int is_lowercase(char letter);
static inline int is_number(char letter);


int fio_check(char *fio);
int psNum_check(char *psNum);
int age_check(int age);

static inline void free_elem(struct Element *elem);
void free_array(struct Element **array, int len);


struct Element* init_elem(FILE *fin, int *flag);
struct Element** init_array(char *inFile, int *len);


void write_elem(struct Element *elem, FILE *fout);
void write_array(struct Element **array, int len, char *outFile);
#endif