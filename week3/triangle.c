/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Classify a triangle, given side lengths as strings:
// Not fully implemented yet
char *triangle(const char *length1, const char *length2, const char *length3) {
    return "Equilateral";
}

// Increment the test number and check that two strings are equal.
int eq(int n, const char *actual, const char *expected) {
    n++;
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "Test %d fails\n", n);
        fprintf(stderr, "result: %s\n", actual);
        fprintf(stderr, "instead of: %s\n", expected);
        exit(1);
    }
    return n;
}

// Run tests on the triangle function.
void test() {
    int n = 0;

    // Tests 1 to 2: check equilateral
    n = eq(n, triangle("8", "8", "8"), "Equilateral");
    n = eq(n, triangle("1073", "1073", "1073"), "Equilateral");

    // Tests 3 to 5: check isosceles
    n = eq(n, triangle("25", "25", "27"), "Isosceles");
    n = eq(n, triangle("25", "27", "25"), "Isosceles");
    n = eq(n, triangle("27", "25", "25"), "Isosceles");

    // Tests 6 to 14: check right angled
    n = eq(n, triangle("3", "4", "5"), "Right");
    n = eq(n, triangle("3", "5", "4"), "Right");
    n = eq(n, triangle("5", "3", "4"), "Right");
    n = eq(n, triangle("5", "12", "13"), "Right");
    n = eq(n, triangle("5", "13", "12"), "Right");
    n = eq(n, triangle("12", "5", "13"), "Right");
    n = eq(n, triangle("12", "13", "5"), "Right");
    n = eq(n, triangle("13", "5", "12"), "Right");
    n = eq(n, triangle("13", "12", "5"), "Right");

    // Tests 15 to 20: check scalene
    n = eq(n, triangle("12", "14", "15"), "Scalene");
    n = eq(n, triangle("12", "15", "14"), "Scalene");
    n = eq(n, triangle("14", "12", "15"), "Scalene");
    n = eq(n, triangle("14", "15", "12"), "Scalene");
    n = eq(n, triangle("15", "12", "14"), "Scalene");
    n = eq(n, triangle("15", "14", "12"), "Scalene");

    // Tests 21 to 25: check flat
    n = eq(n, triangle("7", "9", "16"), "Flat");
    n = eq(n, triangle("7", "16", "9"), "Flat");
    n = eq(n, triangle("9", "16", "7"), "Flat");
    n = eq(n, triangle("16", "7", "9"), "Flat");
    n = eq(n, triangle("16", "9", "7"), "Flat");

    // Tests 26 to 31: check impossible
    n = eq(n, triangle("2", "3", "13"), "Impossible");
    n = eq(n, triangle("2", "13", "3"), "Impossible");
    n = eq(n, triangle("3", "2", "13"), "Impossible");
    n = eq(n, triangle("3", "13", "2"), "Impossible");
    n = eq(n, triangle("13", "2", "3"), "Impossible");
    n = eq(n, triangle("13", "3", "2"), "Impossible");

    // Tests 32 to 42: check illegal
    n = eq(n, triangle("0", "0", "0"), "Illegal");
    n = eq(n, triangle("0", "10", "12"), "Illegal");
    n = eq(n, triangle("10", "12", "0"), "Illegal");
    n = eq(n, triangle("-1", "-1", "-1"), "Illegal");
    n = eq(n, triangle("-1", "10", "12"), "Illegal");
    n = eq(n, triangle("10", "-1", "12"), "Illegal");
    n = eq(n, triangle("10", "12", "-1"), "Illegal");
    n = eq(n, triangle("x", "y", "z"), "Illegal");
    n = eq(n, triangle("3", "4y", "5"), "Illegal");
    n = eq(n, triangle("10", "12", "13.4"), "Illegal");
    n = eq(n, triangle("03", "4", "5"), "Illegal");

    // Tests 43 to 47: check the upper limits on lengths
    n = eq(n, triangle("2147483647","2147483647","2147483647"),"Equilateral");
    n = eq(n, triangle("2147483648","2147483647","2147483647"),"Illegal");
    n = eq(n, triangle("2147483647","2147483648","2147483647"),"Illegal");
    n = eq(n, triangle("2147483647","2147483647","2147483648"),"Illegal");
    n = eq(n, triangle("2147483649","2147483649","2147483649"),"Illegal");

    // Tests 48 to 50: check for correct handling of overflow
    n = eq(n, triangle("1100000000","1705032704","1805032704"),"Scalene");
    n = eq(n, triangle("2000000001","2000000002","2000000003"),"Scalene");
    n = eq(n, triangle("150000002","666666671","683333338"),"Scalene");

    printf("Tests passed: %d\n", n);
}

// Run the program or, if there are no arguments, test it.
int main(int argc, char **argv) {
    if (argc == 1) {
        test();
    }
    else if (argc == 4) {
        char *result = triangle(argv[1], argv[2], argv[3]);
        printf("%s\n", result);
    }
    else {
        fprintf(stderr, "Use e.g.: ./triangle 3 4 5\n");
        exit(1);
    }
}
