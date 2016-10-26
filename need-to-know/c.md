# Weeks 0-4 Need to Know: C

It appears from weeks 0-4 the lectures on C covered the basics of the C language, the C99 standard & programming practices and techniques.

Pointers were hinted at and mentioned where relevant, but not explored.

Three lectures with intermediate concepts & need to knows:

1. Arrays
2. Structures
3. Input/Output (IO)

## Arrays

- passing arrays

  - no way to find the length of an array in C

- strings and ascii

- the `EOS` char `'\0''`

- memory allocation for strings - **always allocate length + 1** (make room for EOS)

## Structures

- structure declaration
- passed by value by default, but can pass by reference also
- demonstrated traversing struct pointers and fields
- introduced `Typedef` - defines a type synonym

## Input and Output

- types of input:

  1. CLA
  2. stdin
  3. files

- special characters - assume everything will have an effect

- introduced the idea of 'multi-word' words (arguments with a space in the middle)

- `EOF` and `feof` behaviour

  - need an extra call to fgetc than there are characters in the file

- `sscanf` - read and interpret data

- removing new lines at end of string

- dont use `fscanf`

- end **STDIN** with `ctrl + D`
- `fgets` - read lines from `stdin`
- don't use `gets` because there is no size-checking of the input array, which is a security hole
- writing characters to a file
