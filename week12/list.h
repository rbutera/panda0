/* This is a library module supporting generic lists.  A list has a current
position which is thought of as being between items, and can thus be anywhere
from before the first item to after the last item.  Lists are implemented using
doubly linked nodes, so that every operation is constant time.

The items stored in a list can be of any raw type (e.g int, char[20], struct...)
or pointer type (e.g. char *, struct...*).  The byte-size of the type is
specified when the list is created. In the case of a raw type, an item is copied
into the list and the caller does not need to allocate memory for it.  Items
must be passed to the library functions by pointer (because the library cannot
know how much memory is needed for the function arguments). So, it may be
convenient to define type-correct synonyms, e.g. for a list of int:

    inline list *newIntList() { return newList(sizeof(int)); }
    inline void insertIntBefore(list *l, int n) { insertBefore(l, &n); }

In the case of items which are pointers, the pointer is copied into the list,
but the caller is responsible for allocating the memory which the item points
to.  For uniformity, a pointer is passed using a pointer-to-a-pointer, so again
it may be convenient to define synonyms such as:

    inline list *newStringList() { return newList(sizeof(char *)); }
    inline void insertStringBefore(list *l, char *s) { insertBefore(l, &s); }

The lists provided by this module are not thread safe.
*/
#include <stdbool.h>
#ifndef LIST_H_
#define LIST_H_

// The list type is opaque (declared here, and defined in list.c).
struct list;
struct node;

typedef struct Node
{
    void *data;
    struct Node *prev;
    struct Node *next;
    int  id;
    bool isSentinel;
} node;

typedef struct List
{
    int  itemSize;
    struct Node *current;
    struct Node *start;
    struct Node *end;
    int listId;
} list;

// For Debugging purposes
int listDetails(list *input);
int printList(list *l);

// Create a new node.
node *newNode(void *data, node *prev, node *next);

// Create a new empty list.  The argument is the size of an item in bytes.
list *newList(int b);

// Delete a list at a given address.
int removeList(list *l);

// Set the current position before the first item or after the last item, e.g.
// to begin a forward or backward traversal.
void start(list *l);
void end(list *l);

// Check whether the current position is at the start or end, e.g. to test
// whether a traversal has finished.
bool atStart(list *l);
bool atEnd(list *l);

// Move the current position one place forwards or backwards.  It is an error
// to call forward when at the end of the list, or backward when at the start.
void forward(list *l);
void backward(list *l);

// Insert an item before or after the current position (i.e. at the current
// position, but with the current position ending up after or before the new
// item).  The second argument is a pointer to the item to be copied.
void insertBefore(list *l, void *p);
void insertAfter(list *l, void *p);

// Get the item before the current position or after the current position.
// The second argument is a pointer to a place to copy the item into. It is an
// error to call getBefore when at the start, or getAfter when at the end.
void getBefore(list *l, void *p);
void getAfter(list *l, void *p);

// Set the item before the current position or after the current position.
// The second argument is a pointer to the new item value. It is an error to
// call setBefore when at the start, or setAfter when at the end.
void setBefore(list *l, void *p);
void setAfter(list *l, void *p);

// Delete the item before or after the current position. It is an error to call
// deleteBefore when at the start, or deleteAfter when at the end.
void deleteBefore(list *l);
void deleteAfter(list *l);

// Unit testing.  Test the module, returning the number of tests passed.  If a
// test fails, print out a message and stop the program.
int testLists();

#endif
