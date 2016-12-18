#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

#define DEBUG          1

#ifdef DEBUG
#define DEBUG_PRINT    printf
#else
#define DEBUG_PRINT(...)
#endif

int NUMBER_OF_NODES = 0;


/********************************************************************************
*  BEGIN IMPLEMENTATION CODE
********************************************************************************/
struct node
{
    void *data;
    node *prev;
    node *next;
    int  wtf;
    bool isSentinel;
};

struct list
{
    int  itemSize;
    node *current;
    node *start;
    node *end;
};

node *newNode(int b, node *prev, node *next, void *data)
{
    node *output = malloc(sizeof(node));

    output->wtf        = NUMBER_OF_NODES++;
    output->data       = data;
    output->prev       = prev;
    output->next       = next;
    output->isSentinel = false;
    return output;
}


int *deleteNode(node *input)
{
    DEBUG_PRINT("deleting node\n");
    free(input);
    return 0;
}


/**
 * create a new list of items of a specified size
 * @param  b size of each item in bytes
 * @return   pointer to list
 */
list *newList(int b)
{
    // DEBUG_PRINT("creating list of size %i\n", b);
    list *output    = malloc(sizeof(struct list));
    node *startNode = malloc(sizeof(node));
    node *endNode   = malloc(sizeof(node));

    startNode->isSentinel = true;
    startNode->next       = endNode;

    endNode->isSentinel = true;
    endNode->prev       = startNode;

    output->itemSize = b;
    output->start    = startNode;
    output->end      = endNode;
    output->current  = startNode;
    // DEBUG_PRINT("list created. item size %i\n", output->itemSize);
    return output;
}


int removeList(list *l)
{
    // TODO: free nodes
    free(l);
    return 0;
}


/********************************************************************************
*  BEGIN TEST CODE
********************************************************************************/
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

    /*
     * DEBUG_PRINT("exampleList = %p\n", exampleList);
     * DEBUG_PRINT("exampleList->start \t= %p\n", exampleList->start);
     * DEBUG_PRINT("exampleList->current \t= %p\n", exampleList->current);
     * DEBUG_PRINT("exampleList->start->prev\t= %p\n", exampleList->start->prev);
     * DEBUG_PRINT("exampleList->start->next\t= %p\n", exampleList->start->next);
     * DEBUG_PRINT("exampleList->end\t= %p\n", exampleList->end);
     * DEBUG_PRINT("exampleList->end->prev\t= %p\n", exampleList->end->prev);
     * DEBUG_PRINT("exampleList->end->next\t= %p\n", exampleList->end->next);
     */
    mu_assert("end node 'prev' points to start (exampleList->end->prev != exampleList->start)", exampleList->end->prev == exampleList->start);
    mu_assert("start node 'next' points to start (exampleList->start->next != exampleList->end)", exampleList->start->next == exampleList->end);
    mu_assert("current node is start node", exampleList->start == exampleList->current);
    return 0;
}


static char *test_removeList()
{
    list *toRemove = newList(1024);

    mu_assert("Remove list", removeList(toRemove) == 0);
    return 0;
}


static char *all_tests()
{
    mu_run_test(test_check_testing_works);
    mu_run_test(test_newList);
    mu_run_test(test_removeList);
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
    printf("\nTests:\n\trun: %d\n\tpassed: %i\n\tfailed: %i\n", tests_run, tests_run - tests_failed, tests_failed);

    return result != 0;
}


int main()
{
    testLists();
}
