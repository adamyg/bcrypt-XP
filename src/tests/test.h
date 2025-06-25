#pragma once

#include "../debug.h"

#define todo_wine               /**/;
#define todo_wintodo_winee      /**/;

#define ok_(file, line)         (winetest_set_location(file, line), 0) ? (void)0 : winetest_ok
#define ok                      ok_(__FILE__, __LINE__)

#define win_skip_(file, line)   (winetest_set_location(file, line), 0) ? (void)0 : winetest_win_skip
#define win_skip                win_skip_(__FILE__, __LINE__)

static inline int
broken(int condition)
{
    return (condition ? 1 : 0);
}

#define START_TEST(__name) \
const char *wine_test_name = #__name; \
void test_main(void)

static void test_main(void);

static int winetest_debug = 1;
static int winetest_report_flaky = 0;
static int winetest_time = 1;
static int winetest_start_time;
static int winetest_last_time;

           
static int 
winetest_get_time(void)
{
    return (int)GetTickCount();
}

          
static const char *
winetest_elapsed(char *buffer)
{
    int now;

    if (! winetest_time) return "";
    winetest_last_time = now = winetest_get_time();
    sprintf(buffer, "%.3f", (now - winetest_start_time) / 1000.0);
    return buffer;
}


int
main(int argc, char **argv)
{
    extern const char *wine_test_name;
//  char p[32];
    int status;
    
//  if (GetEnvironmentVariableA("WINETEST_REPORT_FLAKY", p, sizeof(p) )) winetest_report_flaky = atoi(p);
//  if (GetEnvironmentVariableA("WINETEST_REPORT_SUCCESS", p, sizeof(p) )) winetest_report_success = atoi(p);

    winetest_start_time = winetest_get_time();
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    test_main();

    if (winetest_debug)
    {
        char elapsed[64];

        printf( "%04x:%s:%s %u tests executed (%u marked as todo, %u as flaky, %u %s), %u skipped.\n",
            (unsigned)GetCurrentProcessId(), wine_test_name, winetest_elapsed( elapsed ),
            (unsigned)(winetest_successes() + winetest_failures() + winetest_flaky_failures() + winetest_todo_successes() + winetest_todo_failures()),
                (unsigned)winetest_todo_successes(),
                (unsigned)winetest_flaky_failures(), 
                (unsigned)(winetest_failures() + winetest_todo_failures()),
                    ((winetest_failures() + winetest_todo_failures()) != 1) ? "failures" : "failure",
            (unsigned)winetest_skipped());
    }
    
    status = winetest_failures() + winetest_todo_failures();
//  if (winetest_report_flaky) status += winetest_flaky_failures();
    if (status > 255) status = 255;
    return status;
}

//end
