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
