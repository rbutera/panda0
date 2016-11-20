# Syntax in Functions
- **Pattern Matching** allows you to create separate function bodies for different patterns:
  - order is important. First come first served.

```haskell
lucky :: Int -> String
lucky 7 = "LUCKY NUMBER 7!"
lucky x = "Sorry, you're out of luck pal"
```
