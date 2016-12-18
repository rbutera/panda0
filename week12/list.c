#include "raibutera.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"

int NUMBER_OF_NODES = 0;

node *newNode(void *data, node *prev, node *next)
{
    node *output = malloc(sizeof(node));

    output->id         = NUMBER_OF_NODES++;
    output->isSentinel = false;

    if (data != NULL)
    {
        output->data = data;
    }
    if (prev != NULL)
    {
        output->prev = prev;
    }
    if (next != NULL)
    {
        output->next = next;
    }

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
    list *output    = malloc(sizeof(list));
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


// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
void start(list *l)
{
    l->current = l->start->next;
}


void end(list *l)
{
    l->current = l->end->prev;
}


// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l)
{
    return false;
}


bool atEnd(list *l)
{
    return false;
}


// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l)
{
    DEBUG_PRINT("forward\n");
}


void backward(list *l)
{
    DEBUG_PRINT("backward\n");
}


// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).  The second argument is a pointer to the item to be copied.
void insertBefore(list *l, void *p)
{
    DEBUG_PRINT("insertBefore\n");
}


void insertAfter(list *l, void *p)
{
    DEBUG_PRINT("insertAfter\n");
}


// Get the item before the current position or after the current position.
// The second argument is a pointer to a place to copy the item into. It is an
// error to call getBefore when at the start, or getAfter when at the end.
void getBefore(list *l, void *p)
{
    DEBUG_PRINT("getBefore\n");
}


void getAfter(list *l, void *p)
{
    DEBUG_PRINT("getAfter\n");
}


// Set the item before the current position or after the current position.
// The second argument is a pointer to the new item value. It is an error to
// call setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, void *p)
{
    DEBUG_PRINT("setBefore\n");
}


void setAfter(list *l, void *p)
{
    DEBUG_PRINT("setAfter\n");
}


// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l)
{
    DEBUG_PRINT("deleteBefore\n");
}


void deleteAfter(list *l)
{
    DEBUG_PRINT("deleteAfter\n");
}
