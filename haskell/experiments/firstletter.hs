firstLetter :: String -> String
firstLetter "" = "Empty string whoops!"
firstLetter all@(x:xs) = "The first letter of " ++ "\"" ++ all ++ "\"" ++ " is " ++ [x]
showFL :: (Show a) => [a] -> String
showFL a = show a
