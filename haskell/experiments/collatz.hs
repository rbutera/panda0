createCollatzChain :: Integer -> [Integer]
createCollatzChain 1 = [1]
createCollatzChain x
  | odd x = x : createCollatzChain ((x * 3) + 1)
  | even x = x : createCollatzChain (x `div` 2)


allCollatzChainsToHundred = map createCollatzChain [1..100]
longCollatzChainsToHundred =
  let x = allCollatzChainsToHundred
      isLong y = length y > 15
  in filter isLong allCollatzChainsToHundred


lengthsCollatzChainsToHundred = map (length) allCollatzChainsToHundred
lengthsOfLongCollatzChains = filter (>15) lengthsCollatzChainsToHundred

numLongCollatzChains = length longCollatzChainsToHundred
numLongCollatzChains' = length lengthsOfLongCollatzChains

didRaiSmashIt = numLongCollatzChains == numLongCollatzChains'
