#include "pch.h"
#include <utility>
#include <limits.h>
#include <iostream>
#include <stdio.h>
#include "Header.h"


void ch(int* a, int n)
{
	int min = 0; int buf = 0;
	for (int i = 0; i < n; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[min]) min = j;
		}
		if (i != min)
		{
			buf = a[i];
			a[i] = a[min];
			a[min] = buf;
		}
	}
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
	delete a;
}

void b(int arrForSort[], const int SIZE)
{
	int buff = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = SIZE - 1; j > i; j--)
		{
			if (arrForSort[j] < arrForSort[j - 1])
			{
				buff = arrForSort[j - 1];
				arrForSort[j - 1] = arrForSort[j];
				arrForSort[j] = buff;
			}
		}
	}
	for (int i = 0; i < SIZE; i++) {
		std::cout << arrForSort[i] << " ";
	}
	delete arrForSort;
}

void swap(int* arr, int i)
{
	int buff;
	buff = arr[i];
	arr[i] = arr[i - 1];
	arr[i - 1] = buff;
}


void sh(int* arr, int size)
{
	int leftMark = 1;
	int rightMark = size - 1;
	while (leftMark <= rightMark)
	{
		for (int i = rightMark; i >= leftMark; i--)
			if (arr[i - 1] > arr[i]) swap(arr, i);
		leftMark++;

		for (int i = leftMark; i <= rightMark; i++)
			if (arr[i - 1] > arr[i]) swap(arr, i);
		rightMark--;
	}
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	delete arr;
}

void in(int* a, int N)
{
	int buff = 0;
	int i, j;
	for (i = 1; i < N; i++)
	{
		buff = a[i];
		for (j = i - 1; j >= 0 && a[j] > buff; j--)
			a[j + 1] = a[j];
		a[j + 1] = buff;
	}
	for (int i = 0; i < N; i++)
		std::cout << a[i] << " ";
	delete a;
}
