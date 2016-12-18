#include "minunit.h"
#include "list.h"
#include "raibutera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run    = 0;
int tests_failed = 0;

static char *test_check_testing_works()
{
    mu_assert("Testing does not work", 7 == 7);
    return 0;
}


static char *test_newList()
{
    int  exampleSize  = 42;
    list *exampleList = newList(exampleSize);

    mu_assert("New list works", 999 == 999);
    mu_assert("itemSize valid", exampleList->itemSize == exampleSize);
    mu_assert("creates start nodes", exampleList->start != NULL);
    mu_assert("creates a startnode with isSentinel == true", exampleList->start->isSentinel == true);
    mu_assert("creates end node", exampleList->end != NULL);
    mu_assert("creates end node with isSentinel == true", exampleList->end->isSentinel == true);
    mu_assert("start node 'next' points to start (exampleList->start->next != exampleList->end)", exampleList->start->next == exampleList->end);
    mu_assert("current node is start node", exampleList->start == exampleList->current);
    return 0;
}


static char *test_newNode()
{
    list *nodeless = newList(99);

    char *aData = malloc((sizeof(char) * 3) + 1);
    char *bData = malloc((sizeof(char) * 3) + 1);
    char *cData = malloc((sizeof(char) * 10) + 8);

    aData = "foo";
    bData = "bar";
    cData = "Raimondo";

    node *a = newNode(aData, nodeless->start, nodeless->end);
    node *b = newNode(bData, a, nodeless->end);
    node *c = newNode(cData, b, nodeless->end);

    a->next = b;
    b->next = c;

    mu_assert("newNode works", 999 == 999);
    // DEBUG_PRINT("nodeless node ids: %i %i %i\n", nodeless->start->next->id, nodeless->start->next->next->id, nodeless->start->next->next->next->id);
    // DEBUG_PRINT("node ids: %i %i %i", a->id, b->id, c->id);
    mu_assert("newNode creates a node with an id", a->id == 0);
    mu_assert("the id increments with each new node", b->id == 1 && c->id == 2);
    mu_assert("newNode sets isSentinel to false", a->isSentinel == false);
    mu_assert("newNode sets prev", a->prev == nodeless->start);
    mu_assert("newNode sets next", c->next == nodeless->end);
    mu_assert("newNode sets data (#1)", strcmp(a->data, "foo") == 0);
    mu_assert("newNode sets data (#2)", strcmp(b->data, "bar") == 0);
    mu_assert("newNode sets data (#3)", strcmp(c->data, "Raimondo") == 0);

    return 0;
}


static char *test_removeList()
{
    list *toRemove = newList(1024);

    mu_assert("Remove list returns 0", removeList(toRemove) == 0);
    return 0;
}


static char *test_start()
{
    mu_assert("start implemented", false);
    return 0;
}


static char *test_end()
{
    mu_assert("end implemented", false);
    return 0;
}


static char *test_atStart()
{
    mu_assert("atStart implemented", false);
    return 0;
}


static char *test_atEnd()
{
    mu_assert("atEnd implemented", false);
    return 0;
}


static char *test_forward()
{
    mu_assert("forward implemented", false);
    return 0;
}


static char *test_backward()
{
    mu_assert("backward implemented", false);
    return 0;
}


static char *test_insertBefore()
{
    mu_assert("insertBefore implemented", false);
    return 0;
}


static char *test_insertAfter()
{
    mu_assert("insertAfter implemented", false);
    return 0;
}


static char *test_getBefore()
{
    mu_assert("getBefore implemented", false);
    return 0;
}


static char *test_getAfter()
{
    mu_assert("getAfter implemented", false);
    return 0;
}


static char *test_setBefore()
{
    mu_assert("setBefore implemented", false);
    return 0;
}


static char *test_setAfter()
{
    mu_assert("setAfter implemented", false);
    return 0;
}


static char *test_deleteBefore()
{
    mu_assert("deleteBefore implemented", false);
    return 0;
}


static char *test_deleteAfter()
{
    mu_assert("deleteAfter implemented", false);
    return 0;
}


static char *all_tests()
{
    mu_run_test(test_check_testing_works);
    mu_run_test(test_newList);
    mu_run_test(test_removeList);
    mu_run_test(test_newNode);
    mu_run_test(test_start);
    mu_run_test(test_end);
    mu_run_test(test_atStart);
    mu_run_test(test_atEnd);
    mu_run_test(test_forward);
    mu_run_test(test_backward);
    mu_run_test(test_insertBefore);
    mu_run_test(test_insertAfter);
    mu_run_test(test_getBefore);
    mu_run_test(test_getAfter);
    mu_run_test(test_setBefore);
    mu_run_test(test_setAfter);
    mu_run_test(test_deleteBefore);
    mu_run_test(test_deleteAfter);
    return 0;
}


int testLists()
{
    char *result = all_tests();

    if (result != 0)
    {
        printf("FAIL: %s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("-----------------------------------------------------\nTests:\n\trun: %d\n\tpassed: %i\n\tfailed: %i\n-----------------------------------------------------\n", tests_run, tests_run - tests_failed, tests_failed);

    return tests_run - tests_failed;
}


int main()
{
    testLists();
}
