#pragma once

#ifndef MATHLIBRARY_EXPORT
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllexport)
#endif

extern "C" MATH_API int Add(int a, int b);
extern "C" MATH_API int Minus(int a, int b);