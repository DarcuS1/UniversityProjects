/*
*@ Gelu-Samuel Josan
*@ group 30421
* Task: You are required to implement correctly and efficiently two methods for building a heap,
namely the bottom-up and the top-down strategies.
*  Personal Interpretation :
*       Cases :  
*        BuildHeapBttUP : Worst case O(n) 
*                         AVG case O(n)
* 
*        BuildHeapTD    : Worst case O(nlgn)
*                         AVG case O(nlgn)
* 
*        HeapSort       : Worst case O(nlgn)
*                       : AVG case O(nlgn)
* 
*        As we can see the bottom up approach is better in the average and worst cases with a large percentage, 
*        while in worst and average having a running complexity of about O(N) and Top Down has approximative O(nlgn) complexity 
*        TD being better in average case as the no. of sifts approaches a smaller value asimtotic to 1, rather than worst case where it is lgn
*        HeapSort is not stable 
*        
* 
*/


#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include"Profiler.h"
Profiler HW2("Heap Build and Sort");
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NO_TESTS 5

int parent(int i)
{
	return (i - 1)/ 2;
}

void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void copyArray(int* source, int* destination, int n)
{
	for (int i = 0; i < n; i++)
	{
		destination[i] = source[i];
	}
}

void printArray(int a[], int n)
{
	for (int j = 0; j < n; j++)
	{
		printf("%d ", a[j]);
	}
	printf("\n");
}

void heapify(int* a, int n, int i, int n2)
{
	Operation comp = HW2.createOperation("ComparisonsHeapify", n2);
	Operation att = HW2.createOperation("AssignmentsHeapify", n2);

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

void heapIncreaseKey(int* a, int i, int key, int n)
{
	Operation comp = HW2.createOperation("ComparisonsIncKEY", n);
	Operation att = HW2.createOperation("AssignmentsIncKEY", n);

	comp.count();
	if (key < a[i])
	{
		printf("Error!");
		exit(1);
	}
	att.count();
	while ((i > 0) && (a[parent(i)] < key))
	{
		comp.count();
		a[i] = a[parent(i)];
		att.count();
		i = parent(i);
	}
	if (i > 0)
	{
		comp.count();
	}
	a[i] = key;
	att.count();
}

void heapInsert(int* a, int &n, int key, int n2)
{
	Operation comp = HW2.createOperation("ComparisonsHINS", n2);
	Operation att = HW2.createOperation("AssignmentsHINS", n2);
	n++;
	a[n-1] = INT_MIN;
	att.count();
	heapIncreaseKey(a, n-1, key, n2);
}

void buildHeapTop(int* a, int n, int n_aux)
{ 
 	n = 0;
	for (int i = 0; i < n_aux; i++)
	{
		heapInsert(a, n, a[i], n_aux);
	}
}

void buildHeap(int* a, int n, int n2)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
	{
		heapify(a, n, i, n2);
	}
}

void heapSort(int* a, int n)
{
	Operation comp = HW2.createOperation("ComparisonsHeapSort", n);
	Operation att = HW2.createOperation("AssignmentsHeapSort ", n);
	buildHeap(a, n, n);
	for (int g = n - 1; g >= 0; g--)
	{
		swap(&a[g], &a[0]);
		att.count(3);
		heapify(a, g, 0, n);
	}
}

void buildHeapDemo(int* a, int n, int n2)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
	{
		printArray(a, n2);
		heapify(a, n, i, n2);
	}
	printArray(a, n2);
}

void buildHeapTopDemo(int* a, int n, int n_aux)
{
	
	n = 0;
	for (int i = 0; i < n_aux; i++)
	{
		printArray(a, n_aux);
		heapInsert(a, n, a[i], n_aux);
	}
	printArray(a, n_aux);
}

void heapSortDemo(int* a, int n)
{
	printArray(a, n);
	buildHeap(a, n, n);
	for (int g = n - 1; g >= 0; g--)
	{
		printArray(a, n);
		swap(&a[g], &a[0]);
		heapify(a, g, 0, n);
	}
}

void DemoSort(int* a, int n, int caseJS)
{
	switch (caseJS)
	{
	case 1: buildHeapDemo(a, n, n);
		break;
	case 2: buildHeapTopDemo(a, n, n);
		break;
	case 3:heapSortDemo(a, n);
		break;
	default:
		printf("Please try 9 for exit\n");
		break;
	}
}

int main()
{
	//int caseSort = 0;
	//int demoARR[] = { 1,2,3,4,5 };
	//int demoDimension = sizeof(demoARR) / sizeof(int);
	//int auxARR[256];
	//while (caseSort != 9)
	//{
	//	printf("\n");
	//	printf("[******************************************]\n");
	//	printf("Input the wanted algorithm \n 1-BuildHeapBtt \n 2-BuildHeapTD \n 3-HeapSort \n Or 9 to exit \n");
	//	scanf("%d", &caseSort);
	//	copyArray(demoARR, auxARR, demoDimension);
	//	DemoSort(demoARR, demoDimension, caseSort);
	//	copyArray(auxARR, demoARR, demoDimension);
	//	printf("\n");
	//}

	int ARRAY[MAX_SIZE];
	int ARRAY_AUX[MAX_SIZE];
	int g=0;
	int s=0;
	//Worst case
	for (s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
	{
		FillRandomArray(ARRAY, s, 0, 1000000, true, 1);

		copyArray(ARRAY, ARRAY_AUX, s);

		buildHeap(ARRAY_AUX, s, s);

		copyArray(ARRAY, ARRAY_AUX, s);

		buildHeapTop(ARRAY_AUX, s, s);
	}
	HW2.createGroup("CMP_TopDown", "ComparisonsHINS", "ComparisonsIncKEY");
	HW2.createGroup("ATT_TopDown", "AssignmentsHINS", "AssignmentsIncKEY");

	HW2.addSeries("CMP_TopDown", "ComparisonsHINS", "ComparisonsIncKEY");
	HW2.addSeries("ATT_TopDown", "AssignmentsHINS", "AssignmentsIncKEY");

	HW2.createGroup("Op_comp_worst", "ComparisonsHeapify", "CMP_TopDown");
	HW2.createGroup("Op_Att_worst", "AssignmentsHeapify", "ATT_TopDown");

	HW2.addSeries("Total_Operations-BottUp", "ComparisonsHeapify", "AssignmentsHeapify");
	HW2.addSeries("Total_Operations-TopDown", "CMP_TopDown", "ATT_TopDown");

	HW2.createGroup("Total_Worst", "Total_Operations-BottUp", "Total_Operations-TopDown");

    HW2.reset("test case 1");
	
	//Average case
	for (g = 0; g < NO_TESTS; g++)
	{
		for (s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
		{
			FillRandomArray(ARRAY, s);

			copyArray(ARRAY, ARRAY_AUX, s);

			buildHeap(ARRAY_AUX, s, s );

			copyArray(ARRAY, ARRAY_AUX, s);

			buildHeapTop(ARRAY_AUX, s, s);
		}
	}
	HW2.divideValues("ComparisonsHINS", NO_TESTS);
	HW2.divideValues("ComparisonsIncKEY", NO_TESTS);
	HW2.divideValues("AssignmentsHINS", NO_TESTS);
	HW2.divideValues("AssignmentsIncKEY", NO_TESTS);
	HW2.divideValues("ComparisonsHeapify", NO_TESTS);
	HW2.divideValues("AssignmentsHeapify", NO_TESTS);

	HW2.addSeries("CMP_TopDownAVG", "ComparisonsHINS", "ComparisonsIncKEY");
	HW2.addSeries("ATT_TopDownAVG", "AssignmentsHINS", "AssignmentsIncKEY");

	HW2.createGroup("Op_comp_AVG", "ComparisonsHeapify", "CMP_TopDownAVG");
	HW2.createGroup("Op_Att_AVG", "AssignmentsHeapify", "ATT_TopDownAVG");

	HW2.addSeries("Total_Operations-BottUpAVG", "ComparisonsHeapify", "AssignmentsHeapify");
	HW2.addSeries("Total_Operations-TopDownAVG", "CMP_TopDownAVG", "ATT_TopDownAVG");

	HW2.createGroup("Total_AVG", "Total_Operations-BottUpAVG", "Total_Operations-TopDownAVG");

	HW2.reset("test case 2");

	return 0;
}

