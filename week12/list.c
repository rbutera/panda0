#include "list.h"
#include <stdio.h>

struct node
{
    void *data;
    node *prev;
    node *next;
};

typedef struct node   node;

struct list
{
    int  itemSize;
    node *current;
    node *start;
    node *end;
};

list *newList(int b)
{
    list *output = malloc(sizeof list);
    node startNode;
    node endNode;
    node *startNodePtr;
    node *endNodePtr;
    output->start = startNodePtr;
    output->end = endNodePtr;
    return output;
}
