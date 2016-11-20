rwsTell :: Double -> String
rwsTell rws
  | rws <= 10.0 = "MM Scrub"
  | rws <= 12.5 = "ESEA Rookie"
  | rws <= 14 = "Almost Pro"
  | rws <= 20 = "Pro"
  | otherwise = "Cheater"
