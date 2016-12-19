#include "debugprint.h"
#include "minunit.h"
#include "list.h"
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

    mu_assert("Assigns listId", exampleList->listId > 0);
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

    // test insertBefore at beginning of list
    char *dummyData = malloc(sizeof(char) * 9);

    dummyData = "12345678";
    start(example);
    insertBefore(example, dummyData);
    mu_assert("insertBefore works at start of list", strcmp(example->start->next->data, "12345678") == 0);

    // test insertBefore at end of list
    char *moreDummyData = malloc(sizeof(char) * 5);
    moreDummyData = "more";
    end(example);
    insertBefore(example, moreDummyData);
    mu_assert("insertBefore works at end of list", strcmp(example->end->prev->prev->data, "more") == 0);


    // test insertBefore in the middle of a list
    char *malcom = malloc(sizeof(char) * 7);
    malcom = "malcom"; // malcom in the middle, hehe
    start(example);
    forward(example);
    forward(example);
    insertBefore(example, malcom);
    mu_assert("malcom is in the middle", strcmp(example->start->next->next->next->data, "malcom") == 0);

    return 0;
}


static char *test_insertAfter()
{
    list *example = scaffold();

    // printList(example);
    // test insertBefore at beginning of list
    char *dummyData = malloc(sizeof(char) * 9);

    dummyData = "87654321";
    start(example);
    insertAfter(example, dummyData);
    mu_assert("insertAfter works at start of list", strcmp(example->current->next->data, "87654321") == 0);

    // test insertAfter at end of list
    char *moreDummyData = malloc(sizeof(char) * 5);
    moreDummyData = "erom";
    end(example);
    insertAfter(example, moreDummyData);
    mu_assert("insertAfter works at end of list", strcmp(example->end->prev->data, "erom") == 0);


    // test insertAfter in the middle of a list
    char *malcom = malloc(sizeof(char) * 7);
    malcom = "moclam"; // malcom in the middle, hehe
    start(example);
    forward(example);
    forward(example);
    insertAfter(example, malcom);
    mu_assert("malcom is in the middle", strcmp(example->start->next->next->next->next->data, "moclam") == 0);

    return 0;
}


static char *test_getBefore()
{
    list *example = scaffold();
    char buffer[100]; // where we will copy test values to

    // typical example. getting first value by getBefore the second value
    example->current = example->start->next->next; // should be "second"
    getBefore(example, buffer);
    mu_assert("getBefore can handle a typical case", strcmp(buffer, "first") == 0);

    // edge case: getBefore at start of list should not work
    char edgeCaseBuffer[100];
    list *edgeCase = scaffold();
    edgeCase->current = edgeCase->start->next;
    getBefore(edgeCase, edgeCaseBuffer);
    // DEBUG_PRINT("EDGE CASE: %s\n strcmp results = %i and %i", edgeCaseBuffer, strcmp(edgeCaseBuffer, "first"), strcmp(edgeCaseBuffer, "first") == 1);
    mu_assert("getBefore fails if used at start of list", edgeCaseBuffer[0] != "f");
    mu_assert("getBefore copies ERROR if used at start of list", strcmp(edgeCaseBuffer, "ERROR") == 0);
    return 0;
}


static char *test_getAfter()
{
    list *example = scaffold();
    char buffer[100]; // where we will copy test values to

    // typical example. getting first value by getAfter the second value
    example->current = example->start->next->next; // should be "second"
    getAfter(example, buffer);
    mu_assert("getAfter can handle a typical case", strcmp(buffer, "third") == 0);

    // edge case: getAfter at start of list should not work
    char edgeCaseBuffer[100];
    list *edgeCase = scaffold();
    edgeCase->current = edgeCase->end->prev;
    getAfter(edgeCase, edgeCaseBuffer);
    // DEBUG_PRINT("EDGE CASE: %s\n strcmp results = %i and %i", edgeCaseBuffer, strcmp(edgeCaseBuffer, "first"), strcmp(edgeCaseBuffer, "first") == 1);
    mu_assert("getAfter fails if used at start of list", edgeCaseBuffer[0] != "t");
    mu_assert("getAfter copies ERROR if used at start of list", strcmp(edgeCaseBuffer, "ERROR") == 0);
    return 0;
}


static char *test_setBefore()
{
    list *example = scaffold();
    char buffer[100]; // where we will copy test values to

    // typical example. getting first value by getBefore the second value
    example->current = example->start->next->next; // should be "second"
    setBefore(example, "surprise");
    getBefore(example, buffer);
    mu_assert("getBefore can handle a typical case", strcmp(buffer, "surprise") == 0);

    // edge case: getBefore at start of list should not work
    char edgeCaseBuffer[100];
    list *edgeCase = scaffold();
    edgeCase->current = edgeCase->start->next;
    setBefore(example, "mofukka");
    getBefore(edgeCase, edgeCaseBuffer);
    // DEBUG_PRINT("EDGE CASE: %s\n strcmp results = %i and %i", edgeCaseBuffer, strcmp(edgeCaseBuffer, "first"), strcmp(edgeCaseBuffer, "first") == 1);
    mu_assert("getBefore fails if used at start of list", edgeCaseBuffer[0] != "m");
    mu_assert("getBefore copies ERROR if used at start of list", strcmp(edgeCaseBuffer, "ERROR") == 0);
    return 0;
}


static char *test_setAfter()
{
    list *example = scaffold();
    char buffer[100]; // where we will copy test values to

    // typical example. getting first value by setAfter the second value
    example->current = example->start->next->next; // should be "second"
    setAfter(example, "good luck");
    getAfter(example, buffer);
    mu_assert("setAfter can handle a typical case", strcmp(buffer, "good luck") == 0);

    // edge case: setAfter at start of list should not work
    char edgeCaseBuffer[100];
    list *edgeCase = scaffold();
    edgeCase->current = edgeCase->end->prev;
    setAfter(edgeCase, "have fun");
    getAfter(edgeCase, edgeCaseBuffer);
    // DEBUG_PRINT("EDGE CASE: %s\n strcmp results = %i and %i", edgeCaseBuffer, strcmp(edgeCaseBuffer, "first"), strcmp(edgeCaseBuffer, "first") == 1);
    mu_assert("setAfter fails if used at start of list", edgeCaseBuffer[0] != "t");
    mu_assert("setAfter copies ERROR if used at start of list", strcmp(edgeCaseBuffer, "ERROR") == 0);
    return 0;
}


static char *test_deleteBefore()
{
    node *deletedPrev;

    // deleteBefore at end
    list *endExample = scaffold();

    end(endExample);
    deletedPrev = endExample->current->prev->prev;
    deleteBefore(endExample);
    // printList(endExample);
    // check current's prev is set to the deleted note's prev
    mu_assert("deleteBefore end: current's prev is set to the deleted note's prev", endExample->current->prev == deletedPrev);
    // check deleted note's prev points to to the current node
    mu_assert("deleteBefore end: deleted note's prev points to to the current node", deletedPrev->next == endExample->current);

    // deleteBefore in the middle
    list *middleExample = scaffold();

    start(middleExample);
    forward(middleExample);
    deletedPrev = middleExample->current->prev->prev;
    deleteBefore(middleExample);
    // printList(middleExample);
    node *firstNode = middleExample->start->next->data;
    // DEBUG_PRINT("\nmiddleExample->start->next->data = %s\n", firstNode);
    // DEBUG_PRINT("strcmp = %i", strcmp(firstNode, "first"));
    mu_assert("deleteBefore middle: first element no longer exists #1", strcmp(middleExample->start->next->data, "first") != 0);
    mu_assert("deleteBefore middle: first element no longer exists # 2 ", strcmp(middleExample->start->next->data, "second") == 0);
    // check current's prev is set to the deleted note's prev
    mu_assert("deleteBefore middle: current's prev is set to the deleted note's prev", middleExample->current->prev == deletedPrev);
    // check deleted note's prev points to to the current node
    mu_assert("deleteBefore middle: deleted note's prev points to to the current node", deletedPrev->next == middleExample->current);

    // deleteBefore at start - shouldn't work
    list *startExample = scaffold();
    start(startExample);
    deleteBefore(startExample);
    // printList(startExample);
    // check list still has 3 elements
    //DEBUG_PRINT("deleteBefore startExample: %s\n", startExample->start->next->data);
    //DEBUG_PRINT("strcmp first: %i\n", strcmp(startExample->start->next->data, "first"));
    mu_assert("deleteBefore edgecase: first element still exists", strcmp(startExample->start->next->data, "first") == 0);
    mu_assert("deleteBefore edgecase: second element still exists", strcmp(startExample->start->next->next->data, "second") == 0);
    mu_assert("deleteBefore edgecase: third element still exists", strcmp(startExample->start->next->next->next->data, "third") == 0);
    mu_assert("deleteBefore implemented", true);
    // cleanupScaffold(example);
    return 0;
}


static char *test_deleteAfter()
{
    list *lol = scaffold();

    start(lol);
    mu_assert("deleteAfter test set up correctly", strcmp(lol->current->data, "first") == 0);
    deleteAfter(lol);
    mu_assert("deleteAfter deletes next node", strcmp(lol->current->next->data, "second") != 0);
    mu_assert("deleteAfter pulls in the next node", strcmp(lol->current->next->data, "third") == 0);
    deleteAfter(lol);
    mu_assert("deleteAfter can kill the third node and thus join current to the end sentinel", lol->current->next->isSentinel);
    deleteAfter(lol);
    mu_assert("deleteAfter won't try and delete the end node", lol->current->next->isSentinel);
    mu_assert("deleteAfter won't try and delete the end node", strcmp(lol->current->data, "first") == 0);
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
