#include <stdio.h>
#include <stdlib.h>
#include "big_int.h"
#define LINE_FEED               "\x0a"
#define OK                      0
#define ERROR                   -1

static void print_usage()
{
    printf("Usage: calc_big_int [-?hasmd] integer integer" LINE_FEED
        "Options:" LINE_FEED
        "  -?,-h    : this help." LINE_FEED
        "  -a       : addition." LINE_FEED
        "  -s       : subtraction." LINE_FEED
        "  -m       : multiplication." LINE_FEED
        "  -d       : division." LINE_FEED);
}

int main(int argc, char *const argv[])
{
    if(argc != 4)
    {
        print_usage();
        exit(1);
    }
    char *p = argv[1];
    bi_div_t div_r;
    if(*p++ != '-'){
        fprintf(stderr, "invalid option: \"%s\"\n", argv[1]);
        return ERROR;
    }
    switch(*p++) {
    case '?':
    case 'h':
        print_usage();
        break;
    case 'a':
        printf("%s\n", bi_add(argv[2], argv[3]));
        break;
    case 's':
        printf("%s\n", bi_sub(argv[2], argv[3]));
        break;
    case 'm':
        printf("%s\n", bi_mul(argv[2], argv[3]));
        break;
    case 'd':
        div_r = bi_div(argv[2], argv[3]);
        printf("%s, %s\n", div_r.quot, div_r.rem);
        break;
    default:
        fprintf(stderr, "invalid option: \"%s\"\n", argv[1]);
        return ERROR;
    }
    return OK;
}
