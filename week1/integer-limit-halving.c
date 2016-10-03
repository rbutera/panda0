/* Find the limits of the int type */
#include <stdio.h>

int newLine(){
	printf("\n");
	return 0;
}

int doubleUntilLimit(){
	int max = 1;
	int lastValid = 0;

	while(max != 0 && max + 1 > max){
		printf("checking %d, doubled is %d, (m+1) = %d", max, (2 * max), max + 1);
		newLine();
		if (2 * max > max){
			printf("2*%d > %d, cont.", max, max);
			newLine();
			max = 2 * max;
		} else {
			printf("WOW: 2*%d < %d", max, max);
			newLine();

			// TODO: handle limit
			if(max + 1 > max){
				printf("can still go higher\n");
				while(max + 1 > max){
					lastValid = ++max;
					// printf("lastValid is now %d", lastValid);
					// newLine();
				}
			} else {
				// limit hit
				printf("we've hit the limit");
				lastValid = max;
			}
		}
	}

	printf("limit hit @ %d", lastValid);
	newLine();

	return lastValid;
}

int findMax(){
	int max = 0;

	while(max + 1 > max){
		printf("%d\n", max);
		max++;
	}

	return max;
}

int main() {
    setbuf(stdout, NULL);
    int n = doubleUntilLimit();
    printf("\n\nmax is %d\n", n);
    printf("c thinks the next largest number would be %d\n", n + 1);
    return 0;
}