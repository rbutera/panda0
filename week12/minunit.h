#define mu_assert(message, test)          \
    do {if(tests_failed < 1){tests_run++;} if (!(test)) {tests_failed++; return message; } \
    } while (0)
#define mu_run_suite(test)                     \
    do { char *message = test(); if(tests_failed > 1) { suites_run++; } \
         if (message) { suites_failed++; return message; }     \
    } while (0)

extern int tests_run;
extern int tests_failed;
extern int suites_run;
extern int suites_failed;
