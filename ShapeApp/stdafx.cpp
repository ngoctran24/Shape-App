// stdafx.cpp : source file that includes just the standard includes
// ShapeApp.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file


int totalBalance(int* flag, int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += (flag[i] % 2);
	return sum;
}