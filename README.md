# bcrypt-XP

Windows XP bcrypt.dll - Cryptography API Next Generation (CNG)

2025/06 - Wine Merge

# Build

## Mingw64

 * configure environment

```
@echo off
set TARGETDIR=build_mingw_x86
if not exist %TARGETDIR% mkdir %TARGETDIR%
cd %TARGETDIR%
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release %* ..
```
   
 * build

```
cmake --build build_mingw_x86
```

## MSVC

 * configure environment

```
@echo off
set TARGETDIR=build_msvc_x86
if not exist %TARGETDIR% mkdir %TARGETDIR%
cd %TARGETDIR%
cmake -G "Visual Studio 16 2019" -A Win32 -DCMAKE_BUILD_TYPE=Release %* ..
```

 * build

```
cmake --build build_msvc_x86
```
