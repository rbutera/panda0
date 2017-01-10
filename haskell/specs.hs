import Control.Monad

main = do
  specs <- forM ["cpu","ram", "gpu"] (\x -> do
      putStrLn("What is your " ++ x ++ "?")
      ans <- getLine
      return ans)
  putStrLn("your specs are ")
  mapM putStrLn specs
