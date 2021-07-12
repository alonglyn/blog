#include <cstdio>
int main() {
    int a = 0x7fffffff;
    short b = (short)a;
    int c = 0xffffffff;
    short d = (short)c;
    int e = 0xffff7fff;
    short f = (short)e;
    printf("%d->%d, %d->%d, %d->%d", a,b,c,d,e,f);
    return 0;
}