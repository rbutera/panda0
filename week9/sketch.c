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

#define HEXIDECIMAL_FORMAT "0x%02hhx"

// constants representing possible opcodes (the first two bits of an instruction byte)
#define DX 0
#define DY 1
#define DT 2
#define PEN 3
#define CLEAR 4
#define KEY 5
#define COL 6

// storing bytes as unsigned chars
typedef unsigned char Byte;

// typedef enum {DX, DY, DT, PEN} OpCode; // TODO:  enumerated type representing an opcode
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
typedef struct Instruction Instruction;
struct Instruction {
  Byte raw; // store a copy of the uninterpreted raw instruction
  // OpCode opcode; // instruction opcode (first 2 bits)
  int opcode; // instruction opcode (first 2 bits) TODO: change to enumerated type
  union {
    signed int move;
    unsigned int pause;
    _Bool pen;
    _Bool clear;
    _Bool key;
    signed int col;
  }  operand; // instruction operand (last 6 bits)
};

// represents drawing state
typedef struct State State;
struct State {
  display * d;
  int x;
  int y;
  _Bool p;
  int downX;
  int downY;
};

signed int byteToDecimal (Byte input){
  return (signed int) input;
}

char *decimalToBinaryString(signed int input, char *outputStream){
  int bitOffset, bit, outputIndex;
  for (bitOffset = 31; bitOffset >= 0; bitOffset--)
  {
    bit = input >> bitOffset;
    outputIndex = 31 - bitOffset;
    if (bit & 1)
      outputStream[outputIndex] = '1';
    else
      outputStream[outputIndex] = '0';
  }

  return outputStream;
}

// TODO: from http://cboard.cprogramming.com/c-programming/114077-converting-binary-string-decimal.html
int binaryStringToDecimal(const char * str)
{
    int val = 0;

    while (*str != '\0')
    val = 2 * val + (*str++ - '0');
    return val;
}

int printState(State *state){
  char *penState;
  if (state->p == true) {
    penState = "down";
  } else {
    penState = "up";
  }

  DEBUG_PRINT("state: (%i,%i) P: %s\n", state->x, state->y, penState);

  return 0;
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
  Byte copyInstruction = instruction;
  // printBitsNL(copyInstruction);
  copyInstruction <<= 2;
  // printBitsNL(copyInstruction);
  copyInstruction >>= 7;
  // printBitsNL(copyInstruction);

  if (copyInstruction == 1) {
    return false;
  } else {
    return true;
  }
}

char operandPolarity (Byte x){
  return (operandByteHasPositive(x) ? '+' : '-');
}

signed int moveOperandExtract (Byte input){
  _Bool needsFlipping = !operandByteHasPositive(input); // need to flip negatives from two's complement form
  /**
    DEBUG_PRINT(HEXIDECIMAL_FORMAT, input);
    DEBUG_PRINT("\n");
    printBits(1, &input);
  **/

  signed int converted;

  if (needsFlipping == true) {
    //DEBUG_PRINT("\n ###### flip! #####\n");

    // DEBUG_PRINT(" operand needs flipping because it is %c\n", operandPolarity(input));
    input <<= 2;
    input = ~input;
    input >>= 2;

    converted = (signed int) input;
    converted += 1;
    converted = -converted;
  } else {
    input = input & 0x3f;
    converted = (signed int) input;
  }


  // printBits(1, &input);
  // DEBUG_PRINT(" -> %d\n", converted);

  if(converted < -32 || converted > 32){
    DEBUG_PRINT("bad operand! %d\n", input);
  }

  return converted;
}

unsigned int operandExtract(Byte input){
  return input & 0x3f;
}

int opcodeExtract (Byte input){
  Byte masked = input & 0xC0;
  Byte firstTwoBits = masked >> 6;
  if (firstTwoBits != 3){
    return firstTwoBits;
  } else { // extended
    Byte lastFourBits = input & 0x0f;
    // printBitsNL(lastFourBits);
    return lastFourBits;
  }
}

Byte extractSizeBits (Byte input){
  Byte output;
  output = input & 0x30;
  output >>= 4;
  return output;
}

Byte extractLastFourBits (Byte input){
  Byte output;
  output = input & 0x0F;
  return output;
}

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
    case 4:
    result = "CLEAR";
    break;
    case 5:
    result = "KEY";
    break;
    case 6:
    result = "COL";
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

  DEBUG_PRINT("\nReading...\n\n");

  while (input != EOF && numInstructions < IMPORT_MAX_INSTRUCTIONS) {
    buffer[numInstructions++] = input;
    DEBUG_PRINT(HEXIDECIMAL_FORMAT, (Byte) input);
    DEBUG_PRINT(" ");
    input = fgetc(in);
  }

  DEBUG_PRINT("\n\n%i instructions loaded.\n\n", numInstructions);
  return numInstructions;
}

int transformInstructions (int inputStream[IMPORT_MAX_INSTRUCTIONS], Byte outputStream[IMPORT_MAX_INSTRUCTIONS]) {
  DEBUG_PRINT("Transforming...");
  // traverse inputStream whilst there is data
  for (size_t i = 0; i <= IMPORT_MAX_INSTRUCTIONS; i++) {
    int input = inputStream[i];
    if (input != '\0' && input != EOF) {
      if (input != 0) {
        outputStream[i] = (Byte) input;
      } else {
        DEBUG_PRINT("\nblank instruction found: transform halted\n");
        break;
      }
    } else {
      DEBUG_PRINT(" done.\n\n");
      break;
    }
  }

  return 0;
}

signed int operandExtractFromExtendedBuffer (Byte extendedInstruction[], int totalBytes){
  DEBUG_PRINT("operandExtractFromExtendedBuffer: extendedInstruction is of size %i\n", totalBytes);
  Byte operand[totalBytes - 1];
  unsigned int result;
  for (size_t i = 1; i < totalBytes; i++) {
    operand[i - 1] = extendedInstruction[i];
  }

  DEBUG_PRINT("eOperand = \n");
  for (size_t j = 0; j < totalBytes - 1; j++) {
    printBits(1, &operand[j]);
  }
  result = 420;
  return result;
}

const int possibleExtendedSizes[4] = {1,2,3,5};

int bytesToInstructions (Byte instructions[IMPORT_MAX_INSTRUCTIONS], Instruction output[IMPORT_MAX_INSTRUCTIONS]){
  DEBUG_PRINT("Converting into instruction objects... \n\n");
  int numInstructions = 0;
  int i = 0;
  _Bool extendedProcessing = false; // currently processing extended instruction data
  int instructionBytesRemaining = 0; // how many bytes we need to fetch
  Byte extendedInstructionBuffer[5]; // to store the extended instruction bytes

  while(i < IMPORT_MAX_INSTRUCTIONS && instructions[i] != '\0' && instructions[i] != 0){
    Byte current = instructions[i];
    if (extendedProcessing == false) { // we are processing a new instruction
      // determine instruction type
      int opcode = opcodeExtract(current);
      DEBUG_PRINT("%s ", opcodeStringify(opcode));

      if(opcode < 3){ // byte is not extended
          Instruction converted;
          converted.raw = current;
          converted.opcode = opcode;

          if(opcode == DX || opcode == DY || opcode == DT){
            if(opcode == DX || opcode == DY){
              signed int operand;
              operand = moveOperandExtract(current);
              DEBUG_PRINT("%i :> ", operand);
              converted.operand.move = operand;
            } else if (opcode == DT || opcode == PEN){
              unsigned int operand;
              operand = operandExtract(current);
              DEBUG_PRINT("%i :> ", operand);
              if (opcode == DT){
                converted.operand.pause = operand;
              } else if (opcode == PEN) {
                converted.operand.pen = operand;
              }
            }
          } else {
            DEBUG_PRINT("ERROR! ");
          }
          output[numInstructions] = converted;
          numInstructions++;
      } else { // byte is extended
        // TODO: push byte to buffer
        extendedInstructionBuffer[0] = current;
        int totalSize = possibleExtendedSizes[extractSizeBits(extendedInstructionBuffer[0])];
        int extendedOpcode = (int) extractLastFourBits(extendedInstructionBuffer[0]);
        // DEBUG_PRINT("extended %s instruction (size %i) begin processing!\n", opcodeStringify(extendedOpcode), totalSize);

        // TODO: set instructionBytesRemaining
        instructionBytesRemaining = totalSize - 1;
        if (totalSize == 1){
          // DEBUG_PRINT("single-byte extended instruction. no operand necessary\n");
          Instruction converted;
          converted.raw = extendedInstructionBuffer[0];
          converted.opcode = extendedOpcode;
          switch(converted.opcode){
            case PEN:
              converted.operand.pen = true;
              break;
            case CLEAR:
              converted.operand.clear = true;
              break;
            case KEY:
              converted.operand.key = true;
              break;
            default:
              DEBUG_PRINT("#### ERROR: treating %s as single-byte (should be multi-byte!) ####\n", opcodeStringify(converted.opcode));
            break;
          }
          DEBUG_PRINT("[%i]?:> ",converted.opcode);
          output[numInstructions] = converted;
          numInstructions++;
        }
      }
    } else { // we are still processing an extended instruction
      if (instructionBytesRemaining > 0) { // we need to fetch more data
        DEBUG_PRINT("%i bytes remain\n", instructionBytesRemaining);
        int extendedInstructionBytesTotal = possibleExtendedSizes[extractSizeBits(extendedInstructionBuffer[0])];
        int index = extendedInstructionBytesTotal - instructionBytesRemaining;
        extendedInstructionBuffer[index] = current;
        instructionBytesRemaining--;
      } else { // we have all the data we need
        DEBUG_PRINT("completing processing\n");
        int extendedOpcode = (int) extractLastFourBits(extendedInstructionBuffer[0]);
        int extendedInstructionBytesTotal = possibleExtendedSizes[extractSizeBits(extendedInstructionBuffer[0])];
        // DEBUG_PRINT("operand size %i\n", extendedInstructionBytesTotal - 1);



        Instruction converted;
        converted.raw = extendedInstructionBuffer[0];
        converted.opcode = extendedOpcode;

        // TODO: combine all the data from the buffer and put into converted
        if(extendedInstructionBytesTotal > 1){
          signed int operand;
          operand = operandExtractFromExtendedBuffer(extendedInstructionBuffer, extendedInstructionBytesTotal);

          switch(converted.opcode){
            case DX:
            case DY:
              converted.operand.move = operand;
              break;
            case DT:
              converted.operand.pause = operand;
              break;
            case COL:
              converted.operand.col = operand;
              break;
            default:
              DEBUG_PRINT("#### ERROR: treating %s as MULTI-BYTE (should be single-byte) ####\n", opcodeStringify(converted.opcode));
              break;
          }
        } else {
          DEBUG_PRINT("#### ERROR: treating %s as SINGLE-BYTE!?\n", opcodeStringify(converted.opcode));
        }
        // reset state variables and reset buffer
        extendedProcessing = false;
        // TODO: clear buffer
        numInstructions++;
        int outputIndex = numInstructions - 1;
        DEBUG_PRINT("outputIndex%i\n", outputIndex);
        output[outputIndex] = converted;
        DEBUG_PRINT(" :> ");
      }
    }

    i++;

  }
  DEBUG_PRINT("END\n\n%i bytes converted. %i instructions created.\n\n", i, numInstructions);
  return numInstructions;
}

int drawLine (State *state){
  DEBUG_PRINT("line call: %d %d %d %d\n", state->downX, state->downY, state->x, state->y);
  line(state->d, state->downX, state->downY, state->x, state->y);
  state->downX = state->x;
  state->downY = state->y;
  return 0;
}

int performDX (Instruction input, State *state){
  if (input.opcode != DX) {
    DEBUG_PRINT("performDX FAIL: opcode is %i\n", input.opcode);
  } else {
    // DEBUG_PRINT("performDX\n");
    state->x += input.operand.move;
  }
  return 0;
}

int performDY (Instruction input, State *state){
  if (input.opcode != DY) {
    DEBUG_PRINT("performDY FAIL: opcode is %i\n", input.opcode);
  } else {
    state->y += input.operand.move;
    // DEBUG_PRINT("performDY\n");
    if(state->p){
      drawLine(state);
    }
  }
  return 0;
}

int performDT (Instruction input, State *state){
  if (input.opcode != DT) {
    DEBUG_PRINT("performDT FAIL: opcode is %i\n", input.opcode);
  } else {
    // DEBUG_PRINT("performDT\n");
    pause(state->d, input.operand.pause);
  }
  return 0;
}

int performPEN (Instruction input, State *state){
  if (input.opcode != PEN) {
    DEBUG_PRINT("performPEN FAIL: opcode is %i\n", input.opcode);
  } else {
    // DEBUG_PRINT("performPEN\n");
    _Bool initial = state->p;
    state->p = !initial;
    if(state->p == true){
      state->downX = state->x;
      state->downY = state->y;
    }
  }
  return 0;
}

int performCLEAR (Instruction input, State *state){
  if (input.opcode != CLEAR) {
    DEBUG_PRINT("performCLEAR FAIL: opcode is %i\n", input.opcode);
  } else {
    // DEBUG_PRINT("ERROR: performCLEAR NOT YET IMPLEMENTED!!!\n");
    clear(state->d);
  }
  return 0;
}

int performKEY (Instruction input, State *state){
  if (input.opcode != KEY) {
    DEBUG_PRINT("performKEY FAIL: opcode is %i\n", input.opcode);
  } else {
    // DEBUG_PRINT("ERROR: performKEY NOT YET IMPLEMENTED!!!\n");
    key(state->d);
  }
  return 0;
}

int performCOL (Instruction input, State *state){
  if (input.opcode != COL) {
    DEBUG_PRINT("performCOL FAIL: opcode is %i\n", input.opcode);
  } else {
    DEBUG_PRINT("ERROR: performCOL NOT YET IMPLEMENTED!!!\n");
    // pause(state->d, input.operand.pause);
  }
  return 0;
}

int interpretInstructions (int n, Instruction instructions[IMPORT_MAX_INSTRUCTIONS], display *d){
  DEBUG_PRINT("Interpreting %i instructions...\n", n);
  int i = 0;

  State state = {
    .x = 0,
    .y = 0,
    .p = false,
    .d = d
  };
  State *statePtr = &state;

  DEBUG_PRINT("START\n");
  printState(statePtr);

  char operandStr[5];
  while (i < n && i < IMPORT_MAX_INSTRUCTIONS) {
    DEBUG_PRINT("%i: ", i);
    Instruction instruction = instructions[i];
    // printf("%i", instruction.opcode);

    switch(instruction.opcode){
      case DX:
        // DEBUG_PRINT("DX");
        sprintf(operandStr, "%i", instruction.operand.move);
        DEBUG_PRINT("%s %i (%s %s)\n", opcodeStringify(instruction.opcode), instruction.operand.move, opcodeStringify(instruction.opcode), operandStr);
        performDX(instruction, statePtr);
        break;
      case DY:
        // DEBUG_PRINT("DY");
        DEBUG_PRINT("%s %i (%s %s)\n", opcodeStringify(instruction.opcode), instruction.operand.move, opcodeStringify(instruction.opcode), operandStr);
        sprintf(operandStr, "%i", instruction.operand.move);
        performDY(instruction, statePtr);
        break;
      case DT:
        // DEBUG_PRINT("DT");
        DEBUG_PRINT("%s %i (%s %s)\n", opcodeStringify(instruction.opcode), instruction.operand.pause, opcodeStringify(instruction.opcode), operandStr);
        sprintf(operandStr, "%i", instruction.operand.pause);
        performDT(instruction, statePtr);
        break;
      case PEN:
        // DEBUG_PRINT("PEN");
        performPEN(instruction, statePtr);
        DEBUG_PRINT("%s (%s %s)\n", opcodeStringify(instruction.opcode), opcodeStringify(instruction.opcode), operandStr);
        break;
      case CLEAR:
        // DEBUG_PRINT("CLEAR");
        performCLEAR(instruction, statePtr);
        break;
      case KEY:
        // DEBUG_PRINT("KEY");
        performKEY(instruction, statePtr);
        break;
      case COL:
        // DEBUG_PRINT("COL");
        sprintf(operandStr, "%i", instruction.operand.col);
        performCOL(instruction, statePtr);
      break;
      default:
        printf("interpretInstructions ERROR\n");
        break;
    }
    // DEBUG_PRINT("%s %s ", opcodeStringify(instruction.opcode), operandStr);
    printState(statePtr);

    i++;
  }

  DEBUG_PRINT("\n ...done.\n");
  return 0;
}

void initializeBuffer(int buffer[IMPORT_MAX_INSTRUCTIONS]){
  for (size_t i = 0; i < IMPORT_MAX_INSTRUCTIONS; i++) {
    buffer[i] = 0;
  }
}

void initializeInstructionBytes (Byte instructions[IMPORT_MAX_INSTRUCTIONS]){
    for (size_t i = 0; i < IMPORT_MAX_INSTRUCTIONS; i++) {
      instructions[i] = 0;
    }
}


// Read sketch instructions from the given file.  If test is NULL, display the
// result in a graphics window, else check the graphics calls made.
void run(char *filename, char *test[]) {
  int numInstructions = 0;
  int buffer[IMPORT_MAX_INSTRUCTIONS];
  Byte instructionBytes[IMPORT_MAX_INSTRUCTIONS];

  initializeBuffer(buffer);
  initializeInstructionBytes(instructionBytes);

  FILE *in = fopen(filename, "rb");
  if (in == NULL) {
    fprintf(stderr, "Can't open %s\n", filename);
    exit(1);
  }
  display *d = newDisplay(filename, 200, 200, test);

  getInstructions(in, d, buffer);
  transformInstructions(buffer, instructionBytes);

  Instruction instructions[IMPORT_MAX_INSTRUCTIONS];
  numInstructions = bytesToInstructions(instructionBytes, instructions);
  interpretInstructions(numInstructions, instructions, d);

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
