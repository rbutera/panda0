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

    return output;
}
