/* Calculate a grade from a mark. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Checks if a string contains exclusively numeric values
bool containsNumbers (const char *mark){
    printf("\nchecking if %s contains non-numeric values\n", mark);

    bool result;
    int length = (int)strlen(mark);
    int i;
    printf("\n");
    for(i = 0; i < length; i++)
    {
        printf("i = %i, *mark = %i, mark[i] = %i, mark = %s \n",i, *mark, mark[i], mark);
        char testing = mark[i];

        if(!isdigit(testing))
        {
            result = false;
        }
        else
        {
            result = true;
        }
    }

    return result;
    printf("\n\n");
}

// Check whether a mark is properly formatted.
bool valid(const char *mark) {

    int converted = atoi(mark);
    bool withinBoundaries = converted >= 0 && converted <= 100;

    if (containsNumbers(mark) && withinBoundaries){
        printf("contains numbers?: %d, within boundaries?:%d \n", containsNumbers(mark), withinBoundaries);
        return true;
    } else {
        printf("contains numbers?: %d, within boundaries?:%d \n", containsNumbers(mark), withinBoundaries);
        return false;
    }
}

// Convert the mark into a grade
char *grade(const char *mark) {
    // TODO: convert mark -> grade

    // check if valid
    if (valid(mark)){
        int converted = atoi(mark);
        // fail
        if(converted < 40){
            return "Fail";
        } else if(converted < 50){
            return "3";
        } else if(converted < 60){
            return "2.2";
        } else if(converted < 70){
            return "2.1";
        } else {
            return "1";
        }
    } else { // error
        return "Error: invalid mark";
    }
}

// Increment and return the test number and check that two strings are equal.
int eq(int n, const char *grade, const char *expected) {
    n++;
    if (strcmp(grade, expected) != 0) {
        fprintf(stderr, "Test %d fails:\n", n);
        fprintf(stderr, "result %s instead of %s\n", grade, expected);
        exit(1);
    }
    return n;
}

// Run the tests.
void test() {
    int n = 0;
    n = eq(n, grade("0"), "Fail");
    n = eq(n, grade("39"), "Fail");
    n = eq(n, grade("40"), "3");
    n = eq(n, grade("49"), "3");
    n = eq(n, grade("50"), "2.2");
    n = eq(n, grade("59"), "2.2");
    n = eq(n, grade("60"), "2.1");
    n = eq(n, grade("69"), "2.1");
    n = eq(n, grade("70"), "1");
    n = eq(n, grade("100"), "1");
    n = eq(n, grade("40.5"), "Error: invalid mark");
    n = eq(n, grade("x"), "Error: invalid mark");
    n = eq(n, grade("-1"), "Error: invalid mark");
    n = eq(n, grade("101"), "Error: invalid mark");
    n = eq(n, grade("01"), "Error: invalid mark");
    printf("Tests passed: %d\n", n);
}

// Deal with input and output, and call either test or grade.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2) printf("%s\n", grade(args[1]));
    else {
        fprintf(stderr, "Use:   ./grade   or   ./grade m\n");
        fprintf(stderr, "where m is an integer mark from 0 to 100\n");
        exit(1);
    }
    return 0;
}
