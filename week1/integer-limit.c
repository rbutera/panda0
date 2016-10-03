/* Find the limits of the int type */
#include <stdio.h>

int findMax(){
	int max = 0;

	while(max + 1 > max){
		// printf("%d\n", max);
		max++;
	}

	return max;
}

int main() {
    setbuf(stdout, NULL);
    int n = findMax();
    printf("\n\nmax is %d\n", n);
    printf("c thinks the next largest number would be %d\n", n + 1);
    return 0;
}