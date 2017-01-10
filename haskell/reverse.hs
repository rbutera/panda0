main = do
  putStrLn("input:")
  input <- getLine
  if null input
    then return ()
    else do
      let reversed = reverse input
      putStrLn reversed
      main
