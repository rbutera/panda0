# Haskell
Notes mostly taken from Learn You a Haskell for Great Good!

## Chapter 1

- `if` statements **MUST** accompany an `else`
- Function names can contain `'` quotes
  - usually used to denote either a *strict* version of a function or a slightly modified version of a function or variable with a similar name.
- functions cannot begin with capital letters

### Lists

```haskell
let raisListOfNumbers = [1,2,3,4,5,6]
```

must be homogenous data types

### Concatenation
- appending done via `++` operator
- prepending done via `:` operator (the *cons* operator)

### Traversing Lists

- access list elements using `!!`
- `head` takes a list and returns first element
- `tail` returns everythign but head
- `last` returns LAST
- `init` returns all but last
- `length` gets list length
- `null` checks if a list is empty
- `reverse` reverses a list
- `take` extracts n elements from beginning
- `drop` drops n elements from beginning of list
- `maximum` returns largest element
- `minimum` returns smallest
- `sum` and `product` are obvious
- `elem` takes an item and a list of items and tells if the item is an element of the list

## Ranges

- ranges + infinite lists are convenient:

```Haskell
[13,26..24*13]
take 24[13,26..]
```

## Infinite Lists
- `cycle` takes a list and replicates elements indefinitely
- `repeat` produces an infinite list a single element
- `replicate` takes length of lsit and item to replicate
- ranges with floating point numbers yield funky results

## List Comprehensions
- ways of filter, transform or combine lists
- example: `[x*2 | x <- [1..10]]`
- predicates go on end, act like filters `[x*2 | x <- [1..10], x * 2 >= 12 ]` would only return the values which are greater than 12


## Tuples
- used to store several heterogenous elements as a single value
- tuples have a fixed size
- you cant compare two tuples of different sizes
- the size of a tuple is considered part of its type
- a tuple of size 2 is called a **PAIR**
- a tuple of size 3 is called a **TRIPLE**

### Functions that operate on pairs
Function  |  Behaviour
--|--
fst  |  returns first component
snd  |  returns second component
zip  |  joins matching elements of two lists into pairs


## Finding the Right Triangle
- Problem that combines tuples and list comprehensions
- use Haskell to find a right triangle that fits all of these conditions:
  1. lenghts of al three sides are integers
  2. length of each side is less than or equal to 10
  3. the triangle's perimeter is equal to 24
