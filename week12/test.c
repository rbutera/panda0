#include "minunit.h"
#include "list.h"
#include "raibutera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tests_run     = 0;
int tests_failed  = 0;
int suites_run    = 0;
int suites_failed = 0;

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


/**
 * Scaffold a mock list for testing - runs before each of the tests below
 * @return [description]
 */
list *scaffold()
{
    list *nodeless = newList(99);

    char *aData = malloc((sizeof(char) * 5) + 1);
    char *bData = malloc((sizeof(char) * 6) + 1);
    char *cData = malloc((sizeof(char) * 5) + 1);

    aData = "first";
    bData = "second";
    cData = "third";

    node *a = newNode(aData, nodeless->start, nodeless->end);
    node *b = newNode(bData, a, nodeless->end);
    node *c = newNode(cData, b, nodeless->end);

    nodeless->start->next = a;
    nodeless->end->prev   = c;
    a->next = b;
    b->next = c;

    return nodeless;
}


static char *test_start()
{
    list *example = scaffold();

    example->current = example->start->next->next;
    // DEBUG_PRINT("%s\n", example->current->data);
    mu_assert("initial value of current incorrect for start", strcmp(example->current->data, "second") == 0);
    start(example);
    mu_assert("start sets list current to start->next", strcmp(example->current->data, "first") == 0);
    mu_assert("start sets list current to start->next (checking data)", example->current == example->start->next);
    // cleanupScaffold(example);
    return 0;
}


static char *test_end()
{
    list *example = scaffold();

    example->current = example->start;

    // DEBUG_PRINT("%s\n", example->current->next->data);

    mu_assert("initial value of current incorrect for end", strcmp(example->current->next->data, "first") == 0);
    end(example);
    mu_assert("end sets list current to end->prev", strcmp(example->current->data, "third") == 0);
    mu_assert("end sets list current to end->prev (checking data)", example->current == example->end->prev);
    // cleanupScaffold(example);
    return 0;
}


static char *test_atStart()
{
    list *example = scaffold();

    example->current = example->start->next;
    mu_assert("atStart returns true if at start->next", atStart(example));
    example->current = example->current->next;
    mu_assert("atStart returns false if not at start->next", !atStart(example));
    example->current = example->current->next;
    mu_assert("atStart returns false if not at start->next (again)", !atStart(example));
    // cleanupScaffold(example);
    return 0;
}


static char *test_atEnd()
{
    list *example = scaffold();

    example->current = example->end->prev;
    mu_assert("atEnd returns true if at end->prev", atEnd(example));
    example->current = example->current->prev;
    mu_assert("atEnd returns false if not at end->prev", !atEnd(example));
    example->current = example->current->prev;
    mu_assert("atEnd returns false if not at end->prev (again)", !atEnd(example));
    return 0;
}


static char *test_forward()
{
    list *example = scaffold();

    example->current = example->start->next;
    forward(example);
    mu_assert("forward works once", strcmp(example->current->data, "second") == 0);
    forward(example);
    mu_assert("forward works twice", strcmp(example->current->data, "third") == 0);
    forward(example);
    mu_assert("forward does nothing if already at end", strcmp(example->current->data, "third") == 0);
    return 0;
}


static char *test_backward()
{
    list *example = scaffold();

    example->current = example->end->prev;
    mu_assert("backward test should not fail because of atStart", !(atStart(example)));
    // DEBUG_PRINT("%s %s\n", example->current->data, example->current->prev->data);
    backward(example);
    mu_assert("backward works once", strcmp(example->current->data, "second") == 0);
    backward(example);
    mu_assert("backward works twice", strcmp(example->current->data, "first") == 0);
    backward(example);
    mu_assert("backward does nothing if already at end", strcmp(example->current->data, "first") == 0);
    return 0;
}


static char *test_insertBefore()
{
    list *example = scaffold();

    mu_assert("insertBefore implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_insertAfter()
{
    list *example = scaffold();

    mu_assert("insertAfter implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_getBefore()
{
    list *example = scaffold();

    mu_assert("getBefore implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_getAfter()
{
    list *example = scaffold();

    mu_assert("getAfter implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_setBefore()
{
    list *example = scaffold();

    mu_assert("setBefore implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_setAfter()
{
    list *example = scaffold();

    mu_assert("setAfter implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_deleteBefore()
{
    list *example = scaffold();

    mu_assert("deleteBefore implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *test_deleteAfter()
{
    list *example = scaffold();

    mu_assert("deleteAfter implemented", false);
    // cleanupScaffold(example);
    return 0;
}


static char *all_tests()
{
    mu_run_suite(test_check_testing_works);
    mu_run_suite(test_newList);
    mu_run_suite(test_removeList);
    mu_run_suite(test_newNode);
    mu_run_suite(test_start);
    mu_run_suite(test_end);
    mu_run_suite(test_atStart);
    mu_run_suite(test_atEnd);
    mu_run_suite(test_forward);
    mu_run_suite(test_backward);
    mu_run_suite(test_insertBefore);
    mu_run_suite(test_insertAfter);
    mu_run_suite(test_getBefore);
    mu_run_suite(test_getAfter);
    mu_run_suite(test_setBefore);
    mu_run_suite(test_setAfter);
    mu_run_suite(test_deleteBefore);
    mu_run_suite(test_deleteAfter);
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
    printf("%i tests passed.\n", tests_run - tests_failed);

    return tests_run - tests_failed;
}


int main()
{
    testLists();
}
