module Turtle where

type Pos = (Double, Double)
type Path = [[Pos]]

data Turtle = Turtle
  { ang :: Double
  , pos :: Pos
  }
  deriving Show

data Command
  = Fd Double
  | Bk Double
  | Lt Double
  | Rt Double
  | Go Command
  | Command :> Command
  deriving Show

infixr 4 :>

initTurtle :: Turtle
initTurtle = Turtle 90 (0,0)

defaultCommand :: Command
defaultCommand = Fd 0.40 :> Lt 30 :> Fd 0.40

walk :: Turtle -> Path -> Command -> (Turtle, Path)
walk (Turtle ang (x,y)) (ps:pss) (Fd z) = (Turtle ang (x',y') , ((x',y'):ps):pss)
  where x' = x + z * cos (ang * 2 * pi / 360)
        y' = y + z * sin (ang * 2 * pi / 360)
walk (Turtle ang (x,y)) (ps:pss) (Bk z) = (Turtle ang (x',y') , ((x',y'):ps):pss)
  where x' = x - z * cos (ang * 2 * pi / 360)
        y' = y - z * sin (ang * 2 * pi / 360)
walk (Turtle ang pos) pss (Lt delta) = (Turtle (ang + delta) pos , pss)
walk (Turtle ang pos) pss (Rt delta) = (Turtle (ang - delta) pos , pss)

walk turtle pss (Go c)    = (turtle, [pos turtle]:pss')
  where (turtle', pss')   = walk turtle pss c
walk turtle pss (c :> c') = (turtle'', pss'')
  where (turtle', pss')   = walk turtle pss c
        (turtle'', pss'') = walk turtle' pss' c'
walk _ _ c = error ("walk: " ++ show c)
