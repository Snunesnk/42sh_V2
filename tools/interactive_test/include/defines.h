//test if process is still running, gonna remove it and make a proper functions
#define PROCESS_STOPPED (kill(g_pid, 0) != 0 || access(g_process_input, F_OK) > 0) ? 1 : 0

//Time bewteen each char sent to target process, in ns.
#define CHAR_DELAY 500

//Time bewteen line sent to send_input(), in ns. Used in is_ready() to wait for a cmd to finish
#define INPUT_DELAY 65000

// Time, in ms, before a process is going to be stopped. First a CTRL-C is sent, and if process timeout again, a CTRL-D is sent, then prog is declared to be in infinite loop and tester exit.
#define TIMEOUT (5 * 1000000)

// Test directory, make sure to end it by a '/':
#define TEST_DIR "../"

//test file extension
#define TEST_EXT ".test"
