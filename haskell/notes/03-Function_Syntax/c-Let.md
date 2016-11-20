# Let vs Where
`let` is similar to `where`, but whilst `where` is expression first and bindings after, `let` is **bindings first and expression after**.

```haskell
cylinder :: Double -> Double -> Double
cylinder r h =
  let sideArea = 2 * pi * r * h
      topArea = pi * r ^ 2
  in  sideArea + 2 * topArea
```

## The significance of `let` being an *expression*

- Expressions have, by definition, a value
- This means you can use `let` expressions almost anywhere in your code

## Multiple `let` expressions

- Separate using a semicolon

```haskell
(let a = 100; b = 200; c = 300 in a*b*c, let foo = "Hey "; bar = "there" in foo ++ bar)
-- this returns (6000000, "Hey there")
```
