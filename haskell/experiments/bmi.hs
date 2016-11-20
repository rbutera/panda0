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
