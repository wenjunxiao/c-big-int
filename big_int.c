#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "big_int.h"

char g_r[MAX_BI_LEN];
char g_rem[MAX_BI_LEN];

void c_to_d(const char cx[], char dx[], int len);
void d_to_c(const char dx[], char cx[], int len);
void print_d(const char *msg, const char *x, int len);
char factor(char **p);
void swap_i(int *a, int *b);
void swap_p(char **a, char **b);
void _bi_add(char f, const char *x, const char *y, char r[], int lr);
void _bi_sub(const char *x, const char *y, char r[], int lr);
int _bi_sub0(char f, char *dx, char *dy, char r[], int lx, int ly, int lr);

void c_to_d(const char cx[], char dx[], int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        if(cx[i] >= '0' && cx[i] <= '9')
        {
            dx[i] = cx[i] - '0';
        } 
        else
        {
            dx[i] = cx[i];
        }
    }
    dx[len] = '\0';
}

void d_to_c(const char dx[], char cx[], int len)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        if(dx[i] >= 0 && dx[i] <= 9)
        {
            cx[i] = dx[i] + '0';
        }
        else
        {
            cx[i] = dx[i];
        }
    }
    cx[len] = '\0';
}

void print_d(const char *msg, const char *x, int len)
{
    int i;
    printf("%s", msg);
    for (i = 0; i < len; ++i)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
}

char factor(char **p)
{
    switch(**p){
    case '-':
    case '+':
        return *(*p)++;
    default:
        return '\0';
    }
}

int bi_compare(const char x[], const char y[])
{
    return bi_compare1(x, y, strlen(x), strlen(y));
}

int bi_compare1(const char *x, const char *y, int lx, int ly)
{
    char *px = (char *)x;
    char *py = (char *)y;
    char fx = factor(&px);
    char fy = factor(&py);
    lx = lx - (px - x);
    ly = ly - (py - y);
    if(fx != fy){
        if(fx == 0) return 2;
        else return -2;
    } else if(lx < ly) return -3;
    else if(lx > ly) return 3;
    else return strncmp(px, py, lx);
}

char *bi_add(const char x[], const char y[])
{
    bi_add1(x, y, g_r, MAX_BI_LEN);
    return g_r;
}

void bi_add1(const char x[], const char y[], char r[], int lr)
{
    char *px = (char *)x;
    char *py = (char *)y;
    char fx = factor(&px);
    char fy = factor(&py);

    if(fx != fy){
        if(fx == 0){
            _bi_sub(px, py, r, lr);
        } else {
            _bi_sub(py, px, r, lr);
        }
    } else {
        _bi_add(fx, px, py, r, lr);
    }
}

void swap_i(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void swap_p(char **a, char **b)
{
    char *t = *a;
    *a = *b;
    *b = t;
}

void _bi_add(char f, const char *x, const char *y, char r[], int lr)
{
    int lx = strlen(x);
    int ly = strlen(y);
    char dx[MAX_BI_LEN], dy[MAX_BI_LEN];
    if(lx < ly){
        c_to_d(y, dx, ly);
        c_to_d(x, dy, lx);
        swap_i(&lx, &ly);
    } else {
        c_to_d(x, dx, lx);
        c_to_d(y, dy, ly);
    }
    memset(r, 0, lr);
    --lr;

    int i = lr, t;
    while(i-- > 0 && lx-- > 0){
        if(ly > 0){
            t = dx[lx] + dy[--ly] + r[i];
        } else {
            t = dx[lx] + r[i];
        }
        if(t > 9){
            r[i - 1] = t / 10;
            t = t % 10;
        } 
        r[i] = t;
    }
    while(i < lr - 1 && r[i] == 0) ++i;
    if(f > 0) r[--i] = f;
    d_to_c(&r[i], r, lr - i);
}

void _bi_sub(const char *x, const char *y, char r[], int lr)
{
    int lx = strlen(x);
    int ly = strlen(y);
    char f = '\0';
    char dx[MAX_BI_LEN], dy[MAX_BI_LEN];
    if(lx < ly || (lx == ly && strcmp(x, y) < 0) ){
        c_to_d(y, dx, ly);
        c_to_d(x, dy, lx);
        swap_i(&lx, &ly);
        f = '-';
    } else {
        c_to_d(x, dx, lx);
        c_to_d(y, dy, ly);
    }
    lr = _bi_sub0(f, dx, dy, r, lx, ly, lr);
    d_to_c(r, r, lr);
}

int _bi_sub0(char f, char *dx, char *dy, char r[], int lx, int ly, int lr)
{
    memset(r, 0, lr);
    --lr;
    
    int i = lr, t;
    while(i-- > 0 && lx-- > 0){
        if(ly > 0){
            --ly;
            t = dx[lx] - dy[ly] - r[i];
        } else {
            t = dx[lx] - r[i];
        }
        if(t < 0){
            r[i - 1] += 1;
            t = t + 10;
        }
        r[i] = t;
    }
    while(i < lr - 1 && r[i] == 0) ++i;
    if(f > 0) r[--i] = f;
    if(i > 0){
        memcpy(r, &r[i], lr - i + 1);
    }
    return lr - i;
}

char *bi_sub(const char x[], const char y[])
{
    bi_sub1(x, y, g_r, MAX_BI_LEN);
    return g_r;
}

void bi_sub1(const char x[], const char y[], char r[], int lr)
{
    char *px = (char *)x;
    char *py = (char *)y;
    char fx = factor(&px);
    char fy = factor(&py);

    if(fx != fy){
        _bi_add(fx, px, py, r, lr);
    } else if(fx == '-'){
        _bi_sub(py, px, r, lr);
    } else {
        _bi_sub(px, py, r, lr);
    }
}

char *bi_mul(const char x[], const char y[])
{
    bi_mul1(x, y, g_r, MAX_BI_LEN);
    return g_r;
}

void bi_mul1(const char x[], const char y[], char r[], int lr)
{
    char *px = (char *)x;
    char *py = (char *)y;
    char fx = factor(&px);
    char fy = factor(&py);
    int lx = strlen(px);
    int ly = strlen(py);
    char dx[MAX_BI_LEN], dy[MAX_BI_LEN];
    c_to_d(px, dx, lx);
    c_to_d(py, dy, ly);
    memset(r, 0, lr);

    int ix, iy, ir, sr, t;
    ir = sr = lr - 1;
    for (iy = ly - 1, sr = lr - 1; iy >= 0; --iy, --sr)
    {
        for (ix = lx - 1, ir = sr; ix >= 0; --ix, --ir)
        {
            t = dx[ix] * dy[iy] + r[ir];
            if(t > 9){
                r[ir - 1] += t / 10;
                t = t % 10;
            }
            r[ir] = t;
        }
    }
    while(ir < lr - 1 && r[ir] == 0) ++ir;
    if(fx != fy && r[ir] != 0){
        r[--ir] = '-';
    }
    d_to_c(&r[ir], r, lr - ir);
}

bi_div_t bi_div(const char x[], const char y[])
{
    bi_div1(x, y, g_r, MAX_BI_LEN);
    bi_div_t t;
    t.quot = g_r;
    t.rem = g_rem;
    return t;
}

void bi_div1(const char x[], const char y[], char r[], int lr)
{
    bi_div2(x, y, r, lr, g_rem, MAX_BI_LEN);
}

void bi_div2(const char x[], const char y[], char r[], int lr, char rem[], int lrem)
{
    char *px = (char *)x;
    char *py = (char *)y;
    char fx = factor(&px);
    char fy = factor(&py);
    int lx = strlen(px);
    int ly = strlen(py);
    char dx[MAX_BI_LEN], dy[MAX_BI_LEN], dswap[MAX_BI_LEN];
    c_to_d(px, dx, lx);
    c_to_d(py, dy, ly);
    memset(r, 0, lr);
    memset(rem, 0, lrem);
    memset(dswap, 0, MAX_BI_LEN);
    if(dy[0] == 0) r[0] = 1 / dy[0]; /* trigger the divisor is zero. */
    
    char *prem = rem, *pswap = dswap;
    int ix = 0, ir = 0, irmd = 0, lswap = MIN(lrem, MAX_BI_LEN);
    int valid = 0;
    if(fx != fy){
        r[ir++] = '-';
    }
    while(ix < lx){
        while(ix < lx && bi_compare1(prem, dy, irmd, ly) < 0){
            if(prem[0] == 0) irmd = 0;
            prem[irmd++] = dx[ix++];
            if(valid) ++ir;
        }
        while(bi_compare1(prem, dy, irmd, ly) >= 0){
            r[ir] += 1;
            irmd = _bi_sub0(0, prem, dy, pswap, irmd, ly, lswap);
            swap_p(&prem, &pswap);
            valid = 1;
        }
    }
    ++ir;
    if(prem != rem){
        memcpy(rem, dswap, irmd + 1);
    }
    d_to_c(r, r, ir);
    d_to_c(g_rem, g_rem, irmd);
}
