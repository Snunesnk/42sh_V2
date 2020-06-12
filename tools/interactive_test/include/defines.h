//Time bewteen each char sent to target process, in ns.
//Default is 500ns
#define CHAR_DELAY 100

// Time, in ms, before a process is going to be stopped. First a CTRL-C is sent, and if process timeout again, a CTRL-D is sent, then prog is declared to be in infinite loop and tester exit.
// Default is 5s
#define TIMEOUT (5 * 1000000)

// Test directory, make sure to end it by a '/':
#define TEST_DIR "../"

//test file extension
#define TEST_EXT ".test"
