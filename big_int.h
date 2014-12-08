#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#ifndef MAX_BI_LEN
#define MAX_BI_LEN              2048
#endif

#define MIN(x, y)               (x > y ? y : x)
#define MAX(x, y)               (x > y ? x : y)

/* Returned by `bi_div`. */
typedef struct 
{
    char *quot;     /* Quotient */
    char *rem;      /* Remainder */
} bi_div_t;

/* Big int comparison. */
int bi_compare(const char x[], const char y[]);
int bi_compare1(const char x[], const char y[], int lx, int ly);

/* Big int addition. */
char *bi_add(const char x[], const char y[]);
void bi_add1(const char x[], const char y[], char r[], int lr);

/* Big int subtraction. */
char *bi_sub(const char x[], const char y[]);
void bi_sub1(const char x[], const char y[], char r[], int lr);

/* Big int multiplication. */
char *bi_mul(const char x[], const char y[]);
void bi_mul1(const char x[], const char y[], char r[], int lr);

/* Big int division. */
bi_div_t bi_div(const char x[], const char y[]);
void bi_div1(const char x[], const char y[], char r[], int lr);
void bi_div2(const char x[], const char y[], char r[], int lr, char rem[], int lrem);

#endif