#include <cstdio>
int main() {
    int a = 0x7fffffff;
    short b = (short)a;
    int c = 0xffffffff;
    short d = (short)c;
    int e = 0xffff7fff;
    short f = (short)e;
    printf("%d->%d, %d->%d, %d->%d\n", a,b,c,d,e,f);
    int x = 0x00007fab;
    unsigned char *point = (unsigned char *)&x;
    size_t len = sizeof(int)/sizeof(char);
    for (size_t i=0;i<len;i++) {
        printf("%p\t0x%.2x\n", point+i, *(point+i));
    }
    return 0;
}