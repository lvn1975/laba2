// ConsoleApplication16.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

struct LoopOptions
{
	long start;
	long limit;
	long sum;
};

long *array;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	LoopOptions *options = (LoopOptions*)lpParameter;
	
	long sum = 0;
	for(long i = options->start; i < options->limit; i++)
	{
		sum+=array[i];
	}
	options->sum = sum;
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	long n=10;
	array=new long[n];
	 
	for (int i=0; i<n; i++)
	{
		array[i]=i;
	}

	HANDLE hThreads[2];

	LoopOptions loop1;
	loop1.start = 0;
	loop1.limit = n/2;

	LoopOptions loop2;
	loop2.start = n/2;
	loop2.limit = n;

	hThreads[0] = CreateThread(NULL, NULL, ThreadProc, &loop1, 0, 0);
	hThreads[1] = CreateThread(NULL, NULL, ThreadProc, &loop2, 0, 0);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	cout << "sum is " << loop1.sum+loop2.sum<<endl;	

	system ("pause");
	return 0;
}

