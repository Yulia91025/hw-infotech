#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
extern void ch(int* a, int n);
extern void b(int arrForSort[], const int SIZE);
extern void swap(int* arr, int i);
extern void sh(int* arr, int size);
extern void in(int* a, int N);