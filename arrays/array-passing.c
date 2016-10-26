// DEMONSTRATES THAT ARRAYS ARE PASSED BY REFERENCE
#include <stdio.h>

// Initialise elements of array
void init(int n, int items[n], int v, int x, int y) {
    items[0] = v;
    items[1] = x;
    items[2] = y;
}

void trythis(int n, int numbers[n], int x, int y, int z) {
  init(n, numbers, x, y, z);
  printf("n0 = %d\n", numbers[0]);
  printf("n1 = %d\n", numbers[1]);
  printf("n2 = %d\n", numbers[2]);
}

int main() {
    setbuf(stdout, NULL);
    int numbers[3] = { 0, 0, 0 };
    trythis(3, numbers, 1,2,3);
    trythis(3, numbers, 3,2,1);
    trythis(3, numbers, 4,2,0);
}
