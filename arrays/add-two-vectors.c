/* Adds two vectors together, demonstrating how to deal with returning arrays from functions */

/* For now, to design a function which adds two vectors,
you can pass a third argument to hold the result, which
works because of pass-by-reference */
#include <stdio.h>

#define VECTOR_DIMENSIONS 3

void add(int n, int a[n], int b[n], int result[n]) {
  for (int i = 0; i < n; i++) {
    result[i] = a[i] + b[i];
  }
}

int main (){
  int first[VECTOR_DIMENSIONS] = {1,2,3};
  int second[VECTOR_DIMENSIONS] = {2,4,6}; // expected sum would be {3,6,9};
  int result[VECTOR_DIMENSIONS];

  add(VECTOR_DIMENSIONS, first, second, result);

  if (result[0] == 3 && result[1] == 6 && result[2] == 9) {
    printf("added as expected yay 2");
    return 0;
  } else {
    printf("didn't work lol");
    return 1;
  }
}
