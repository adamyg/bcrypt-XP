/*
 * Definitions for Wine C unit tests.
 *
 * Copyright (C) 2002 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

typedef struct {
    const char *current_file;       /* file of current check */
    int current_line;               /* line of current check */

    unsigned int todo_level;        /* current todo nesting level */
    unsigned int nocount_level;
    int todo_do_loop;

//  char *str_pos;                  /* position in debug buffer */
//  char strings[2000];             /* buffer for debug strings */

#define BUFFERSIZE 128
    char context[8][BUFFERSIZE];    /* data to print before messages */
    unsigned int context_count;     /* number of context prefixes */

    char buffer[8][BUFFERSIZE];     /* data to print before messages */
    unsigned int buffer_count;      /* number of context prefixes */

} tls_data;

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(__x) (sizeof(__x)/sizeof(__x[0]))
#endif

static void winetest_printf(const char *msg, ...);
static void winetest_print_context(const char *msgtype);

static LONG successes;              /* number of successful tests */
static LONG failures;               /* number of failures */
static LONG skipped;                /* number of skipped test chunks */
static LONG todo_successes;         /* number of successful tests inside todo block */
static LONG todo_failures;          /* number of failures inside todo block */

int report_success = 1;             /* verbose */


//#define WINETEST_PRINTFOUT

static tls_data *
get_tls_data(void)
{
    static tls_data data;
    return &data;
}


static char *
get_context_buffer(void)
{
    tls_data *data = get_tls_data();
    return data->buffer[ (data->buffer_count++) % ARRAY_SIZE(data->buffer) ];
}


void 
TRACE(const char *fmt, ...)
{
    char buffer[512];
    va_list ap;
    int buflen;

    va_start(ap, fmt);
    strcpy(buffer, "TRACE: ");
    buflen = vsnprintf(buffer + 7, sizeof(buffer) - 7, fmt, ap);
#ifndef WINETEST_PRINTFOUT
    OutputDebugStringA(buffer);
#else
    fwrite(buffer, buflen + 7, 1, stdout);
#endif
    va_end(ap);
}


void
WARN(const char *fmt, ...)
{
    char buffer[512];
    va_list ap;
    int buflen;

    va_start(ap, fmt);
    strcpy(buffer, "WARN:  ");
    buflen = vsnprintf(buffer + 7, sizeof(buffer) - 7, fmt, ap);
#ifndef WINETEST_PRINTFOUT
    OutputDebugStringA(buffer);
#else
    fwrite(buffer, buflen + 7, 1, stdout);
#endif
    va_end(ap);
}


void 
FIXME(const char *fmt, ...)
{
    char buffer[512];
    va_list ap;
    int buflen;

    va_start(ap, fmt);
    strcpy(buffer, "FIXME: ");
    buflen = vsnprintf(buffer + 7, sizeof(buffer) - 7, fmt, ap);
#ifndef WINETEST_PRINTFOUT
    OutputDebugStringA(buffer);
#else
    fwrite(buffer, buflen + 7, 1, stdout);
#endif
    va_end(ap);
}


void 
ERR(const char *fmt, ...)
{
    char buffer[512];
    va_list ap;
    int buflen;

    va_start(ap, fmt);
    strcpy(buffer, "ERROR: ");
    buflen = vsnprintf(buffer + 7, sizeof(buffer) - 7, fmt, ap);
#ifndef WINETEST_PRINTFOUT
    OutputDebugStringA(buffer);
#else
    fwrite(buffer, buflen + 7, 1, stdout);
#endif
    va_end(ap);
}


const char *
wine_dbgstr_wn(const WCHAR *str, int n)
{
    static const char hex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    char *buffer = get_context_buffer(), *dst = buffer;

    if (NULL == str)  {
        return "(null)";
    }

    if (n == -1) {
        for (n = 0; str[n]; n++);
    }

    *dst++ = 'L';
    *dst++ = '"';

    while (n-- > 0 && dst <= buffer + (BUFFERSIZE - 10))
    {
        WCHAR c = *str++;
        switch (c)
        {
        case '\n': *dst++ = '\\'; *dst++ = 'n'; break;
        case '\r': *dst++ = '\\'; *dst++ = 'r'; break;
        case '\t': *dst++ = '\\'; *dst++ = 't'; break;
        case '"':  *dst++ = '\\'; *dst++ = '"'; break;
        case '\\': *dst++ = '\\'; *dst++ = '\\'; break;
        default:
            if (c < ' ' || c >= 127) 
            {
                *dst++ = '\\';
                *dst++ = hex[(c >> 12) & 0x0f];
                *dst++ = hex[(c >> 8) & 0x0f];
                *dst++ = hex[(c >> 4) & 0x0f];
                *dst++ = hex[c & 0x0f];
            }
            else *dst++ = (char)c;
        }
    }

    *dst++ = '"';
    if (n > 0)
    {
        *dst++ = '.';
        *dst++ = '.';
        *dst++ = '.';
    }
    *dst = 0;

    return buffer;
}


const char *
wine_dbgstr_an(const char *str, int n)
{
    static const char hex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    char *buffer = get_context_buffer(), *dst = buffer;

    if (NULL == str) {
        return "(null)";
    }

    if (n == -1) {
        for (n = 0; str[n]; n++);
    }

    *dst++ = 'L';
    *dst++ = '"';

    while (n-- > 0 && dst <= buffer + (BUFFERSIZE - 10))
    {
        WCHAR c = *str++;
        switch (c)
        {
        case '\n': *dst++ = '\\'; *dst++ = 'n'; break;
        case '\r': *dst++ = '\\'; *dst++ = 'r'; break;
        case '\t': *dst++ = '\\'; *dst++ = 't'; break;
        case '"':  *dst++ = '\\'; *dst++ = '"'; break;
        case '\\': *dst++ = '\\'; *dst++ = '\\'; break;
        default:
            if (c < ' ' || c >= 127)
            {
                *dst++ = '\\';
                *dst++ = hex[(c >> 4) & 0x0f];
                *dst++ = hex[c & 0x0f];
            }
            else *dst++ = (char)c;
        }
    }

    *dst++ = '"';
    if (n > 0)
    {
        *dst++ = '.';
        *dst++ = '.';
        *dst++ = '.';
    }
    *dst = 0;

    return buffer;
}


void 
winetest_vskip(const char *msg, va_list args)
{
    winetest_print_context("Tests skipped: ");
    vfprintf(stdout, msg, args);
    ++skipped;
}


void 
winetest_win_skip(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    winetest_vskip(msg, ap);
    va_end(ap);
}


int 
winetest_vok(int condition, const char *msg, va_list args)
{
    tls_data *data = get_tls_data();
 
    if (data->todo_level)
    {
        if (condition)
        {
            winetest_print_context( "Test succeeded inside todo block: " );
            vfprintf(stdout, msg, args);
            if ((data->nocount_level & 2) == 0)
            InterlockedIncrement(&todo_failures);
            return 0;
        }
        else
        {
            /* show todos even if traces are disabled*/
            /*if (winetest_debug > 0)*/
            {
                winetest_print_context("Test marked todo: ");
                vfprintf(stdout, msg, args);
            }
            if ((data->nocount_level & 1) == 0)
            InterlockedIncrement(&todo_successes);
            return 1;
        }
    }
    else
    {
        if (!condition)
        {
            winetest_print_context("Test failed: ");
            vfprintf(stdout, msg, args);
            if ((data->nocount_level & 2) == 0)
            InterlockedIncrement(&failures);
            return 0;
        }
        else
        {
            if (report_success && (data->nocount_level & 1) == 0)
            {
                winetest_printf("Test succeeded\n");
            }
            if ((data->nocount_level & 1) == 0)
            InterlockedIncrement(&successes);
            return 1;
        }
    }
}
 

void 
winetest_ok(int condition, const char *msg, ...)
{
    va_list ap ;
 
    va_start(ap , msg);
    winetest_vok(condition, msg, ap );
    va_end(ap );
}


void 
winetest_set_location(const char *file, int line)
{
    tls_data *data = get_tls_data();

#if defined(WINETEST_MSVC_IDE_FORMATTING)
    data->current_file = file;
#else
    data->current_file = strrchr(file,'/');
    if (data->current_file == NULL)
        data->current_file = strrchr(file,'\\');
    if (data->current_file == NULL)
        data->current_file = file;
    else
        data->current_file++;
#endif
    data->current_line = line;
}


static void 
winetest_printf(const char *msg, ...)
{
    tls_data *data = get_tls_data();
    va_list ap;
 
    fprintf(stdout, "%s[%d]: ", data->current_file, data->current_line);
    va_start(ap, msg);
    vfprintf(stdout, msg, ap);
    va_end(ap);
}


void 
winetest_push_context(const char* fmt, ...)
{
    tls_data *data = get_tls_data();
    va_list ap;
 
    if (data->context_count < ARRAY_SIZE(data->context))
    {
        va_start(ap, fmt);
        vsnprintf(data->context[data->context_count], sizeof(data->context[data->context_count]), fmt, ap);
        va_end(ap);
        data->context[data->context_count][sizeof(data->context[data->context_count]) - 1] = 0;
    }
    ++data->context_count;
}
 

void 
winetest_pop_context(void)
{
    tls_data* data = get_tls_data();
 
    if (data->context_count)
        --data->context_count;
}
 

static void 
winetest_print_context(const char *msgtype)
{
    tls_data *data = get_tls_data();
    unsigned int i;
 
    winetest_printf("%s", msgtype);
    for (i = 0; i < data->context_count; ++i) {
        fprintf(stdout, "%s: ", data->context[i]);
    }
}


LONG
winetest_failures(void)
{
    return failures;
}
         

LONG
winetest_successes(void)
{
    return successes;
}


LONG
winetest_skipped(void)
{
    return skipped;
}


LONG 
winetest_flaky_failures(void)
{
    return 0;
}


LONG
winetest_todo_successes(void)
{
    return todo_successes;
}


LONG
winetest_todo_failures(void)
{
    return todo_failures;
}

//end

