#define DEBUG          1

#ifdef DEBUG
#define DEBUG_PRINT    printf
#else
#define DEBUG_PRINT(...)
#endif
