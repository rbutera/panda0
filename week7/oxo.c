#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-----------------------------------------------------------------------------
// Setting up types and constants.  This section doesn't need to be changed.
//-----------------------------------------------------------------------------

// A board object contains the entire current state of a game. It contains the
// cells, the player whose turn it is, and the number of moves made in total.
// The name 'Board' is a synonym for the type 'struct board'.
struct board {
    char cells[3][3];
    char player;
    int moves;
};
typedef struct board Board;

// A row/column position in the board.
// The name 'Position' is a synonym for the type 'struct position'.
struct position { int row, col; };
typedef struct position Position;

// Constants for player X, player O, and blank.
enum { X = 'X', O = 'O', B = '.' };

//-----------------------------------------------------------------------------
// Functions providing the logic of the game.  Change these.
//-----------------------------------------------------------------------------

int setPosition (Board *b, int row, int col, char newValue);
int initializeBoard (Board *b);
int setAndDisplay (Board *b, int row, int col, char newValue);

// TODO: finish this function
// Initialize a blank board for a new game, with the given player to move first.
void newGame(Board *b, char player) {
  initializeBoard(b);
  b->player = player;
  b->moves = 0;
}

_Bool validRow (char c){
  _Bool result = (c == 'a' || c == 'b' || c == 'c');
  if(!result){
    printf("invalid Row: %c\n", c);
  }
  return result;
}

int convertRowCharToInt (char input) {
  int output;
  switch (input) {
    case 'a':
      output = 0;
      break;
    case 'b':
      output = 1;
      break;
    case 'c':
      output = 2;
      break;
    default:
      output = -1;
      printf("OMG INVALID ROW CHAR DETECTED!\n");
      break;
  }
  return output;
}

_Bool validCol (char c){
  _Bool result = (c == '1' || c == '2' || c == '3');
  if(!result){
    printf("invalid Col: %c\n", c);
  }
  return result;
}

int convertColCharToInt (char input) {
  return ((input - '0') - 1);
}

// TODO: finish this function
// Prepare to make a move by converting a string such as "a2" to a row and
// column.  Return false if the string is invalid, or the cell isn't blank.
bool position(Board *b, char *text, Position *p) {
    _Bool valid = true;

    if(strlen(text) != 2) {
      printf("string of length %i input - should be 2", (int) strlen(text));
      valid = false;
    } else if (!validRow(text[0]) || !validCol(text[1])) {
      valid = false;
    } else {
      int row = convertRowCharToInt(text[0]);
      int col = convertColCharToInt(text[1]);

      // check if cell is blank
      if (b->cells[row][col] != B) {
        valid = false;
      } else {
        // printf("valid!\n");
        p->row = row;
        p->col = col;
      }
    }

    return valid;
}

// TODO: finish this function
// Make a move at the given position, assuming that it is valid.
void move(Board *b, Position *p) {
  if(position(b,p)){
    
  }
}

// TODO: finish this function
// Check whether x, y, z form a winning line.
bool line(char x, char y, char z) {
    return false;
}

// TODO: finish this function
// Check whether or not the player who has just moved has won.
bool won(Board *b) {
    return false;
}

// TODO: finish this function
// Check whether the game is drawn
bool drawn(Board *b) {
    return false;
}

// TODO: finish this function
// Display the board.
void display(Board *b) {
    // iterate over all rows
    int i, j;
    for (i = 0; i < 3; i++) {
        // iterate over all columns
        for (j = 0; j < 3; j++) {

            printf("%c", b->cells[i][j]);

            // insert newline at end of row
            if (j == 2){
                printf("\n");
            }
        }
    }
}
Board *createBoard(char player) {
    Board *b = (Board *) malloc (sizeof(Board));

    b->player = player;
    b->moves = 0;
    // Board b = {
    //         .player = player,
    //         .moves = 0
    // };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b->cells[i][j] = B;
        }
    }

    return b;
}

int destroyBoard (Board * b) {
  free(b);
  // printf("destroyed board\n");
}

int setPosition (Board *b, int row, int col, char newValue) {
    char currentValue = b->cells[row][col];
    if (currentValue == X || currentValue == O) {
      printf("COULD NOT ASSIGN POSITION - TAKEN!\n");
      return 1;
    } else {
      // printf("setting position %i %i to %c\n", row, col, newValue);
      b->cells[row][col] = newValue;
      return 0;
    }
}

int initializeBoard (Board *b){
  for (size_t row = 0; row < 3; row++) {
    for (size_t col = 0; col < 3; col++) {
      setPosition(b, row, col, B);
    }
  }
  return 0;
}

int setAndDisplay (Board *b, int row, int col, char newValue) {
  int positionSet = setPosition(b, row, col, newValue);
  if (positionSet == 0) {
    display(b);
    return 0;
  } else {
    printf("could not set+display [%i,%i] to %c\n", row, col, newValue);
    return 1;
  }
}

// TODO: finish this function
// Play the game interactively between two human players who take turns.
void play(char player) {
    Board *b = createBoard('X');
    setAndDisplay(b, 1, 1, X);
    setAndDisplay(b, 0, 1, O);
    setAndDisplay(b, 0, 0, X);
    setAndDisplay(b, 0, 1, O);
}

//-----------------------------------------------------------------------------
// Testing and running: nothing after this point needs to be changed.
//-----------------------------------------------------------------------------

// Constants representing types.
enum type { CHAR, INT, BOOL };

// Check that two ints, chars or bools are equal
int eq(enum type t, int x, int y) {
    static int n = 0;
    n++;
    if (x != y) {
        if (t==CHAR) fprintf(stderr, "Test %d gives %c not %c\n", n, x, y);
        if (t==INT) fprintf(stderr, "Test %d gives %d not %d\n", n, x, y);
        if (t==BOOL && x) fprintf(stderr, "Test %d gives true not false\n", n);
        if (t==BOOL && y) fprintf(stderr, "Test %d gives false not true\n", n);
        exit(1);
    }
    return n;
}

// More specific versions of the eq function
int eqc(char x, char y) { return eq(CHAR, x, y); }
int eqi(int x, int y) { return eq(INT, x, y); }
int eqb(bool x, bool y) { return eq(BOOL, x, y); }

void test() {
    Board bdata = {{{'?','?','?'},{'?','?','?'},{'?','?','?'}},'?',-1};
    Board *board = &bdata;
    Position pdata = {-1,-1};
    Position *pos = &pdata;

    // Tests 1 to 5 (new board)
    newGame(board, X);
    eqc(board->cells[0][0], B); // todo: TEST 1
    eqc(board->cells[1][2], B); // todo: TEST 2
    eqc(board->cells[2][1], B); // todo: TEST 3
    eqc(board->player, X); // todo: TEST 4
    eqc(board->moves, 0); // todo: TEST 5

    // Tests 6 to 14 (valid positions)
    eqb(position(board, "a1", pos), true); // todo: TEST 6
    eqi(pos->row, 0); // todo: TEST 7
    eqi(pos->col, 0); // todo: TEST 8
    eqb(position(board, "b3", pos), true); // todo: TEST 9
    eqi(pos->row, 1); // todo: TEST 10
    eqi(pos->col, 2); // todo: TEST 11
    eqb(position(board, "c1", pos), true); // todo: TEST 12
    eqi(pos->row, 2); // todo: TEST 13
    eqi(pos->col, 0); // todo: TEST 14

    // Tests 15 to 22 (invalid positions, and occupied squares)
    eqb(position(board, "d2", pos), false); // todo: TEST 15
    eqb(position(board, "b0", pos), false); // todo: TEST 16
    eqb(position(board, "b4", pos), false); // todo: TEST 17
    eqb(position(board, "2b", pos), false); // todo: TEST 18
    eqb(position(board, "b2x", pos), false); // todo: TEST 19
    eqb(position(board, "b", pos), false); // todo: TEST 20
    eqb(position(board, "", pos), false); // todo: TEST 21
    *board = (Board) {{{B,B,B},{B,B,B},{B,X,B}},O,1};
    eqb(position(board, "c2", pos), false); // todo: TEST 22

    // Tests 23 to 28 (moves)
    newGame(board, 'X');
    position(board, "b2", pos);
    move(board, pos);
    eqc(board->cells[1][1], X); // todo: TEST 23
    eqc(board->player, O); // todo: TEST 24
    eqc(board->moves, 1); // todo: TEST 25
    position(board, "a3", pos);
    move(board, pos);
    eqc(board->cells[0][2], O); // todo: TEST 26
    eqc(board->player, X); // todo: TEST 27
    eqc(board->moves, 2); // todo: TEST 28

    // Tests 29 to 36 (winning lines)
    eqb(line(X, X, X), true); // todo: TEST 29
    eqb(line(O, O, O), true); // todo: TEST 30
    eqb(line(X, O, O), false); // todo: TEST 31
    eqb(line(O, X, O), false); // todo: TEST 32
    eqb(line(O, O, X), false); // todo: TEST 33
    eqb(line(B, B, B), false); // todo: TEST 34
    eqb(line(X, B, B), false); // todo: TEST 35
    eqb(line(O, O, B), false); // todo: TEST 36

    // Tests 37-44 (won function, winning lines)
    *board = (Board) {{{X,X,X},{B,O,B},{B,O,B}},O,5};
    eqb(won(board), true); // todo: TEST 37
    *board = (Board) {{{B,O,B},{X,X,X},{B,O,B}},O,5};
    eqb(won(board), true); // todo: TEST 38
    *board = (Board) {{{B,O,B},{B,O,B},{X,X,X}},O,5};
    eqb(won(board), true); // todo: TEST 39
    *board = (Board) {{{O,B,B},{O,X,B},{O,B,X}},X,5};
    eqb(won(board), true); // todo: TEST 40
    *board = (Board) {{{B,O,B},{X,O,B},{B,O,X}},X,5};
    eqb(won(board), true); // todo: TEST 41
    *board = (Board) {{{B,B,O},{X,B,O},{B,B,O}},X,5};
    eqb(won(board), true); // todo: TEST 42
    *board = (Board) {{{X,B,O},{B,X,O},{B,B,X}},O,5};
    eqb(won(board), true); // todo: TEST 43
    *board = (Board) {{{X,B,O},{B,O,X},{O,B,B}},X,5};
    eqb(won(board), true); // todo: TEST 44

    // Tests 45-48 (won function, no winning line)
    *board = (Board) {{{B,B,B},{B,B,B},{B,B,B}},X,0};
    eqb(won(board), false); // todo: TEST 45
    *board = (Board) {{{O,B,X},{X,X,O},{O,X,B}},O,7};
    eqb(won(board), false); // todo: TEST 46
    *board = (Board) {{{X,O,X},{X,O,O},{O,X,O}},X,9};
    eqb(won(board), false); // todo: TEST 47
    *board = (Board) {{{O,O,X},{X,X,O},{O,X,X}},O,9};
    eqb(won(board), false); // todo: TEST 48

    // Tests 49-50 (drawn function)
    *board = (Board) {{{O,B,X},{X,X,O},{O,X,B}},O,7};
    eqb(drawn(board), false); // todo: TEST 49
    *board = (Board) {{{O,O,X},{X,X,O},{O,X,X}},O,9};
    eqb(drawn(board), true); // todo: TEST 50

    printf("Tests passed: %d\n", eqi(0, 0) - 1);
}

// Run the program with no args to carry out the tests, or with one arg (the
// player to go first) to play the game.
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1) test();
    else if (n == 2 && strcmp(args[1],"X") == 0) play(args[1][0]);
    else if (n == 2 && strcmp(args[1],"O") == 0) play(args[2][0]);
    else {
        fprintf(stderr, "Use: ./oxo  OR  ./oxo X  OR  ./oxo O\n");
        exit(1);
    }
    return 0;
}
