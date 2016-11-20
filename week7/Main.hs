module Main where

import qualified Graphics.Rendering.OpenGL as GL
import qualified Graphics.UI.GLUT as GL
import Graphics.UI.GLUT (($=))
import Data.List
import Data.Function
import System.Exit

import Turtle
import Answer

main :: IO ()
main = do
  GL.initialWindowSize $= GL.Size 600 600
  (_, args) <- GL.getArgsAndInitialize
  GL.initialDisplayMode $= [GL.DoubleBuffered, GL.RGBAMode, GL.WithAlphaComponent]
  w <- GL.createWindow "Turtle"
  GL.lineSmooth $= GL.Enabled
  GL.hint GL.LineSmooth $= GL.Nicest

  let command = case args of
                  []                -> cursor
                  ["square"]        -> square
                  ["triangle"]      -> triangle
                  ["hexagon"]       -> hexagon
                  ["polygon",n]     -> polygon (read n)
                  ["squares",n]     -> squares (read n)
                  ["hexagons",n]    -> hexagons (read n)
                  ["kochflake",n]   -> kochflake (read n)
                  ["koch",n]        -> Rt 90 :> koch (read n)
                  ["daisy",n]       -> daisy (take (read n) (map fromIntegral pis))
                  ["fib",d,n]       -> drawTree (read d) (fibTree (read n))
                  "lsystem":n:d:rsr -> Rt 90 :> lsystem (read n) (read d) (init rsr) (last rsr)
                  _               -> error ("Invalid commandline args: " ++ show args)

  GL.displayCallback  $= display command
  GL.keyboardCallback $= Just keyboard
  GL.reshapeCallback  $= Just reshape
  GL.mainLoop

keyboard '\27' _ = exitSuccess
keyboard 'q'   _ = exitSuccess
keyboard _     _ = return ()

display :: Command -> IO ()
display command = do
  GL.clear [GL.ColorBuffer]
  GL.loadIdentity

  GL.blend $= GL.Enabled
  GL.blendFunc $= (GL.SrcAlpha, GL.OneMinusSrcAlpha)

  let (turtle', path) = walk initTurtle [[pos initTurtle]] command
  zoom (concat path)

  GL.lineWidth $= 1.0

  GL.color (GL.Color4 255 255 255 255 :: GL.Color4 GL.GLubyte)
  mapM_ line (reverse (map reverse path))

  let (turtle'', path') = walk turtle' [[pos turtle']] cursor

  GL.lineWidth $= 2.0
  GL.color (GL.Color4 145 210 144 255 :: GL.Color4 GL.GLubyte)
  mapM_ line (reverse (map reverse path'))

  GL.swapBuffers

zoom :: [(Double, Double)] -> IO ()
zoom ps = do
  GL.matrixMode $= GL.Projection
  GL.loadIdentity
  GL.ortho (midX - size2) (midX + size2) (midY - size2) (midY + size2) 1 0
  where
    minX = realToFrac ((minimum . map fst) ps)
    maxX = realToFrac ((maximum . map fst) ps)
    midX = (minX + maxX) / 2

    minY = realToFrac ((minimum . map snd) ps)
    maxY = realToFrac ((maximum . map snd) ps)
    midY = (minY + maxY) / 2

    width2 = (maxX - minX) / 2
    height2 = (maxY - minY) / 2

    size2 = 1.1 * (max width2 height2)

vertex :: Pos -> IO ()
vertex (x, y) = GL.vertex (GL.Vertex3 (realToFrac x) (realToFrac y) (0 :: GL.GLfloat))

line :: [Pos] -> IO ()
line xs = GL.renderPrimitive GL.LineStrip (mapM_ vertex xs)

reshape :: GL.ReshapeCallback
reshape size = GL.viewport $= (GL.Position 0 0, size)