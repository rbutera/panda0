# Types in Haskell
## Defining a Data Type using `data`
The syntax:
```haskell
data TYPENAME = VALUE_CONSTRUCTOR | VALUE_CONSTRUCTOR #... and so on
```

Basic type definition (`Bool`):
```haskell
data Bool = False | True
```

More complex example: a **shape** (`Shape`) that can be a circle or rectangle:

`data Shape = Circle Float Float Float | Rectangle Float Float Float Float`

A **value constructor** is a function that ultimately returns a value of a data type

## Deriving from Type Classes

Making `Shape` type part of the `Show` type class:
```haskell
data Shape = Circle Float Float Float | Rectangle Float Float Float Float
  deriving (Show)
```

## Limitations of the `Data` Syntax
A large number of fields is unwieldy when using the `data` type. The definition is long and obfuscated, and using the class in functions is unwieldy when a small number of fields is required, eg:

```haskell
data Person = Person String String int Float String String deriving (Show)
firstName :: Person -> String
firstName (Person firstName _____) = firstNam

## The Record Syntax
Defining a `PCBuild` type using the *record syntax*

```haskell
data PCBuild = PCBuild { cpu :: String,
                      , memory :: String,
                      , gpu :: String } deriving (Show)
```

Instantiating a `PCBuild`:

```haskell
PCBuild {cpu="6700K", memory="16GB", gpu="GTX 970"}
```

## Type Parameters
Type constructors can take types as parameters to produce new types.

`Maybe` is implemented in such a way:
```haskell
data Maybe a = Nothing | Just a
```
