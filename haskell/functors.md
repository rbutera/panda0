# Functors
## Critical
- Functor wants a type constructor that takes only one type parameter.

## Intro
The functor type class is for things that can be mapped over
The list type is a part of the Functor type class

## Implementation
```haskell
classFunctor f where
  fmap :: (a - b) -> f a -> f b
```
**NB**:
- f is not a concrete type
- f is a _**type constructor**_ that takes **one value**

## Lists as an instance of the `Functor` type class

```haskell
instance Functor [] where   -- NB: [] is a type constructor that takes one type
    fmap = map
```

## Functors and Boxes
Types like `list` that can 'act like a box' can be functors. A box that can be epty or have something inside it, including another box.

`Maybe` can either hold nothing or it can contain one item, so it can be a functor:

```haskell
instance Functor Maybe where
  fmap f (Just x) = Just (f x)
  fmap f Nothing = Nothing
```

a **Tree** can also be a _functor_, however a binary search tree may lose its integrity if mapped over (all of the elements to the left of a node in a binary search tree must be smalle rthan the element in the node, and all the elements to the right must be greater.)

## `Either` as a functor
Reminder of how `Either` is defined:
```haskell
data Either a b = Left a | Right b
```

it is defined as a functor in the standard libraries:

```haskell
instance Functor (Either a) where
  fmap f (Right x) = Right (f x)
  fmap f (Left x) = Left x
```
We do not map over `left`. We use `Either a` because it is a type constructor that takes one parameter.
