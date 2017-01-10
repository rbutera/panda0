# I/O (Input and Output)
## Pure and Impure
Haskell is a pure functional programming language. Nothing is supposed to change state. Haskell separates the part of programs that are pure and the part that is impure.

## I/O Actions
An **I/O action** carries out an action with a side effect and yields a result.
We can use recursion in I/O actions.

## putStrLn
```haskell
putStrLn :: String -> IO ()
```

NB:
- putStrLn returns an **IO ACTION**
- the **IO ACTION** *yields* `()` (an empty tuple)
- `()` is used as a *dummy value* where nothing meaningful can be returned

## `main` and `do` blocks
IO actions are performed when named `main` and a program is run.
`do` blocks glue I/O actions together in a pseudo-imperative style into a single action.
main yields the last I/O action inside.
`do` blocks can be glued together.

```haskell
main = do
  foo <- putStrLn ("new fone who dis")
  name <- getLine
  putStrLn ("send nudes")
  putStrLn (name ++ "? are you there?? pls respond")
```

## The `<-` Construct
An I/O action performs something then maybe brings back some data. The fetched data can be bound using `<-`.
**NB:** Haskell will only let you take the data out of an I/O action when inside another I/O action.

You CANNOT concatenate a string and an I/O action... so the following is invalid

```haskell
-- INVALID!!!!!
nameTag = "Hello, my name is " ++ getLine
-- Valid
name <- getLine
putStrLn("Hello there, " ++ name)
```

We leave out the `<-` for I/O actions that don't yield an important result, like `putStrLn`

## Return
In Haskell, `return` makes an I/O action out of a pure value.

## Useful I/O Functions:
### putStr, putChar, and print
- `putStr`- doesn't put a new line
- `print` - basically `putStrLn . show`

### when
- `when`
  - looks like a flow-control statement, but its just a normal function
  - takes a `bool` and an I/O action.
    -  If the `Bool` value is **true** then it returns the same I/O action supplied.
    - If the `Bool` value is **false*** then it returns the `return ()` action.

### Sequence
`Sequence` takes a list of I/O actions and returns an I/O action that will perform those actions one after the other, for example `rs <- sequence [getLine, getLine, getLine]`

a common pattern with `sequence` is to map I/O functions over lists, creating a list of I/O actions, and then turning the list of I/O actions into a single I/O action, eg:

```haskell
main = sequence $ map print [1,2,3,4]
```
### mapM
`mapM` and `mapM_` encapsulate the pattern of mapping a function that returns an I/O action over a list and then sequencing it.
`mapM` yields results as normal. `mapM_` disposes of the result.

### forM
like `mapM` with reversed parameters. Useful in combination with lambdas and the `do` notation:

```haskell
import Control.Monad

main = do
  specs <- forM ["cpu","ram", "gpu"] (\x -> do
      putStrLn("What is your " ++ x ++ "?")
      ans <- getLine
  )
  putStrLn("your specs are ")
  mapM putStrLn specs
```

## Files and Streams
A *stream* is a succession of pieces of data entering or exiting a program over time.

We can use simple *input redirection* like all applications/programs using `EXECUTABLE_NAME < FILENAME` (e.g. `capslocker < haiku.txt`) in the command prompt.

## Getting Strings from Input Streams
`getContents` reads everything until it encounters `EOF`
It does lazy I/O, it doesn't read the input until the result is used.

## `interact` - Transforming Input
`interact` gets a string from the input, transforms it with a function, and outputs the result.
