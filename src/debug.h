#pragma once

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(__x) (sizeof(__x)/sizeof(__x[0]))
#endif

int winetest_vok(int condition, const char *msg, va_list args);
void winetest_ok(int condition, const char *msg, ...);

void winetest_vskip(const char *msg, va_list args);
void winetest_win_skip(const char *msg, ...);

void winetest_set_location(const char *file, int line);
void winetest_push_context(const char* fmt, ...);
void winetest_pop_context(void);

LONG winetest_failures(void);
LONG winetest_successes(void);
LONG winetest_skipped(void);
LONG winetest_flaky_failures(void);
LONG winetest_todo_successes(void);
LONG winetest_todo_failures(void);

const char *wine_dbgstr_wn(const WCHAR *str, int n);
const char *wine_dbgstr_an(const char *str, int n);


static inline const char *
wine_dbgstr_w(const WCHAR *s)
{
    return wine_dbgstr_wn( s, -1 );
}

static inline const char *
wine_dbgstr_a( const char *s )
{
    return wine_dbgstr_an( s, -1 );
}

static inline const char *
debugstr_wn(const WCHAR *s, int n) 
{ 
    return wine_dbgstr_wn( s, n );
}

static inline const char *
debugstr_w( const WCHAR *s ) 
{
    return wine_dbgstr_wn( s, -1 );
}

static inline const char *
debugstr_a( const char *s ) 
{
    return wine_dbgstr_an( s, -1 );
}
        
static inline const char *
wine_dbgstr_longlong(ULONGLONG ll)
{
    static unsigned ll_cursor = 0; // allocate cursor
    static char ll_buffers[8][32] = {0}; // round-robin internal buffers
    char *buffer = ll_buffers[ (ll_cursor++) % 8 ]; // allocate next buffer 

    if (sizeof(ll) > sizeof(unsigned long) && ll >> 32) { 
        snprintf( buffer, sizeof(ll_buffers[0])-1, "%lx%08lx", (unsigned long)(ll >> 32), (unsigned long)ll );
    } else {
        snprintf( buffer, sizeof(ll_buffers[0])-1, "%lx", (unsigned long)ll );
    }
    return buffer;
}

#define TRACE_ON(__topic) (1)
#define ERR_(__topic) ERR

void TRACE(const char *fmt, ...);
void WARN(const char *fmt, ...);
void FIXME(const char *fmt, ...);
void ERR(const char *fmt, ...);

//endif
