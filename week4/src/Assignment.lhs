Functional Programming Assignment 1
===================================
In this assignment your task is to understand basic types and
functions in Haskell, as well as to gain an understanding of how to
use the ghc compiler and ghci interpreter.

The assignment consists of the following files,
please finish reading the whole of this document before looking at the
others!
**NOTE:** This assignment is designed to teach you as you go through
the files in order: make sure you've read everything that precedes a
task before attempting it!

* [Assignment.html](Assignment.html) ([source](Assignment.lhs)) (this file)
* [Triangle.html](Triangle.html) ([source](Triangle.lhs))
* [Main.html](Main.html) ([source](Main.lhs))

This assignment is not assessed. If you would like feedback on what
you come up with, ask a lab assistant.


Tutorial
========

This tutorial section is to help you get started with programming in
Haskell. There is nothing in this section that is assessed, but
following along will help you in your later tasks.

Text Editor
-----------

You will need a text editor to modify source files that will then be
compiled and executed in the terminal. If you already have your
favourite editor, then just use that. If you're unsure, then I
recommend you start with atom:

* [https://atom.io/](https://atom.io/)

This works best if you also install a Haskell plugin that will do some
syntax highlighting; this will make your code be coloured which helps
with reading. There's a plugin called `language-haskell` that does
this for you; you should drill through the preferences in atom and
install it yourself there.

Source Files
------------

Haskell source files come in two forms. Files that end in `.lhs` are known
as *literate* scripts, and those that end in `.hs` are *illiterate*.
The difference between the two is that in a literate file, all
lines are comments by default and thus ignored by the compiler, except
that those that start with a `> `, called bird tracks. For example,
the following contains the contents of a file called
[Literate.lhs](Literate.lhs):

    ~~~~ Literate.lhs
    > module Literate where

    This is an example of a comment in a `.lhs` file. All lines
    are comments by default. The function `foo` is code because
    the line starts with a `> `.

    > foo :: Int
    > foo = 42

    One thing to watch out for is that code blocks in a literate script
    must have a space before and after the block.
    ~~~~

In an illiterate script, all lines are code by default.
Writing in line comments is done by using `-- comment`, and
a comment block with `{- comment block -}`. Here are the
contents of [Illiterate.hs](Illiterate.hs):

    ~~~~ Illiterate.hs
    module Illiterate where

    {- This is an example of a comment in a `.hs` file. All lines
       are code by default.
    -}
    foo :: Int
    foo = 42  -- inline comments are possible too!
    ~~~~

This assignment is generated from a Haskell source
file, called [Assignment.lhs](Assignment.lhs).

It's good practice for Haskell files to start with a line that
names the module that is being defined. The module name is usually
either `Main`, if the file includes a `main` function, or otherwise
the name of the file itself.
This file is no exception, and so we declare that this module
is called `Assignment` as follows:

> module Assignment where

A module definition must be the first line of code in a Haskell file.


***
**TODO:** Download [Assignment.lhs](Assignment.lhs) and open it in
your text editor. Have a look around, and notice that the first line
of code declares the module name.

***

You'll see that I've sprinkled **TODO** comments around in this file.
These are tasks you'll need to complete to complete the assignment.
You might help it useful to turn those into **DONE** by modifying the
lhs file as you work through, to keep track of what you've
accomplished.

Interpreter
-----------

Haskell source files can be read by GHCi, which is an interpreter. You
can think of this as a very powerful calculator, where you can type
expressions and get back results.
Sometimes this might also be called the *REPL*, which stands for
Read, Evaluate, Print, Loop, since an interpreter will:

* Read a line of code to make an expression
* Evaluate the expression to return a result
* Print the result as a line of text
* Loop back and REPL again

Since this is a Haskell source file, you can open it in GHCi,
and execute its contents.

***
**TODO:**
Run `ghci` in your terminal:

    $ ghci

Load this file using `:l` for *load*:

    GHCi> :l Assignment.lhs

To test if it works, type `hello` in ghci:

    GHCi> hello
    "Hurrah! It works!"

***

The reason you get that output is because I've defined `hello` to be
the following `String`, which gets printed when you execute it in
GHCi. Here is the definition:

> hello :: String
> hello = "Hurrah! It works!"

One of the most important things in Haskell are the *types* of values,
and you can ask GHCi to tell you the type of something by typing `:t`,
followed by the name of the expression you want to know about:

***
**TODO:** Find out the type of `hello`:

    GHCi> :t hello
    hello :: String

***
This tells you that `hello` has type `String`.

When a file GHCi is working with has been modified, GHCi will not be
automatically informed. To inform GHCi, it needs to be *reloaded*.
Here's how you can reload and quit GHCi:

***
**TODO:**
Reload GHCi and its imported files by typing `:r`, for *reload*:
```
GHCi> :r
```
Quit GHCi by typing `:q`, for *quit*:
```
GHCi> :q
Leaving GHCi.
```
***

Now that we have the basics in place, it's time for you to start doing
some coding. Have a look at the other files for this assignment.


A Note on Style
---------------

Good style is something worth cultivating as a programmer: it makes
your code easier to read and debug!
I recommend you follow Johan Tibell's guide to Haskell style here:

* [Haskell Style Guide](https://github.com/tibbe/haskell-style-guide/blob/master/haskell-style.md)

Feel free to disagree with some of the decisions made there, so long
as you are consistent!

