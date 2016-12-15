#include <stdio.h>
#include "list.h"
#include "minunit.h"

int tests_run    = 0;
int tests_failed = 0;

static char *test_check_testing_works()
{
    mu_assert("Testing does not work", 7 == 7);
    return 0;
}


static char *test_newList()
{
    mu_assert("New list works", false);
    return 0;
}


static char *all_tests()
{
    mu_run_test(test_check_testing_works);
    mu_run_test(test_newList);
    return 0;
}


int testLists()
{
    char *result = all_tests();

    if (result != 0)
    {
        printf("TEST FAIL: %s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("\nTests:\n\trun: %d\n\tpassed: %i\n\tfailed: %i\n", tests_run, tests_run - tests_failed, tests_failed);

    return result != 0;
}


int main(int argc, char **argv)
{
    testLists();
}
