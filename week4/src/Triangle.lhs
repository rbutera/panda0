Functional Programming Assignment 1: Triangle
=============================================

This practical exercise is designed to get you used to some of the
syntax of Haskell, and to help you familiarise yourself with
GHC and GHCi.

Preamble
--------

This file is a module that provides functions that process
triangles. To work on this lab you will need to download:

* [Main.lhs](Main.lhs)
* [Triangle.lhs](Triangle.lhs)

The `Main.lhs` file contains code to create an executable that will run
and test your code. You should not modify `Main.lhs`, but you're
welcome to look at what's there.
The `Triangle.lhs` file contains the code that generated this
document, and is where you should modify and add code.
To submit your code for this assignment, you need only upload
`Triangle.lhs`: I'll be using a custom `Main.lhs` that will test your
code more thoroughly than the one I'm giving you.

Since this file is a module, we declare it on the following line.

> module Triangle where

Triangle Classifier
-------------------

Here's the table of different triangle types:

Triangle        Description
---------       ------------
Illegal         any length is not positive
Impossible      lengths do not add up
Flat            no area
Equilateral     three sides are equal
Isosceles       two sides are equal
Right           has a right angle
Scalene         no two sides equal

Part of the result of executing our program on input lengths is to
print a string that says what kind of triangle was detected according
to this table.

Note that some triangles could fit into more than one category.
For instance, certain right angled triangles are also isosceles, and
certain flat triangles are also scalene. Let's resolve this by saying
that triangles are categorised with the precedence set
by the table above. In other words, a flat scalene triangle
will be considered just flat, and a right angled isosceles is
considered to be just an isosceles.

In the previous lab we output the result as a string. In this lab we'll
be more precise by making sure that only allowable triangle types
can be output. The lines below create a new data type called
`Triangle`, and the data type is created by the so-called
*constructors* that are listed here:

> data Triangle
>   = Equilateral
>   | Isosceles
>   | Scalene
>   | RightAngled
>   | Flat
>   | Illegal
>   | Impossible
>   deriving (Eq, Show)

The advantage of creating a custom data type like this is that you
protect yourself from silly mistakes such as typing the wrong
name: if you type `Isoceles` instead of `Isosceles`, the compiler will
detect this as an error.

The last line of the declaration has `deriving (Eq, Show)`. This tells
Haskell that we want to be able to compare these constructors for
equality, and that we'd also like to be able to print them to the screen.

Although you are probably reading an HTML version of this file,
you should spend your time editing the [Triangle.lhs](Triangle.lhs) version,
which can also be compiled.

***
**TODO:** Download [Main.lhs](Main.lhs) and
[Triangle.lhs](Triangle.lhs) and compile with:

    $ ghc Main
    [1 of 2] Compiling Triangle         ( Triangle.lhs, Triangle.o )
    [2 of 2] Compiling Main             ( Main.lhs, Main.o )
    Linking Main ...

***

By default this searches for a file named `Main.hs` or `Main.lhs`,
and compile it into a binary called `Main`. Since `Main.lhs` imports
`Triangle.lhs`, that also gets found and compiled. You can execute
the resulting binary in your console with the command `./Main`.

***
**TODO:** Execute `Main` with arguments:

    $ ./Main 3 3 3
    Equilateral

**TODO:** Execute `Main` without arguments:

    $ ./Main
    Tests passed: 5
    Tests failed: 35
    Expected: (15,15,13,Isosceles), Actual: Impossible
    ...

***
The output of executing `Main` without arguments is the result of running
the `triangle` function on 40 tests. The number of passed tests is shown,
as is the number of failures. Each of the failures is then listed.
The result of the exercises is also shown.

Instead of compiling, you can also *interpret* the `Main.lhs` file in GHCi.
Using GHCi is a useful way of inspecting functions and understanding your
functions. In the example below, we first check the output of `triangle 15 15 13`,
and then that of `triangle 3 3 3`, and we do not have to recompile in between.
Note, however, that if the source file `Main.lhs` or `Triangle.lhs` is modified,
then we need to reload the files with `:r`.

***
**TODO:** Interpret Main.lhs in GHCi and try some examples:

    $ ghci
    GHCi> :l Main
    [1 of 2] Compiling Triangle         ( Triangle.lhs, interpreted )
    [2 of 2] Compiling Main             ( Main.lhs, interpreted )
    Ok, modules loaded: Main, Triangle.
    GHCi> triangle (15, 15, 13)
    Impossible
    GHCi> triangle (3, 3, 3)
    Equilateral

***
Perhaps confusingly, the interpreter first compiles the code for itself before
allowing you to type commands. This is not the same as when you
compile code yourself: a binary does not get created by the
interpreter GHCi.

We'll be using the `Integer` data type to store the lengths of the
edges: these are integers with arbitrary precision, so you don't have
to worry about overflowing values that are too large.

Since our triangles will be represented by triples of integer values,
we'll create a type synonym called `Triple` that will save us the
hassle of typing `(Integer, Integer, Integer)` all the time.

> type Triple = (Integer, Integer, Integer)

Whenever you see `Triple`, this is equivalent to `(Integer, Integer, Integer)`.

The following function implements the `triangle` function.
The type signature tells us that it takes a `Triple`
and produces a `Triangle`. Since a `Triple` is just
another way of writing `(Integer, Integer, Integer)`,
we can pattern match on `(a, b, c)`.
The code for detecting an `Equilateral` is already present,
and it's your task to complete the definition so that all the tests
pass.

> -- TODO: Complete this function!
> triangle :: Triple -> Triangle
> triangle (a, b, c)
>   | a == b && b == c = Equilateral
>   | otherwise        = Impossible

Notice that here we are using a pattern guard, which allows us to put
predicates on the left hand side of the defining equality symbol.
Pattern guards are an alternative to using `if` statements.
Using guards in definitions usually results in concise code
that is easy to understand.
The pattern guards are evaluated from top to bottom. The first line
with a true guard is returned.

The `triangle` function can be completed using only pattern guards, addition and
multiplication, as well as the following operations:

< (&&) :: Bool -> Bool -> Bool
< (||) :: Bool -> Bool -> Bool
< not  :: Bool -> Bool
< (==) :: Eq a => a -> a -> Bool
< (/=) :: Eq a => a -> a -> Bool

Note that testing when two things are not equal is written `x /= y` in
Haskell, which is slightly different to the `x != y` in C.

You can test your function by compiling and executing `./Main` as
described earlier. It might also help to interpret your `triangle`
function with various parameters to see if it does what you expect.


Infinitely Many Triangles
-------------------------

We've been dealing with individual triangles so far.
Now let's start working with the infinite list of all triangles
with integral length sides.

First, we'll define an infinite list of triplets of `Integer` values.

> triples :: [Triple]
> triples = [ (a, b-a, n-b) | n <- [0 .. ] , a <- [0 .. n] , b <- [a .. n] ]

This is an example of a list comprehension. It generates an infinite
list of triples, where each triple `(u, v, w)` is listed in order
such that `u + v + w = n`. You can calculate this, since `u + v + w =
a + (b-a) + (n-b) = n`.
The comprehension first generates all of the values of `n` from `0` to
infinity, and for each `n`, we produce an `a` between `0` and `n`, and
for each `a` we produce a `b` between `a` and `n`.

If you try to evaluate `triples` in GHCi, you'll be asking for infinite output.
It's fun to give that a go, so long as you remember to press `Ctrl-C` to tell
GHCi when you've had enough!

***
**TODO:** Evaluate triples in GHCi (and press Ctrl-C to stop it!)

    GHCi> triples
    [(0,0,0),(0,0,1),(0,1,0),(1,0,0),(0,0,2),(0,1,Interrupted.

***

Although that was fun, it's more practical to take a look at the first few
elements of this list. We can do this with the `take` command:

< take :: Int -> [a] -> [a]

The result of `take n xs` is to return the first `n` elements in the list `xs`.

***
**TODO:** Take the first 10 elements of triples

    GHCi> take 10 triples
    [(0,0,0),(0,0,1),(0,1,0),(1,0,0),(0,0,2),(0,1,1),(0,2,0),(1,0,1),(1,1,0),(2,0,0)]

***

Now what if we wanted to have triangles instead? Well, we can define
a function `triangles` that does this for us:

> triangles :: [Triple]
> triangles = filter isTriangle triples

This works by using a `filter` applied to `triples`. The `filter` function
has this signature:

< filter :: (a -> Bool) -> [a] -> [a]

The result of `filter p xs` is a list whose elements are from `xs` such
that the predicate `p` holds for each element.

For `triangles`, we've used `isTriangle`, which is defined below:

> isTriangle :: Triple -> Bool
> isTriangle t = not (triangle t == Impossible) --TODO: Fix this. 

The `isTriangle` function checks if an incoming triple is an
impossible triangle. It might seem that this works, but it's not quite
enough. We're also allowing triples that are `Illegal`. You'll have
to fix the definition of `isTriangle` to deal with this case as well.
Flat triangles should be allowed.

***
**TODO:** Fix the `isTriangle` function so that no `Illegal` triangles
come through when `triangles` is evaluated.

***

One thing we can do with our list of triangles is turn it into a list of
`Triangle`s. We can use our already defined `triangle` function and `map` it
across the list.

< map :: (a -> b) -> [a] -> [b]

The result of `map f xs` is a list where each element in `xs` has had `f`
applied to it.

***
**TODO:** Use map and triangle to find out the kinds of triangles we got

    GHCi> map triangle triangles

***
This obviously returns an infinite list, so don't forget to `Ctrl-C`.
You might also want to use `take` to look at the first few entries.

To take the first 1000 elements of this list you can apply the `take`
function to the list:

***
**TODO:** Use map and triangle to find out the kinds of triangles we got
from the first 1000 triangles

    GHCi> take 1000 (map triangle triangles)

***
Notice that the second argument to `take` is the list that results from
`map triangle triangles`. In general, we can chain functions together
to get interesting results out.



Ok, now for something a bit more interesting. How many `Isosceles` triangles
are there in the first `n` triangles we produce?

First, you'll find it useful to define a function called
`isIsosceles`, that determines if a triple is an isosceles.

***
**TODO:**
Fix the following function:

> isIsosceles :: Triple -> Bool
> isIsosceles t = True  -- TODO: this should return true only when the triangle that t represents is isosceles

***
You can use `isIsosceles` as the first parameter of `filter`, so that `filter
isIsosceles xs` will filter out the list `xs` so that it contains only
isosceles triples.

So now we should have enough ingredients to answer our original
question: how many `Isosceles` triangles
are there in the first `n` triangles we produce?

***
**TODO:**
Modify ex1 so that it outputs the number of isosceles triangles in the first
n triangles produced by `triangles`. You should build this out of the
functions we have defined so far.

> ex1 :: Int -> Int
> ex1 n = 0 -- TODO: Should produce the number of Isosceles triangles in the first n triangles

**HINT:** It would help to make use of the function `length`, as well
as the `filter` function on lists we introduced.

< length :: [a] -> Int

This returns the length of an incoming list.

***

**NOTE:** If you run the `main` function in `Main` (or execute a compiled
`./Main`), then the testing rig will tell you if the answer you
are producing is correct when `n = 1000`. This should help you work
out if you're on the right lines.

Area
----

We'd like to have a function that works out the area of our triangles.
A good formula to use here is [Heron's formula](https://en.wikipedia.org/wiki/Heron%27s_formula).
Given edges $a$, $b$, and $c$, then the area $A$ is:
$$ A = \sqrt{ s (s-a) (s-b) (s-c)} $$
where 
$$s = \frac{a+b+c}{2}.$$

The following code is an attempt at starting the
implementation, but it looks like whoever did it gave
up too early.

> area :: Triple -> Double
> area (ia, ib, ic) = s * (s - a)  -- TODO: Finish this off!
>   where (a, b, c) = (fromInteger ia, fromInteger ib, fromInteger ic)
>         s = (a + b + c) / 2

The values `a`, `b`, and `c` come from correctly
turning the `ia`, `ib` and `ic` from `Integer` values
to `Double`, and `s` is well defined.
However, it looks like there are a number of multiplications missing,
and the `sqrt` function was never applied:

< sqrt :: Double -> Double

This takes the square root of a number.

***
**TODO:** Fix the area function so that it implements Heron's formula.
Make sure it works when the area is supposed to be 0.

**TODO:** Find out the total area of the first `n` triangles,
where the final total area is rounded down with `floor`.

> ex2 :: Int -> Int
> ex2 n = 0

**HINT:** To round down the result, use the `floor` function,
and to sum up a list of values, use the `sum` function. Both of these
are automatically provided.

< floor :: Double -> Int
< sum :: [Double] -> Double

**TODO:** Find out the total area of the first `n` *scalene* triangles,
where the final total area is rounded down with `floor`.

> ex3 :: Int -> Int
> ex3 n = 0

***

Once you're finished and passing all the tests, well done!

Most of you will have completed this exercise by using function
application instead of function composition.
For instance, you will have written things in the form:

    f (g (h x))

this could alternatively be written using composition:

    (f . g . h) x

Have a go at defining alternative versions of the exercises,
such as `ex1' :: Int -> Int`, where you use composition.
Which one looks clearer?

**TODO:** 

Define `ex1'`, `ex2'`, and `ex3'` so that they behave like `ex1`,
`ex2`, and `ex3`, but where they use function composition.

***

Once you're finished, you should ask one of the lab demonstrators to
look at your code: passing the tests is not the only mark of a good
piece of code, and they may make suggestions for improvement.
