#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./display.h"
#include <string.h> // TODO: check if this is OK

#ifndef DEBUG
  #define DEBUG 2
#endif

#ifndef IMPORT_MAX_INSTRUCTIONS
  #define IMPORT_MAX_INSTRUCTIONS 1024
#endif
// TODO: upgrade the run function, adding functions to support it.

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT(...)
#endif

// constants representing possible opcodes (the first two bits of an instruction byte)
const int DX = 0;
const int DY = 1;
const int DT = 2;
const int PEN = 3;

// storing bytes as unsigned chars
typedef unsigned char Byte;

// TODO: try fix enumerated type representing an opcode
// typedef enum {DX, DY, DT, PEN} OpCode;
int largest (int a, int b, int c){
  int largest = 0;

  int sizes[3];
  sizes[0] = a;
  sizes[1] = b;
  sizes[2] = c;

  for (size_t i = 0; i < sizeof(sizes); i++) {
    largest = (largest > sizes[i]) ? largest : sizes[i];
  }

  return largest;
}

// .sketch file move instruction byte
typedef struct MoveInstruction MoveInstruction;
struct MoveInstruction {
  Byte raw; // store a copy of the uninterpreted raw instruction
  // OpCode opcode; // instruction opcode (first 2 bits)
  int opcode; // instruction opcode (first 2 bits) TODO: change to enumerated type
  signed int operand; // instruction operand (last 6 bits)
};

typedef struct PauseInstruction PauseInstruction;
struct PauseInstruction {
  Byte raw; // store a copy of the uninterpreted raw instruction
  // OpCode opcode; // instruction opcode (first 2 bits)
  int opcode; // instruction opcode (first 2 bits) TODO: change to enumerated type
  unsigned int operand; // instruction operand (last 6 bits)
};

typedef struct PenInstruction PenInstruction;
struct PenInstruction {
  Byte raw;
  int opcode;
  //unsigned int operand; // TODO: check operand is always ignored/insignificant
};

int calcInstructionSize () {
  int result = 0;
  int moveSize = sizeof(MoveInstruction) + 1;
  int pauseSize = sizeof(PauseInstruction) + 1;
  int penSize = sizeof(PenInstruction) + 1;
  result = largest(moveSize, pauseSize, penSize);
  return result;
}



void printBits(size_t const size, void const* const toPrint){
  //TODO: remove before submission
  unsigned char *b = (unsigned char*) toPrint;
  unsigned char byte;
  int i, j;

  for (i=size-1;i>=0;i--)
  {
    for (j=7;j>=0;j--)
    {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    }
  }
  puts("");
}

void printBitsNL (Byte toPrint){
  printBits(1, &toPrint);
  printf("\n");
}

/**
* checks if a byte's operand is positive
* @param  instruction the full instruction byte
* @return             [description]
*/
_Bool operandByteHasPositive (Byte instruction){
  if (instruction>>2 & 1) {
    return false;
  } else {
    return true;
  }
}

char operandPolarity (Byte x){
  return (operandByteHasPositive(x) ? '+' : '-');
}

signed int operandExtract (Byte input, _Bool signedOperand){
  _Bool needsFlipping = signedOperand && !operandByteHasPositive(input); // need to flip negatives from two's complement form
  if (needsFlipping == true) {
    DEBUG_PRINT("operand needs flipping because it is %c\n", operandPolarity(input));

    input = input<<2;
    input = ~input;
    input += 1;
    input = input>>2;
    return -input;
  } else {
    return input & 0x3f;
  }
}

int opcodeExtract (Byte input){
  Byte masked = input & 0xC0;
  return masked >> 6;
}

// TODO: remove before submission
// void printPosNeg (Byte testing){
//   printf("0x%02hhx is %c\n", testing, operandPolarity(testing));
// }

// char *opcodeStringify (int code, char *destination) {
char *opcodeStringify (int code) {
  char *result;

  switch (code) {
    case 0:
    result = "DX";
    break;
    case 1:
    result = "DY";
    break;
    case 2:
    result = "DT";
    break;
    case 3:
    result = "PEN";
    break;
    default:
    result = "ERROR";
    break;
  }

  return result;
}

/**
* read bytes from (already opened) in file, unpack each byte into an opcode and operand, and use those to make suitable calls to display functions
* @param  *in file to read
* @param  d  display to call functions to
* @return    [description]
*/
int getInstructions(FILE *in, display *d, int *buffer) {
  int input = fgetc(in);
  int numInstructions = 0;

  DEBUG_PRINT("Loading:\n\n");

  while (input != EOF && input != '\0' && numInstructions < IMPORT_MAX_INSTRUCTIONS) {
    buffer[numInstructions++] = input;
    DEBUG_PRINT("0x%02hhx ", (Byte) input);
    input = fgetc(in);
  }

  DEBUG_PRINT("\n\n%i instructions loaded.\n", numInstructions);
  return 0;
}

int *transformInstructions (int *inputStream, int *outputStream) {
  // traverse inputStream whilst there is data
  for (size_t i = 0; i <= sizeof(inputStream); i++) {
    int input = inputStream[i];

    if (input != '\0' && input != EOF) {
      outputStream[i] = (Byte) input;
    } else {
      DEBUG_PRINT("reached end of inputStream\n");
      break;
    }
  }

  return outputStream;
}

// Read sketch instructions from the given file.  If test is NULL, display the
// result in a graphics window, else check the graphics calls made.
void run(char *filename, char *test[]) {
  int instructionMemorySize = calcInstructionSize();
  DEBUG_PRINT("instruction block size: %i\n", instructionMemorySize);

  int buffer[IMPORT_MAX_INSTRUCTIONS];
  Byte instructions[IMPORT_MAX_INSTRUCTIONS];


  FILE *in = fopen(filename, "rb");
  if (in == NULL) {
    fprintf(stderr, "Can't open %s\n", filename);
    exit(1);
  }
  display *d = newDisplay(filename, 1024, 1024, test);

  getInstructions(in, d, buffer);
  transformInstructions(buffer, instructions);
  end(d);
  fclose(in);
}

// ----------------------------------------------------------------------------
// Nothing below this point needs to be changed.
// ----------------------------------------------------------------------------

// Forward declaration of test data.
char **lineTest, **squareTest, **boxTest, **oxoTest, **diagTest, **crossTest,
**clearTest, **keyTest, **pausesTest, **fieldTest, **lawnTest;

void testSketches() {
  // Stage 1
  run("line.sketch", lineTest);
  run("square.sketch", squareTest);
  run("box.sketch", boxTest);
  run("oxo.sketch", oxoTest);

  // Stage 2
  run("diag.sketch", diagTest);
  run("cross.sketch", crossTest);

  // Stage 3
  run("clear.sketch", clearTest);
  run("key.sketch", keyTest);

  // Stage 4
  run("pauses.sketch", pausesTest);
  run("field.sketch", fieldTest);
  run("lawn.sketch", lawnTest);
}

int main(int n, char *args[n]) {
  if (n == 1) testSketches();
  else if (n == 2) run(args[1], NULL);
  else {
    fprintf(stderr, "Usage: sketch [file.sketch]");
    exit(1);
  }
}

// Each test is a series of calls, stored in a variable-length array of strings,
// with a NULL terminator.

// The calls that should be made for line.sketch.
char **lineTest = (char *[]) {
  "line(d,30,30,60,30)", NULL
};

// The calls that should be made for square.sketch.
char **squareTest = (char *[]) {
  "line(d,30,30,60,30)", "line(d,60,30,60,60)",
  "line(d,60,60,30,60)","line(d,30,60,30,30)", NULL
};

// The calls that should be made for box.sketch.
char **boxTest = (char *[]) {
  "line(d,30,30,32,30)", "pause(d,10)", "line(d,32,30,34,30)", "pause(d,10)",
  "line(d,34,30,36,30)", "pause(d,10)", "line(d,36,30,38,30)", "pause(d,10)",
  "line(d,38,30,40,30)", "pause(d,10)", "line(d,40,30,42,30)", "pause(d,10)",
  "line(d,42,30,44,30)", "pause(d,10)", "line(d,44,30,46,30)", "pause(d,10)",
  "line(d,46,30,48,30)", "pause(d,10)", "line(d,48,30,50,30)", "pause(d,10)",
  "line(d,50,30,52,30)", "pause(d,10)", "line(d,52,30,54,30)", "pause(d,10)",
  "line(d,54,30,56,30)", "pause(d,10)", "line(d,56,30,58,30)", "pause(d,10)",
  "line(d,58,30,60,30)", "pause(d,10)", "line(d,60,30,60,32)", "pause(d,10)",
  "line(d,60,32,60,34)", "pause(d,10)", "line(d,60,34,60,36)", "pause(d,10)",
  "line(d,60,36,60,38)", "pause(d,10)", "line(d,60,38,60,40)", "pause(d,10)",
  "line(d,60,40,60,42)", "pause(d,10)", "line(d,60,42,60,44)", "pause(d,10)",
  "line(d,60,44,60,46)", "pause(d,10)", "line(d,60,46,60,48)", "pause(d,10)",
  "line(d,60,48,60,50)", "pause(d,10)", "line(d,60,50,60,52)", "pause(d,10)",
  "line(d,60,52,60,54)", "pause(d,10)", "line(d,60,54,60,56)", "pause(d,10)",
  "line(d,60,56,60,58)", "pause(d,10)", "line(d,60,58,60,60)", "pause(d,10)",
  "line(d,60,60,58,60)", "pause(d,10)", "line(d,58,60,56,60)", "pause(d,10)",
  "line(d,56,60,54,60)", "pause(d,10)", "line(d,54,60,52,60)", "pause(d,10)",
  "line(d,52,60,50,60)", "pause(d,10)", "line(d,50,60,48,60)", "pause(d,10)",
  "line(d,48,60,46,60)", "pause(d,10)", "line(d,46,60,44,60)", "pause(d,10)",
  "line(d,44,60,42,60)", "pause(d,10)", "line(d,42,60,40,60)", "pause(d,10)",
  "line(d,40,60,38,60)", "pause(d,10)", "line(d,38,60,36,60)", "pause(d,10)",
  "line(d,36,60,34,60)", "pause(d,10)", "line(d,34,60,32,60)", "pause(d,10)",
  "line(d,32,60,30,60)", "pause(d,10)", "line(d,30,60,30,58)", "pause(d,10)",
  "line(d,30,58,30,56)", "pause(d,10)", "line(d,30,56,30,54)", "pause(d,10)",
  "line(d,30,54,30,52)", "pause(d,10)", "line(d,30,52,30,50)", "pause(d,10)",
  "line(d,30,50,30,48)", "pause(d,10)", "line(d,30,48,30,46)", "pause(d,10)",
  "line(d,30,46,30,44)", "pause(d,10)", "line(d,30,44,30,42)", "pause(d,10)",
  "line(d,30,42,30,40)", "pause(d,10)", "line(d,30,40,30,38)", "pause(d,10)",
  "line(d,30,38,30,36)", "pause(d,10)", "line(d,30,36,30,34)", "pause(d,10)",
  "line(d,30,34,30,32)", "pause(d,10)", "line(d,30,32,30,30)", "pause(d,10)",
  NULL
};

// The calls that should be made for box.sketch.
char **oxoTest = (char *[]) {
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "line(d,30,40,60,40)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "line(d,30,50,60,50)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "line(d,40,30,40,60)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "line(d,50,30,50,60)", NULL
};

// The calls that should be made for diag.sketch.
char **diagTest = (char *[]) {
  "line(d,30,30,60,60)", NULL
};

// The calls that should be made for cross.sketch.
char **crossTest = (char *[]) {
  "line(d,30,30,60,60)", "line(d,60,30,30,60)", NULL
};

// The calls that should be made for clear.sketch.
char **clearTest = (char *[]) {
  "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
  "line(d,50,30,50,60)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "clear(d)", "line(d,30,30,60,60)",
  "line(d,60,30,30,60)", NULL
};

// The calls that should be made for key.sketch.
char **keyTest = (char *[]) {
  "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
  "line(d,50,30,50,60)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
  "pause(d,63)", "pause(d,63)", "key(d)", "clear(d)", "line(d,30,30,60,60)",
  "line(d,60,30,30,60)", NULL
};

// The calls that should be made for diag.sketch.
char **pausesTest = (char *[]) {
  "pause(d,0)", "pause(d,0)", "pause(d,127)", "pause(d,128)", "pause(d,300)",
  "pause(d,0)", "pause(d,71469)", NULL
};

// The calls that should be made for field.sketch.
char **fieldTest = (char *[]) {
  "line(d,30,30,170,30)", "line(d,170,30,170,170)",
  "line(d,170,170,30,170)", "line(d,30,170,30,30)", NULL
};

// The calls that should be made for field.sketch.
char **lawnTest = (char *[]) {
  "cline(d,30,30,170,30,16711935)", "cline(d,170,30,170,170,16711935)",
  "cline(d,170,170,30,170,16711935)", "cline(d,30,170,30,30,16711935)",
  NULL
};