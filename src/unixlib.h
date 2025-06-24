#pragma once
/*
 * Definitions for Unix libraries
 *
 * Copyright (C) 2021 Alexandre Julliard
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
 
#include "config.h"

typedef NTSTATUS (*unixlib_entry_t)( void *args );

static NTSTATUS
wine_unix_call_notimplemented( int func )
{
    FIXME( "unix_call(%d): not implemented\n", func );
    return STATUS_NOT_IMPLEMENTED;
}

#if defined(HAVE_GNUTLS_CIPHER_INIT)

extern const unixlib_entry_t __wine_unix_call_funcs[];
extern const unixlib_entry_t __wine_unix_call_wow64_funcs[];

#define __WINE_UNIX_CALL( func, params ) \
    (__wine_unix_call_funcs[func] ? __wine_unix_call_funcs[func]( params ) : wine_unix_call_notimplemented( func ))

#define UNIX_CALL( func, params ) \
    __WINE_UNIX_CALL( unix_ ## func, params )

#else   // HAVE_GNUTLS_CIPHER_INIT

#define UNIX_CALL( func, params ) \
    wine_unix_call_notimplemented( unix_ ## func )
    
#endif  // HAVE_GNUTLS_CIPHER_INIT

//end
