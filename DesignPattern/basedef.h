#pragma once

#ifdef _DP_DLL
#define _DP_SPEC __declspec(dllexport)
#else
#define _DP_SPEC __declspec(dllimport)
#endif

#ifdef _DEBUG
#define _DP_INL_SPEC _DP_SPEC
#else
#define _DP_INL_SPEC
#endif

#define DP_CV            __cdecl
#define DP_CV_(c)        c DP_CV
#define DP_CLASS         _DP_SPEC
#define DP_FUNC          _DP_SPEC DP_CV
#define DP_FUNC_(c)      _DP_SPEC c DP_CV
#define DP_FUNC_INL      _DP_INL_SPEC DP_CV
#define DP_FUNC_INL_(c)  _DP_INL_SPEC c DP_CV