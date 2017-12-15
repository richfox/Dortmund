#pragma once

#ifdef _UTIL_DLL
#define _UTIL_SPEC __declspec(dllexport)
#else
#define _UTIL_SPEC __declspec(dllimport)
#endif

#ifdef _DEBUG
#define _UTIL_INL_SPEC _UTIL_SPEC
#else
#define _UTIL_INL_SPEC
#endif

#define UTIL_CV            __cdecl
#define UTIL_CV_(c)        c UTIL_CV
#define UTIL_CLASS         _UTIL_SPEC
#define UTIL_FUNC          _UTIL_SPEC UTIL_CV
#define UTIL_FUNC_(c)      _UTIL_SPEC c UTIL_CV
#define UTIL_FUNC_INL      _UTIL_INL_SPEC UTIL_CV
#define UTIL_FUNC_INL_(c)  _UTIL_INL_SPEC c UTIL_CV