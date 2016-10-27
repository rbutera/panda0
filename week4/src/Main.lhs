Functional Programming Assignment 1: Main
=========================================

Functions in this file are used to generate the tests used for
the lab. You're welcome to have a look around, but not expected
to understand what's going on in this corner of the world.

Main
----

Since we will be compiling this file into a binary file for execution,
it will include a `main` function as the entry point for the program,
and this file is also a `Main` module, which we declare as follows:

> module Main where

There are a number of library functions that we will be importing,
so we do that with the following statements:

> import Triangle
> import Data.Maybe
> import Control.Monad
> import System.Environment
> import Data.List

You don't need to know what these do at this point, other than that
they provide various functions that are used later on.

> main :: IO ()
> main = do
>   args <- getArgs
>   case args of
>     [] ->
>       do let (pass, fail) = (partition isNothing . map check) tests
>          putStrLn ("Tests")
>          putStrLn ("* Passed: " ++ (show . length) pass)
>          putStrLn ("* Failed: " ++ (show . length) fail)
>          when (length fail > 0)
>            (mapM_ (putStrLn . showFail . fromJust) fail)

>          putStrLn "Exercises"
>          mapM_ (putStrLn . verify) solutions

>     as:bs:cs:_ -> case parse as bs cs of
>       Nothing        -> putStrLn (show Impossible)
>       Just t  -> putStrLn (show (triangle t))
>     _         -> putStrLn "Triangle takes three arguments: ./Triangle 3 4 5"

> parse :: String -> String -> String -> Maybe Triple
> parse as bs cs = case (reads as, reads bs, reads cs) of
>   ([(a,"")],[(b,"")],[(c,"")]) -> Just (a, b, c)
>   _                            -> Nothing

> verify :: (String, Int, Int) -> String
> verify (exn, ex, sol) = "* " ++ exn ++
>   if (ex == sol)
>     then ": passes test"
>     else ": incorrect, expected " ++ show sol ++ " but got " ++ show ex

These are the solutions to the exercises where n = 1000.
Your final submission will be tested more rigorously.

> solutions :: [(String, Int, Int)]
> solutions = [("ex1 1000", ex1 1000, 231), ("ex2 1000", ex2 1000, 11675), ("ex3 1000", ex3 1000, 23085)]

> check :: (Triple, Triangle) -> Maybe (Triple, Triangle, Triangle)
> check (t, s)
>   | s /= s'   = Just (t, s, s')
>   | otherwise = Nothing
>   where s' = triangle t
> 
> showFail :: (Triple, Triangle, Triangle) -> String
> showFail (t, s, s') = "Expected: " ++ show (t, s) ++ ", Actual: "  ++ show s'

These are the tests that get executed.

> -- There are 40 tests to pass.
> tests :: [(Triple, Triangle)]
> tests =
>   [ ((1073, 1073, 1073), Equilateral)
>   , ((15, 15, 13), Isosceles)
>   , ((15, 13, 15), Isosceles)
>   , ((13, 15, 15), Isosceles)
>   , ((25, 25, 27), Isosceles)
>   , ((25, 27, 25), Isosceles)
>   , ((27, 25, 25), Isosceles)
>   , ((3, 4, 5), RightAngled)
>   , ((5, 12, 13), RightAngled)
>   , ((5, 13, 12), RightAngled)
>   , ((12, 5, 13), RightAngled)
>   , ((12, 13, 5), RightAngled)
>   , ((13, 5, 12), RightAngled)
>   , ((13, 12, 5), RightAngled)
>   , ((12, 14, 15), Scalene)
>   , ((12, 15, 14), Scalene)
>   , ((14, 12, 15), Scalene)
>   , ((14, 15, 12), Scalene)
>   , ((15, 12, 14), Scalene)
>   , ((15, 14, 12), Scalene)
>   , ((7, 9, 16), Flat)
>   , ((7, 16, 9), Flat)
>   , ((16, 7, 9), Flat)
>   , ((16, 9, 7), Flat)
>   , ((8, 4, 4), Flat)
>   , ((1, 1, 5) , Impossible)
>   , ((2, 3, 13), Impossible)
>   , ((2, 13, 3), Impossible)
>   , ((13, 2, 3), Impossible)
>   , ((0, 0, 0), Illegal)
>   , ((0, 10, 12), Illegal)
>   , ((10, 0, 12), Illegal)
>   , ((10, 12, 0), Illegal)
>   , ((-1, -1, -1), Illegal)
>   , ((-1, 10, 12), Illegal)
>   , ((10, -1, 12), Illegal)
>   , ((10, 12, -1), Illegal)
>   , ((1100000000,1705032704,1805032704),Scalene)
>   , ((2000000001,2000000002,2000000003),Scalene)
>   , ((150000002,666666671,683333338),Scalene)
>   ]
