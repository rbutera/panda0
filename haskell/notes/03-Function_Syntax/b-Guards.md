# Guards (Function Syntax in Haskell)

Guards check if soem property of values passed to functions are constructed in a certain way.

```haskell
rwsTell :: Double -> String
rwsTell rws
  | rws <= 10.0 = "MM Scrub"
  | rws <= 12.5 = "ESEA Rookie"
  | rws <= 14 = "Almost Pro"
  | rws <= 20 = "Pro"
  | otherwise = "Cheater"
```

- Usually the last guard in a function is `otherwise` - catch-all

## Multiple Parameters + Guards

```haskell
bmiTell :: Double -> Double -> String
bmiTell weight height
  | weight / height ^ 2 <= 18.5 = "do u even lift"
  | weight / height ^ 2 <= 25 = "U a peng ting 😍"
  | weight / height ^ 2 <= 30 = "You must be best friends with a few McDonald's managers"
  | otherwise = "You fat as fuck homie"
```

## The `where` Keyword

The `where` keyword defines one or more variables or functions to be bound to a variable visible across multiple guards.

```haskell
bmiTell :: Double -> Double -> String
bmiTell weight height
  | bmi <= 18.5 = "do u even lift"
  | bmi <= 25 = "U a peng ting 😍"
  | bmi <= 30 = "You must be best friends with a few McDonald's managers"
  | otherwise = "You fat as fuck homie"
  where bmi = weight / height ^ 2
```

### Multiple `where`s

```haskell
bmiTell :: Double -> Double -> String
bmiTell weight height
  | bmi <= skinny = "do u even lift"
  | bmi <= avg = "U a peng ting 😍"
  | bmi <= fat = "You must be best friends with a few McDonald's managers"
  | otherwise = "You fat as fuck homie"
  where bmi = weight / height ^ 2
        skinny = 18.5
        avg = 25
        fat = 30
```

### `where`'s scope

- Where bindings arent shared across function bodies of different patterns.
- In order to share a variable across functions and functions of different patterns, declare them globally:

```haskell
ecoLoadout :: String
ecoLoadout = "buy fiveseven; buy vest; buy flashbang"
defaultLoadout :: String
defaultLoadout = "buy m4a4; buy a47; buy vesthelm; buy defuser; buy smokegrenade"
bestLoadout :: String
bestLoadout = "buy awp; buy vesthelm; buy defuser; buy p250; buy flashbang; buy smokegrenade"

callBuy :: Integer -> String
callBuy money
  | money <= 2500 = "FULL SAVE"
  | money < 4000 = ecoLoadout
  | money <= 6000 = defaultLoadout
  | otherwise = bestLoadout
```
