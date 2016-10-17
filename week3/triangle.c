/* triangle.c
 Classify a triangle according to the integer lengths of its sides.
 by Raimondo Butera (Uni. Bristol CompSci & Innovation 2020)
 Copyright 2016 Rai Butera. All rights reserved. Don't plagiarize etc.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool validLength (const char *length){
    _Bool isValid = 1;

    // check for leading 0 (test 42)
    if(*length == '0'){
        isValid = 0;
    }

    // traverse over string checking for non-numeric characters
    while(*length != '\0'){
        if (*length >= '0' && *length <= '9')
        {
            // printf("VALID: %c\n", *length);
            isValid = isValid && 1;
        } else {
            // printf("INVALID: %c\n", *length);
            isValid = 0;
        }
        // keep traversing over the string
        length++;
    }

    // if (isValid)
    // {
    //     printf("\nvalidation passed\n");
    // } else {
    //     printf("\nvalidation FAIL\n");
    // }

    return isValid;
}

/**
* validates a length value and converts into an integer for comparison
 * @param  const char *length   a length value in string form to parse
 * @return  int converted (1 to INT_MAX) if successful, -1 if error
 */
int parseLength (const char *length){
    int result;
    /** FOR DEBUGGING
        printf("parsing %s \n", length);
    */

    if(validLength(length)){
        // convert to integer
        result = atoi(length);

        // atoi returns undefined if outside range of valid integers or 0 if unable to convert
        if (!result) {
            result = -1;
        }
    } else {
        result = -1;
    }

    return result;
}

/**
 * returns 1 if three given dimensions are equal
 */
_Bool triangleHasAllSidesEqual (int x, int y, int z){
    return (long) x == (long) y && (long) x == (long) z;
}

/**
 * returns 1 if two sides are equal, 0 if all sides are equal or no sides are equal
 */
_Bool triangleHasOnlyTwoSidesEqual (int x, int y, int z){
    long a = (long) x;
    long b = (long) y;
    long c = (long) z;

    return (a == b && a != c) || (a == c && a != b) || (b == c && b != a);
}

// returns 1 if all sides are of different size
_Bool triangleHasNoEqualSides (int x, int y, int z){
    long a = (long) x;
    long b = (long) y;
    long c = (long) z;

    return a != b && b != c && a != c;
}

// squares two numbers (overkill?)
long squared (int x){
    return x * x;
}

/**
 * checks if three sides satisfy pythagoras' theorem
 * NB: lazily expects arguments sorted by size order, ascending
 * @return  1 if pythagorean, 0 if not
 */
_Bool checkPythagorean (int x, int y, int z){
    long a = (long) x;
    long b = (long) y;
    long c = (long) z;

    return squared(a) + squared(b) == squared(c);
}

/**
 * determines if 3 given dimensions represent a right-angled triangle
 * NB: uses checkPythagorean above
 * @return  1 if right angle, 0 if not
 */
_Bool triangleHasRightAngle (int x, int y, int z){
    int toSort[3] = {x,y,z};

    // printf("\n\nSORTING [%i,%i,%i]\n=================\n", toSort[0], toSort[1], toSort[2]);

    // sort array by size, largest member last (using bubble sort because idk if we've learned other sort algorithms yet in the course)
    for (int i = 0; i < 3; ++i)
    {
        long a = (long) toSort[i - 1];
        long b = (long) toSort[i];

        if(a > b){
            int small = toSort[i];
            int big = toSort[i - 1];

            toSort[i - 1] = small;
            toSort[i] = big;

            // printf("swapped positions %i and %i, now [%i,%i,%i] \n", i - 1, i, toSort[0], toSort[1], toSort[2]);
        } /**
        else {
            // printf("no need to swap, %i < %i, now [%i,%i,%i] \n", toSort[i -1], toSort[i], toSort[0], toSort[1], toSort[2]);
        } **/
    }

    // printf("\n======\n SORTED TO [%i,%i,%i]\n=================\n", toSort[0], toSort[1], toSort[2]);

    // array is sorted, check if there is a pythagorean triangle
    return checkPythagorean(toSort[0], toSort[1], toSort[2]);
}

/**
 * checks if a triangle matches a 'flat' triangle (the sum of two sides' lengths equals the third side's length)
 * @return 1 if a triangle has area, 0 if a triangle doesn't
 */
_Bool triangleHasArea (int x, int y, int z){
    long a = (long) x;
    long b = (long) y;
    long c = (long) z;

    return !(a + b == c || a + c == b || b + c == a);
}

/**
 * checks if a triangle is impossible because one of the sides is longer than the other two sides combined
 */
_Bool triangleIsPossible (int x, int y, int z){
    long a = (long) x;
    long b = (long) y;
    long c = (long) z;

    return (a < b + c) && (b < a + c) && (c < a + b);
}

// Classify a triangle, given side lengths as strings:
char *triangle(const char *length1, const char *length2, const char *length3) {
    char *result;

    int dimensions[3] = {parseLength(length1), parseLength(length2), parseLength(length3)};

    // check for errors
    if(dimensions[0] > 0 && dimensions[1] > 0 && dimensions[2] > 0){

        /** FOR DEBUGGING
        printf("dimensions are: ");

        for (int i = 0; i < 3; ++i)
        {
            printf("%i ", dimensions[i]);
        }

        printf("\n");
        */

        result = "valid triangle";

        int x, y, z;
        x = dimensions[0];
        y = dimensions[1];
        z = dimensions[2];

        if(triangleHasAllSidesEqual(x,y,z)){
            result = "Equilateral";
        } else if (triangleHasOnlyTwoSidesEqual(x,y,z)) {
            result = "Isosceles";
        } else if (triangleHasNoEqualSides(x,y,z)) {

            if(triangleHasRightAngle(x,y,z)){
                result = "Right";
            } else if (triangleHasArea(x,y,z)){

                if (triangleIsPossible(x,y,z)){
                    result = "Scalene";
                } else {
                    result = "Impossible";
                }

            } else {
                result = "Flat";
            }

        } else {
            result = "wtf????";
        }

    } else {
        result = "Illegal";
    }


    return result;
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
    n = eq(n, triangle("8", "8", "8"), "Equilateral"); // Test 1
    n = eq(n, triangle("1073", "1073", "1073"), "Equilateral"); // Test 2

    // Tests 3 to 5: check isosceles
    n = eq(n, triangle("25", "25", "27"), "Isosceles"); // Test 3
    n = eq(n, triangle("25", "27", "25"), "Isosceles"); // Test 4
    n = eq(n, triangle("27", "25", "25"), "Isosceles"); // Test 5

    // Tests 6 to 14: check right angled
    n = eq(n, triangle("3", "4", "5"), "Right"); // Test 6
    n = eq(n, triangle("3", "5", "4"), "Right"); // Test 7
    n = eq(n, triangle("5", "3", "4"), "Right"); // Test 8
    n = eq(n, triangle("5", "12", "13"), "Right"); // Test 9
    n = eq(n, triangle("5", "13", "12"), "Right"); // Test 10
    n = eq(n, triangle("12", "5", "13"), "Right"); // Test 11
    n = eq(n, triangle("12", "13", "5"), "Right"); // Test 12
    n = eq(n, triangle("13", "5", "12"), "Right"); // Test 13
    n = eq(n, triangle("13", "12", "5"), "Right"); // Test 14

    // Tests 15 to 20: check scalene
    n = eq(n, triangle("12", "14", "15"), "Scalene"); // Test 15
    n = eq(n, triangle("12", "15", "14"), "Scalene"); // Test 16
    n = eq(n, triangle("14", "12", "15"), "Scalene"); // Test 17
    n = eq(n, triangle("14", "15", "12"), "Scalene"); // Test 18
    n = eq(n, triangle("15", "12", "14"), "Scalene"); // Test 19
    n = eq(n, triangle("15", "14", "12"), "Scalene"); // Test 20

    // Tests 21 to 25: check flat
    n = eq(n, triangle("7", "9", "16"), "Flat"); // Test 21
    n = eq(n, triangle("7", "16", "9"), "Flat"); // Test 22
    n = eq(n, triangle("9", "16", "7"), "Flat"); // Test 23
    n = eq(n, triangle("16", "7", "9"), "Flat"); // Test 24
    n = eq(n, triangle("16", "9", "7"), "Flat"); // Test 25

    // Tests 26 to 31: check impossible
    n = eq(n, triangle("2", "3", "13"), "Impossible"); // Test 26
    n = eq(n, triangle("2", "13", "3"), "Impossible"); // Test 27
    n = eq(n, triangle("3", "2", "13"), "Impossible"); // Test 28
    n = eq(n, triangle("3", "13", "2"), "Impossible"); // Test 29
    n = eq(n, triangle("13", "2", "3"), "Impossible"); // Test 30
    n = eq(n, triangle("13", "3", "2"), "Impossible"); // Test 31

    // Tests 32 to 42: check illegal
    n = eq(n, triangle("0", "0", "0"), "Illegal"); // Test 32
    n = eq(n, triangle("0", "10", "12"), "Illegal"); // Test 33
    n = eq(n, triangle("10", "12", "0"), "Illegal"); // Test 34
    n = eq(n, triangle("-1", "-1", "-1"), "Illegal"); // Test 35
    n = eq(n, triangle("-1", "10", "12"), "Illegal"); // Test 36
    n = eq(n, triangle("10", "-1", "12"), "Illegal"); // Test 37
    n = eq(n, triangle("10", "12", "-1"), "Illegal"); // Test 38
    n = eq(n, triangle("x", "y", "z"), "Illegal"); // Test 39
    n = eq(n, triangle("3", "4y", "5"), "Illegal"); // Test 40
    n = eq(n, triangle("10", "12", "13.4"), "Illegal"); // Test 41
    n = eq(n, triangle("03", "4", "5"), "Illegal"); // Test 42

    // Tests 43 to 47: check the upper limits on lengths
    n = eq(n, triangle("2147483647","2147483647","2147483647"),"Equilateral"); // Test 43
    n = eq(n, triangle("2147483648","2147483647","2147483647"),"Illegal"); // Test 44
    n = eq(n, triangle("2147483647","2147483648","2147483647"),"Illegal"); // Test 45
    n = eq(n, triangle("2147483647","2147483647","2147483648"),"Illegal"); // Test 46
    n = eq(n, triangle("2147483649","2147483649","2147483649"),"Illegal"); // Test 47

    // Tests 48 to 50: check for correct handling of overflow
    n = eq(n, triangle("1100000000","1705032704","1805032704"),"Scalene"); // Test 48
    n = eq(n, triangle("2000000001","2000000002","2000000003"),"Scalene"); // Test 49
    n = eq(n, triangle("150000002","666666671","683333338"),"Scalene"); // Test 50

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
