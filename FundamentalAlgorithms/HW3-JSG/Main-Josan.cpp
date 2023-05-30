/*
*@ Gelu-Samuel Josan
*@ group 30421
* Task: You are required to implement correctly and efficiently two methods for \sorting,
namely the Quciksort and Heapsort along with direct sorting algorithm iterative vs recursive.
*  Personal Interpretation :
*       Cases :
*        QuickSort      : Worst case O(n^2)
*                         AVG case O(nlgn)
*
*        Ins    :         Worst case O(n^2)
*                         AVG case O(n^2)
*
*        HeapSort       : Worst case O(nlgn)
*                       : AVG case O(nlgn)
*
*        As we can see in practice QuickSort is better than HeapSort, with both having complexity of O(nlgn) in best and AVG 
*        but we can see that QS has O(n^2) in worst case when all elements are greater/smaller than pivot.
*        Qs and Hs are not stable ,and both are inplace.
*        The number of operations for insertion sort recursive vs iterative are the same but the execution time
*        is greater in the recursive approach than iterative.
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include"Profiler.h"

#define MAX_SIZE 10000
#define MAX_SIZE2 8000
#define STEP_SIZE 100
#define NO_TESTS 5
#define NO_TESTS2 100

Profiler HW3("HEAP vs QUICK");

void printArray(int* a, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void copyArray(int* source, int* destination, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		destination[i] = source[i];
	}
}

void insertionSort(int *a, int n, int n2)
{
	Operation opps = HW3.createOperation("OppsInsIte", n2);
	int min = 0, j = 0;
	int i;
	for (i = 1; i < n; i++)
	{
		min = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > min)
		{
			opps.count();
			a[j + 1] = a[j];
			opps.count();
			j--;
		}
		if (j >= 0)
		{
			opps.count();
		}
		a[j + 1] = min;
		opps.count();
	}
}

void insertionSortTime(int *a, int n)
{
	int min = 0, j = 0;
	int i;
	for (i = 1; i < n; i++)
	{
		min = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > min)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = min;
	}
}

void insertionSortDemo(int *a, int n)
{
	int min = 0, j = 0;
	int i;
	for (i = 1; i < n; i++)
	{
		printArray(a, n);
		min = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > min)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = min;
	}
	printArray(a, n);
}

void insertionSortRecursive(int* a, int n, int n2)
{
	Operation opps = HW3.createOperation("OppsInsRec", n2);

	if (n <= 1)
	{
		return;
	}
	insertionSortRecursive(a, n - 1, n2);
	int ultim = a[n - 1];
	int s = n - 2;
	while (s >= 0 && a[s] > ultim)
	{
		opps.count();
		a[s + 1] = a[s];
		opps.count();
		s--;
	}
	if (s >= 0)
	{
		opps.count();
	}
	opps.count();
	a[s + 1] = ultim;
}
#pragma optimize( "", off )
void insertionSortRecursiveTime(int* a, int n)
{
	if (n <= 1)
	{
		return;
	}
	insertionSortRecursiveTime(a, n - 1);
	int ultim = a[n - 1];
	int s = n - 2;
	while (s >= 0 && a[s] > ultim)
	{
		a[s + 1] = a[s];
		s--;
	}
	a[s + 1] = ultim;
}
#pragma optimize( "", on )
void insertionSortRecursiveDemo(int* a, int n)
{
	if (n <= 1)
	{
		return;
	}
	insertionSortRecursiveTime(a, n - 1);
	int ultim = a[n - 1];
	int s = n - 2;
	while (s >= 0 && a[s] > ultim)
	{
		a[s + 1] = a[s];
		s--;
	}
	a[s + 1] = ultim;
}

int partition(int* a, int low, int high, int n)
{
	Operation att = HW3.createOperation("AttPartition", n);
	Operation comp = HW3.createOperation("CompPartition", n);
	int pivot = a[low];
	int g = low - 1;
	int s = high + 1;
	while (1)
	{
		do 
		{ 
			comp.count();
			g++;
		} while (a[g] < pivot);

		do
		{
			comp.count();
			s--;
		} while (a[s] > pivot);

		if (g >= s)
		{
			return s;
		}
		att.count(3);
		swap(&a[g], &a[s]);
	}
}

void quickSort(int* a, int l, int r, int n)
{
	if (l >= r)
	{
		return;
	}
	int pivot = partition(a, l, r,n);
	quickSort(a, l, pivot,n);
	quickSort(a, pivot + 1, r,n);
}

void quickSortDemo(int* a, int l, int r, int n)
{
	if (l >= r)
	{
		return;
	}
	int pivot = partition(a, l, r, n);
	printArray(a, n);
	quickSortDemo(a, l, pivot, n);
	quickSortDemo(a, pivot + 1, r, n);
}

void heapify(int* a, int n, int i, int n2)
{
	Operation att = HW3.createOperation("AttHeapify", n2);
	Operation comp = HW3.createOperation("CompHeapify", n2);
	int max = i;
	int left = (2 * i) + 1;
	int right = (2 * i) + 2;
	comp.count();
	if (left < n && a[left] > a[max])
	{
		max = left;
	}
	comp.count();
	if (right < n && a[right] > a[max])
	{
		max = right;
	}
	if (max != i)
	{
		swap(&a[i], &a[max]);
		att.count(3);
		heapify(a, n, max, n2);
	}
}

void buildHeap(int* a, int n, int n2)
{
	int i;
	for (i = (n / 2) - 1; i >= 0; i--)
	{
		heapify(a, n, i, n2);
	}
}

void heapSort(int* a, int n)
{
	Operation att = HW3.createOperation("AttHS", n);
	Operation comp = HW3.createOperation("CompHS", n);
	int g;
	buildHeap(a, n, n);
	for (g = n - 1; g >= 0; g--)
	{
		swap(&a[g], &a[0]);
		att.count(3);
		heapify(a, g, 0, n);
	}
}

void heapSortDemo(int* a, int n)
{
	int g;
	buildHeap(a, n, n);
	for (g = n - 1; g >= 0; g--)
	{
		swap(&a[g], &a[0]);
		heapify(a, g, 0, n);
		printArray(a, n);
	}
	printArray(a, n);
}

void DemoSort(int* a, int n, int caseJS)
{
	switch (caseJS)
	{
	case 1: quickSortDemo(a, 0, n-1, n);
		break;
	case 2: heapSortDemo(a, n);
		break;
	case 3:insertionSortDemo(a, n);
		break;
	case 4:insertionSortRecursiveDemo(a, n);
		break;
	default:
		printf("Please try 9 for exit\n");
		break;
	}
}

int main()
{
	//int caseSort = 0;
	//int demoARR[] = { 10,2,3,4,5, 7, 2, 8, 99, 23 };
	////int demoARR[] = { 1,2,3 };
	//int demoDimension = sizeof(demoARR) / sizeof(int);
	//int auxARR[256];
	//while (caseSort != 9)
	//{
	//	printf("\n");
	//	printf("[******************************************]\n");
	//	printf("Input the wanted algorithm \n 1-QS \n 2-HS \n 3-IS  \n 4-Is_REC \n Or 9 to exit \n");
	//	scanf("%d", &caseSort);
	//	copyArray(demoARR, auxARR, demoDimension);
	//	printArray(demoARR, demoDimension);
	//	DemoSort(demoARR, demoDimension, caseSort);
	//	printArray(demoARR, demoDimension);
	//	copyArray(auxARR, demoARR, demoDimension);
	//	printf("\n");
	//}

	int ARRAY[MAX_SIZE];
	int ARRAY_AUX[MAX_SIZE];
	int g = 0;
	int s = 0;

	for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
	{
		FillRandomArray(ARRAY, g, 10, 1000000, true, 0);
		
		quickSort(ARRAY, 0, g, g);

		FillRandomArray(ARRAY_AUX, g, 10, 1000000, true, 2);

		heapSort(ARRAY_AUX, g);

	}
	HW3.addSeries("TotalQSBest", "AttPartition", "CompPartition");
	
	HW3.addSeries("OppsHSBest", "AttHS", "CompHS");
	HW3.addSeries("OppsHeapifyBest", "AttHeapify", "CompHeapify");

	HW3.addSeries("OppsHeapSortBest", "OppsHSBest", "OppsHeapifyBest");

	HW3.createGroup("OppsBest", "TotalQSBest","OppsHeapSortBest");

	HW3.reset("CASE BEST");

     for (s = 0;s <= NO_TESTS; s++)
	  {
		for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
		{
			FillRandomArray(ARRAY, g, 10, 1000000, true, 0);
			copyArray(ARRAY, ARRAY_AUX, g);

			heapSort(ARRAY_AUX, g);

			copyArray(ARRAY, ARRAY_AUX, g);

			quickSort(ARRAY_AUX, 0, g, g);

		}
	 }
	HW3.divideValues("AttPartition", NO_TESTS);
	HW3.divideValues("CompPartition", NO_TESTS);
	HW3.divideValues("AttHeapify", NO_TESTS);
	HW3.divideValues("CompHeapify", NO_TESTS);
	HW3.divideValues("AttHS", NO_TESTS);
	HW3.divideValues("CompHS", NO_TESTS);

	HW3.addSeries("OppsHS", "AttHS", "CompHS");
	HW3.addSeries("OppsHeapify", "AttHeapify","CompHeapify");

	HW3.addSeries("OppsHeapSortAVG", "OppsHS", "OppsHeapify");

	HW3.addSeries("OppsQSAVG", "AttPartition", "CompPartition");

	HW3.createGroup("TotalAVG", "OppsHeapSortAVG", "OppsQSAVG");

	HW3.reset("CASE AVG");

	for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
	{
		FillRandomArray(ARRAY, g, 10, 1000000, true, 1);
		
		copyArray(ARRAY, ARRAY_AUX, g);
		heapSort(ARRAY_AUX, g);

		copyArray(ARRAY, ARRAY_AUX, g);
		quickSort(ARRAY_AUX, 0, g, g);

		
	}
	HW3.addSeries("TotalQSWorst", "AttPartition", "CompPartition");

	HW3.addSeries("OppsHSWorst", "AttHS", "CompHS");
	HW3.addSeries("OppsHeapifyWorst", "AttHeapify", "CompHeapify");

	HW3.addSeries("OppsHeapSortWorst", "OppsHSWorst", "OppsHeapifyWorst");

	HW3.createGroup("OppsWORST", "TotalQSWorst","OppsHeapSortWorst");
	HW3.createGroup("OppsWORST-Heap", "OppsHeapSortWorst");

	HW3.reset("CASE Worst");
	
	/*for (s = 0; s <= NO_TESTS2; s++)
	{
		for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
		{
			FillRandomArray(ARRAY, g, 10, 100000, true, 0);
			copyArray(ARRAY, ARRAY_AUX, g);

			HW3.startTimer("array_ite", g);
			insertionSortTime(ARRAY_AUX, g);
			HW3.stopTimer("array_ite", g);

			copyArray(ARRAY, ARRAY_AUX, g);

			HW3.startTimer("array_rec", g);
			insertionSortRecursiveTime(ARRAY_AUX, g);
			HW3.stopTimer("array_rec", g);
		}
	}
	
	HW3.createGroup("AVG_execINS", "array_rec", "array_ite");
    
	
	for (s = 0; s <= NO_TESTS; s++)
	{
		for (g = STEP_SIZE; g <= MAX_SIZE2; g += STEP_SIZE)
		{
			FillRandomArray(ARRAY, g, 10, 100000, true, 0);
			copyArray(ARRAY, ARRAY_AUX, g);
			insertionSort(ARRAY_AUX, g, g);

			copyArray(ARRAY, ARRAY_AUX, g);
			insertionSortRecursive(ARRAY_AUX, g, g);
		}
	}
	HW3.divideValues("OppsInsIte", NO_TESTS);
	HW3.divideValues("OppsInsRec", NO_TESTS);


	HW3.createGroup("AVG_oppsINS", "OppsInsIte", "OppsInsRec");
	
	HW3.showReport();*/

	return 0;
}