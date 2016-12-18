#include "debugprint.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"

int NUMBER_OF_NODES = 0;
int NUMBER_OF_LISTS = 0;

int listDetails(list *input)
{
    DEBUG_PRINT("input->listId\t%i\n", input->listId);
    DEBUG_PRINT("input->current->id\t%i\n", input->current->id);
    DEBUG_PRINT("input->start->id\t%i\n", input->start->id);
    DEBUG_PRINT("input->end->id\t%i\n", input->end->id);
    return 0;
}


int printList(list *l)
{
    node *itemPtr  = l->start;
    int  index     = 0;
    bool searching = true;

    while (searching)
    {
        if (itemPtr->isSentinel)
        {
            DEBUG_PRINT("Items (%i bytes each):\n", l->itemSize);
        }
        else
        {
            DEBUG_PRINT("\t[node %i]\t%s", itemPtr->id, itemPtr->data);
            if (l->current == itemPtr)
            {
                DEBUG_PRINT("\t<-");
            }
            DEBUG_PRINT("\n");
        }

        if (itemPtr->next->isSentinel)
        {
            searching = false;
            DEBUG_PRINT("\ntotal: %i items.\n", NUMBER_OF_LISTS);
        }
        index++;
        itemPtr = itemPtr->next;
    }
}


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
    list *output    = malloc(sizeof(list));
    node *startNode = malloc(sizeof(node));
    node *endNode   = malloc(sizeof(node));

    startNode->isSentinel = true;
    startNode->next       = endNode;

    endNode->isSentinel = true;
    endNode->prev       = startNode;

    output->listId   = ++NUMBER_OF_LISTS;
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
    NUMBER_OF_LISTS--;
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
    if (l && (l->current == l->start->next) && ((l->current->isSentinel == true) || (l->current->prev->isSentinel == true)))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool atEnd(list *l)
{
    if (l)
    {
        return l->current->next->isSentinel == true && l->current == l->end->prev;
    }
    else
    {
        return false;
    }
}


// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l)
{
    if (!atEnd(l))
    {
        l->current = l->current->next;
    }
}


void backward(list *l)
{
    if (!atStart(l))
    {
        l->current = l->current->prev;
    }
}


// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).  The second argument is a pointer to the item to be copied.
void insertBefore(list *l, void *p)
{
    node *prevCopy = l->current->prev;

    // create new node, setting next to the encumbent current, and prev to the encumbent current's predecessor
    node *created = newNode(p, prevCopy, l->current);

    // update encumbent current's prev value to new node
    l->current->prev = created;
    // update the previous value's next pointer to the new node
    prevCopy->next = created;
}


void insertAfter(list *l, void *p)
{
    node *nextCopy = l->current->next;

    // create new node, setting next to the encumbent current, and prev to the encumbent current's predecessor
    node *created = newNode(p, l->current, nextCopy);

    // update encumbent current's next value to new node
    l->current->next = created;
    // update the next value's prev pointer to the new node
    nextCopy->prev = created;
}


// Get the item before the current position or after the current position.
// The second argument is a pointer to a place to copy the item into. It is an
// error to call getBefore when at the start, or getAfter when at the end.
void getBefore(list *l, void *p)
{
    // printList(l);

    if (!atStart(l))
    {
        memcpy(p, l->current->prev->data, l->itemSize);
        // DEBUG_PRINT("\ngetBefore:\nl->c->p->d = %s\nl->itemSize = %i", l->current->prev->data, l->itemSize);
    }
    else
    {
        strcpy(p, "ERROR");
    }
}


void getAfter(list *l, void *p)
{
    if (!atEnd(l))
    {
        memcpy(p, l->current->next->data, l->itemSize);
    }
    else
    {
        strcpy(p, "ERROR");
    }
}


// Set the item before the current position or after the current position.
// The second argument is a pointer to the new item value. It is an error to
// call setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, void *p)
{
    if (!atStart(l))
    {
        l->current->prev->data = p;
    }
    else
    {
        // DEBUG_PRINT("ERROR: setBefore used at start of a list!\n");
    }
}


void setAfter(list *l, void *p)
{
    if (!atEnd(l))
    {
        l->current->next->data = p;
    }
    else
    {
        // DEBUG_PRINT("ERROR: setAfter used at end of list!\n");
    }
}


// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l)
{
    if (!atStart(l))
    {
        node *deletedPrev = l->current->prev->prev;

        l->current->prev  = deletedPrev;
        deletedPrev->next = l->current;
    }
    else
    {
        DEBUG_PRINT("ERROR: deleteBefore used at start of a list!\n");
    }
}


void deleteAfter(list *l)
{
    if (!atEnd(l))
    {
        DEBUG_PRINT("deleteAfter not at end\n");
    }
    else
    {
        // DEBUG_PRINT("ERROR: deleteAfter used at end of list!\n");
    }
}
