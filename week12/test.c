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
    mu_assert("creates a startNode with isSentinel == true", exampleList->start->isSentinel == true);
    mu_assert("creates end node", exampleList->end != NULL);
    mu_assert("creates end Node with isSentinel == true", exampleList->end->isSentinel == true);
    mu_assert("start Node 'next' points to start (exampleList->start->next != exampleList->end)", exampleList->start->next == exampleList->end);
    mu_assert("current Node is start node", exampleList->start == exampleList->current);
    return 0;
}


static char *test_newNode()
{
    list *nodeless = newList(99);

    char *aData = malloc((sizeof(char) * 3) + 1);

    aData = "foo";
    char *bData = malloc((sizeof(char) * 3) + 1);
    bData = "bar";
    char *cData = malloc((sizeof(char) * 10) + 8);
    cData = "Raimondo";

    Node *a = newNode(aData, nodeless->start, nodeless->end);
    Node *b = newNode(bData, a, nodeless->end);
    Node *c = newNode(cData, b, nodeless->end);
    a->next = b;
    b->next = c;

    mu_assert("newNode works", 999 == 999);
    // DEBUG_PRINT("nodeless Node ids: %i %i %i\n", nodeless->start->next->id, nodeless->start->next->next->id, nodeless->start->next->next->next->id);
    // DEBUG_PRINT("Node ids: %i %i %i", a->id, b->id, c->id);
    mu_assert("newNode creates a Node with an id", a->id == 0);
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


static char *all_tests()
{
    mu_run_test(test_check_testing_works);
    mu_run_test(test_newList);
    mu_run_test(test_removeList);
    mu_run_test(test_newNode);
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
