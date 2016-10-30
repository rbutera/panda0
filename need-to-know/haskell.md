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
