module Answer where
import Turtle
import Data.Char

-----------------------------------------------------------
-- Part 0
-----------------------------------------------------------
cursor :: Command
cursor = Lt 160 :> Fd 0.04
      :> Lt 180 :> Fd 0.04
      :> Lt 220 :> Fd 0.04
      :> Lt 180 :> Fd 0.04
      :> Lt 340


-----------------------------------------------------------
-- Part 1
-----------------------------------------------------------
square :: Command
square = Fd 1 :> Rt 90
      :> Fd 1 :> Rt 90
      :> Fd 1 :> Rt 90
      :> Fd 1 :> Rt 90

-- TODO #1.1
triangle :: Command
triangle = Fd 1 :> Rt 120 :> Fd 1 :> Rt 120 :> Fd 1

-- TODO #1.0 Repeat Function
rep :: Int -> Command -> Command
rep n x
  | n > 1     = x :> rep (n-1) x
  | otherwise = x

turnAmount :: Int -> Double
turnAmount x = 360 / fromIntegral x

polygon :: Int -> Command
polygon n = rep n (Fd 1 :> Rt (turnAmount n))

hexagon :: Command
hexagon = polygon 6

-- TODO #1.3
squares :: Int -> Command
squares 2 = square :> scale 0.9 square
squares 3 = square :> scale 0.9 (square :> scale 0.9 square)
squares n = square :> scale 0.9 (squares (n-1))

scale :: Double -> Command -> Command
scale s (Fd z) = Fd (s * z)
scale s (Bk z) = Bk (s * z)
scale s (p :> q) = scale s p :> scale s q
scale s command = command

-- TODO #1.4
repscale :: Int -> Double -> Command -> Command
repscale = undefined

hexagons :: Int -> Command
hexagons n = repscale n 0.8 hexagon


-----------------------------------------------------------
-- Part 2
-----------------------------------------------------------
daisy :: [Double] -> Command
daisy xs = Lt 90 :> foldr cons empty (map (Go . Fd) xs)
  where cons x y = x :> Rt arc :> y
        empty    = Fd 0
        arc = 180 / fromIntegral (length xs - 1)

data Tree a
  = Tip
  | Node (Tree a) a (Tree a)
  deriving Show

-- TODO #2.1
instance Functor Tree where
  -- fmap :: (a -> b) -> Tree a -> Tree b
  fmap = undefined

-- TODO #2.2
foldTree :: b -> (b -> a -> b -> b) -> Tree a -> b
foldTree = undefined

-- TODO #2.3
fibTree :: Int -> Tree Int
fibTree = undefined

-- TODO #2.4
drawTree :: Double -> Tree Int -> Command
drawTree d = foldTree tip node
  where
    tip :: Command
    tip        = undefined
    node :: Command -> Int -> Command -> Command
    node l x r = undefined

-----------------------------------------------------------
-- Part 3
-----------------------------------------------------------

koch :: Int -> Command
koch 0 = Fd 1
koch n = scale (1/3) (koch (n-1)) :> Lt 60
      :> scale (1/3) (koch (n-1)) :> Rt 120
      :> scale (1/3) (koch (n-1)) :> Lt 60
      :> scale (1/3) (koch (n-1))

-- TODO #3.1
kochflake :: Int -> Command
kochflake n = undefined

-- TODO #3.2
lsystem :: Int -> Double -> [String] -> String -> Command
lsystem 0 d rs r       = Fd 1
lsystem n d rs []      = Fd 0
lsystem n d rs ('+':r) = undefined
lsystem n d rs (c:r)   = undefined

ix :: Char -> Int
ix c = ord c - ord '0'


-----------------------------------------------------------
-- WARNING: Deep magic ahead
-----------------------------------------------------------
-- Jeremy Gibbons' amazing spigot implementation:
pis = g(1,0,1,1,3,3) where
  g (q,r,t,k,n,l) =
   if 4*q+r-t < n*t
    then n : g (10*q, 10*(r-n*t), t, k, div (10*(3*q+r)) t - 10*n, l)
    else g (q*k, (2*q+r)*l, t*l, k+1, div (q*(7*k+2)+r*l) (t*l), l+2)
