/*
 * BCrypt Unimplemented functions, Vista+ and Undocumented
 *
 * Copyright (c) 2025, Adam Young.
 *
 * https://github.com/adamyg/bcrypt-XP
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <ntstatus.h>
#define WIN32_NO_STATUS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wincrypt.h>


NTSTATUS WINAPI
BCryptConfigureContext(ULONG dwTable, LPCWSTR pszContext, PCRYPT_CONTEXT_CONFIG pConfig)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptConfigureContextFunction(
    ULONG dwTable, LPCWSTR pszContext, ULONG dwInterface, LPCWSTR pszFunction, PCRYPT_CONTEXT_FUNCTION_CONFIG pConfig)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptCreateContext(
    ULONG dwTable, LPCWSTR pszContext, PCRYPT_CONTEXT_CONFIG pConfig)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptCreateMultiHash(
    BCRYPT_ALG_HANDLE hAlgorithm, BCRYPT_HASH_HANDLE* phHash, ULONG nHashes, PUCHAR pbHashObject, ULONG cbHashObject, PUCHAR pbSecret, ULONG cbSecret, ULONG dwFlags)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptDeleteContext(ULONG dwTable, LPCWSTR pszContext)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptEnumContexts(
    ULONG dwTable, ULONG *pcbBuffer, PCRYPT_CONTEXTS *ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptEnumProviders(
    LPCWSTR pszAlgId, ULONG *pImplCount, BCRYPT_PROVIDER_NAME **ppImplList, ULONG dwFlags)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptEnumRegisteredProviders(
    ULONG *pcbBuffer, PCRYPT_PROVIDERS* ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptProcessMultiOperations(
    BCRYPT_HANDLE hObject, BCRYPT_MULTI_OPERATION_TYPE operationType, PVOID pOperations, ULONG cbOperations, ULONG dwFlags)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptQueryContextConfiguration(
    ULONG dwTable, LPCWSTR pszContext, ULONG *pcbBuffer, PCRYPT_CONTEXT_CONFIG *ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptQueryContextFunctionConfiguration(
    ULONG dwTable, LPCWSTR pszContext, ULONG dwInterface, LPCWSTR pszFunction, ULONG *pcbBuffer, PCRYPT_CONTEXT_FUNCTION_CONFIG *ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptQueryContextFunctionProperty(
    ULONG dwTable, LPCWSTR pszContext, ULONG dwInterface, LPCWSTR pszFunction, LPCWSTR pszProperty, ULONG *pcbValue, PUCHAR *ppbValue)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptQueryProviderRegistration(
    LPCWSTR pszProvider, ULONG dwMode, ULONG dwInterface, ULONG *pcbBuffer, PCRYPT_PROVIDER_REG *ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptRegisterConfigChangeNotify(
    HANDLE *phEvent)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptResolveProviders(
    LPCWSTR pszContext, ULONG dwInterface, LPCWSTR pszFunction, LPCWSTR pszProvider, ULONG dwMode, ULONG dwFlags, ULONG *pcbBuffer, PCRYPT_PROVIDER_REFS *ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptSetContextFunctionProperty(
    ULONG dwTable, LPCWSTR pszContext, ULONG dwInterface, LPCWSTR pszFunction, LPCWSTR pszProperty, ULONG cbValue, PUCHAR pbValue)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptUnregisterConfigChangeNotify(
    HANDLE hEvent)
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS WINAPI
BCryptEnumContextFunctionProviders(
    ULONG dwTable, LPCWSTR pszContext, ULONG dwInterface, LPCWSTR pszFunction, ULONG *pcbBuffer, PCRYPT_CONTEXT_FUNCTION_PROVIDERS *ppBuffer)
{
    return STATUS_NOT_IMPLEMENTED;
}


// undocumented
NTSTATUS WINAPI
BCryptSetAuditingInterface(void)
{
    return STATUS_NOT_IMPLEMENTED;
}

//end
