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
