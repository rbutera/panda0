# Syntax in Functions
- **Pattern Matching** allows you to create separate function bodies for different patterns:
  - order is important. First come first served.

```haskell
lucky :: Int -> String
lucky 7 = "LUCKY NUMBER 7!"
lucky x = "Sorry, you're out of luck pal"
```

- **Recursive Definitions** - when a function calls itself inside its own definition:

```haskell
factorial :: Int -> Int
factorial 0 = 1
factorial n = n * factorial (n - 1)
```

- **Pattern Matching can FAIL**

## List Comprehension

You can use pattern matching in list comprehensions, like so:

```haskell
let xs = [(1,3),(4,3),(2,4),(5,3),(5,6),(3,1)]
[a+b | (a,b) <- xs] --[4,7,6,8,11,4]
```

**NB: you CANNOT use the `++` operator in pattern matches**

## AS-patterns

- Allow you to break up an item according to a pattern, while still keeping a reference to the entire original item.
- To create an as-pattern, precede a regular pattern with a **name** and `@` character.

Example of an as-pattern:

```haskell
firstLetter :: String -> String
firstLetter "" = "Empty string whoops!"
firstLetter all@(x:xs) = "The first letter of " ++ all ++ " is " ++ [x]
```
