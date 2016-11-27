quickSort :: (Ord a) => [a] -> [a]
quickSort [] = []
quickSort (x:xs) =
  let smaller = [a | a <- xs, a <= x]
      bigger = [a | a <- xs, a > x]
  in  quickSort smaller ++ [x] ++ quickSort bigger
