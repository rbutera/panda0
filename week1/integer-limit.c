/* Find the limits of the int type */
#include <stdio.h>

int main() {
    setbuf(stdout, NULL);
    int n = 42;
    printf("%d\n", n);
    return 0;
}