#include <time.h>
#include "io.h"

#ifndef GENERATE_H
#define GENERATE_H

static inline char generate_capital(void);
static inline char generate_lowercase(void);
static inline char generate_number(void);

char * generate_fio(void);
struct Element * generate_element(void);
struct Element ** generate_array(int len);
#endif