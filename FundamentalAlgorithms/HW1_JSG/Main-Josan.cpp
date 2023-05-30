/**
 * @author Gelu-Samuel Josan
 * @group 30421
 *
 * Assignment requirements: Implement and compare Bubble-sort, Insertion-sort and Selection-sort
 *
 * Personal interpretation :
 *     Bubble Sort : compare each pair, using a sliding window approach and swap elemnets in the
 *                   correct position until no more iterations are needed
 *                   AVG : O(n^2)
 *                   WORST : O(n^2)--goes trough both loops to have a correct result,
 *                           we get this when array is sorted in reverse order from how we want it
 *                   BEST : O(n)- elements already sorted 
 * 
 *  *     Insertion Sort : have two parts of an array, one sorted then iterate through unsorted and place element at correct position in sorted parrt
 *                   AVG : O(n^2)
 *                   WORST : O(n^2)--goes through both loops to have a correct result,
 *                           we get this when array is sorted in reverse order from how we want it
 *                   BEST : O(n)- elements already sorted 
 * 
 *  *     Selection Sort : similar to insertion but now we take each smallest elemnt from unsorted part and put it in its place 
 *                   AVG : O(n^2)
 *                   WORST : O(n^2)--goes trough both loops to have a correct result,
 *                           we get this when array is sorted in reverse order from how we want it
 *                   BEST : O(n^2)--we go though both loops anyway
 * 
 *                   As we can see in our graphs in the best case we get a good result from bubble sort and insertion sort 
 *                   both having O(n) complexity while selection is slower ( at O(n^2)) but selection has 0 assignments where the other 2 have more 
 * 
 *                   In avearage case we see a continuation of the trend where selection has fewer assignments but  almost the 
 *                   same comparisons as bubble  ,
 *                   while insertion seems better than bubble 
 *                   
 * 
 *                   In worst case we see that the algorithms have almost the same comparisons while the total shows how bad bubble is
 * 
 *                   All things considered, we have the decider in stabilty where we have bubble and insertion stable while selection is not
 *                   Bubble is stable because of the less than inequality while insertion is stable beacause of the greater inequality, keeping 
 *                   elements in strict places
 *                   
 *                  Overall insertion sort seems a better algorithm beacuse of all things considered, such as how it performs in test cases and stability
 *                  while selection has the edge in low assignments cases.
 * 
 * 
 * 
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Profiler.h"

Profiler HW1("Sorting methods");

#define MAX_SIZE 10000
#define STEP_SIZE 100 
#define NO_TESTS 5


void PrintArray(int* a, int n)
{
	printf("\n a = ");
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");
}


void BubbleSort(int* a, int n)
{
	Operation comp = HW1.createOperation("ComparisonsBubble", n);
	Operation att = HW1.createOperation("AttributionsBubble", n);
	int temp = 0;
	bool ok;

	for(int i = 0; i < n - 1; i++)
	{
		ok = false;
		att.count();
		for (int j = 0; j < n - i - 1; j++)
		{
			comp.count();
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				ok = true;
				att.count(4);
			}
		}
		comp.count();
		if (ok == false)
		{
			break;
		}
	}
}

void BubbleSortDemo(int* a, int n)
{
	int temp = 0;
	bool ok;
	PrintArray(a, n);
	for (int i = 0; i < n - 1; i++)
	{
		ok = true;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				ok = false;
			}
		}
		PrintArray(a, n);
		if (ok == true)
		{
			break;
		}
	}
}

void SelectionSort(int* a, int n)
{
	Operation comp = HW1.createOperation("ComparisonsSelection", n);
	Operation att = HW1.createOperation("AttributionsSelection", n);
	int min = 0,temp = 0;

	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			comp.count();
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			temp = a[min];
			a[min] = a[i];
			a[i] = temp;
			att.count(3);
		}
	}
}

void SelectionSortDemo(int* a, int n)
{
	int min = 0, temp = 0;
	PrintArray(a, n);
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			temp = a[min];
			a[min] = a[i];
			a[i] = temp;
		}
		PrintArray(a, n);
	}
}

void InsertionSort(int* a, int n)
{
	Operation comp = HW1.createOperation("ComparisonsInsertion", n);
	Operation att = HW1.createOperation("AttributionsInsertion", n);
	int min = 0, j = 0 ;
	for (int i = 1; i < n; i++)
	{
		min = a[i];
		att.count();
		j = i - 1;
		
		while (j >= 0 && a[j] > min)
		{
			comp.count();
			a[j + 1] = a[j];
			att.count();
			j--;
		}
		if (j >= 0)
		{
			comp.count();
		}
		a[j + 1] = min;
		att.count();
	}
}

void InsertionSortDemo(int* a, int n)
{
	int min = 0, j = 0;
	PrintArray(a, n);
	for (int i = 1; i < n; i++)
	{
		min = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > min)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = min;
		PrintArray(a, n);
	}
}

void DemoSort(int* a, int n, int caseJS)
{
	switch (caseJS)
	{
	case 1: BubbleSortDemo(a, n);
		break;

	case 2: InsertionSortDemo(a, n);
		break;

	case 3:SelectionSortDemo(a, n);
		break;

	default :
		printf("Please try 9 for exit\n");
		break;
	}
}

void copyArray(int* source, int* destination, int n)
{
	for (int i = 0; i < n; i++)
	{
		destination[i] = source[i];
	}
}

int main()
{
	//int caseSort = 0;
	//int demoARR[] = { 1,5,7,34,-9,10,2,3,-4,99 };
	//int demoDimension = sizeof(demoARR) / sizeof(int);
	//int auxARR[256];
	//while (caseSort != 9)
	//{
	//	printf("\n");
	//	printf("[******************************************]\n");
	//	printf("Input the wanted algorithm \n 1-Bubble \n 2-Insertion \n 3-Selection \n Or 9 to exit \n");
	//	scanf("%d", &caseSort);
	//	copyArray(demoARR, auxARR, demoDimension);
	//	DemoSort(demoARR, demoDimension, caseSort);
	//	copyArray(auxARR, demoARR, demoDimension);
	//    printf("\n");
	//}

	int ARRAY[MAX_SIZE];
	int ARRAY_AUX[MAX_SIZE];

	//Best case
	for (int s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
	{
		FillRandomArray(ARRAY, s, 0, 1000000, false, 1);

		copyArray(ARRAY, ARRAY_AUX, s);

		BubbleSort(ARRAY_AUX, s);

		copyArray(ARRAY, ARRAY_AUX, s);

		InsertionSort(ARRAY_AUX, s);

		copyArray(ARRAY, ARRAY_AUX, s);

		SelectionSort(ARRAY_AUX, s);
	}


	HW1.createGroup("Op_Comp_best", "ComparisonsSelection", "ComparisonsInsertion", "ComparisonsBubble");
	HW1.createGroup("Op_Comp_best_BBL+INS", "ComparisonsInsertion", "ComparisonsBubble");

	HW1.createGroup("Op_Att_best", "AttributionsSelection", "AttributionsInsertion", "AttributionsBubble");

	HW1.createGroup("Op_Att_best-BBL+SEL", "AttributionsSelection", "AttributionsBubble");
	

	HW1.addSeries("Total_Operations-Ins_b", "ComparisonsInsertion", "AttributionsInsertion");
	HW1.addSeries("Total_Operations-Sel_b", "ComparisonsSelection", "AttributionsSelection");
	HW1.addSeries("Total_Operations-Bbl_b", "ComparisonsBubble", "AttributionsBubble");

	HW1.createGroup("Total_Best", "Total_Operations-Sel_b", "Total_Operations-Ins_b", "Total_Operations-Bbl_b");
	HW1.createGroup("Total_Best_INS+BBL", "Total_Operations-Ins_b", "Total_Operations-Bbl_b");

	HW1.reset("Best Case");

	//Worst case
	for (int s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
	{
		FillRandomArray(ARRAY, s, 0, 1000000, false, 2);

		copyArray(ARRAY, ARRAY_AUX, s);

		BubbleSort(ARRAY_AUX, s);

		copyArray(ARRAY, ARRAY_AUX, s);

		InsertionSort(ARRAY_AUX, s);

		copyArray(ARRAY, ARRAY_AUX, s);

		SelectionSort(ARRAY_AUX, s);
	}


	HW1.createGroup("Op_Comp_worst", "ComparisonsSelection", "ComparisonsInsertion", "ComparisonsBubble");

	HW1.createGroup("Op_Att-worst", "AttributionsSelection", "AttributionsInsertion", "AttributionsBubble");

	HW1.createGroup("Op_Att-worst_SEL", "AttributionsSelection");

	HW1.addSeries("Total_Operations-Ins_w", "ComparisonsInsertion", "AttributionsInsertion");
	HW1.addSeries("Total_Operations-Sel_w", "ComparisonsSelection", "AttributionsSelection");
	HW1.addSeries("Total_Operations-Bbl_w", "ComparisonsBubble", "AttributionsBubble");

	HW1.createGroup("Total_Worst", "Total_Operations-Sel_w", "Total_Operations-Ins_w", "Total_Operations-Bbl_w");

	HW1.reset("Worst Case");


	for (int i = 0; i < NO_TESTS; i++)
	{
		for (int s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
		{
			FillRandomArray(ARRAY, s);

			copyArray(ARRAY, ARRAY_AUX, s);

			BubbleSort(ARRAY_AUX, s);

			copyArray(ARRAY, ARRAY_AUX, s);

			InsertionSort(ARRAY_AUX, s);

			copyArray(ARRAY, ARRAY_AUX, s);

			SelectionSort(ARRAY_AUX, s);
		}
	}


	
	HW1.divideValues("ComparisonsSelection", NO_TESTS);
	HW1.divideValues("AttributionsSelection", NO_TESTS);

	
	HW1.divideValues("ComparisonsInsertion", NO_TESTS);
	HW1.divideValues("AttributionsInsertion", NO_TESTS);


	HW1.divideValues("ComparisonsBubble", NO_TESTS);
	HW1.divideValues("AttributionsBubble", NO_TESTS);


	HW1.createGroup("Op_Comp_average", "ComparisonsSelection", "ComparisonsInsertion", "ComparisonsBubble");

	HW1.createGroup("Op_Att_average", "AttributionsSelection", "AttributionsInsertion", "AttributionsBubble");
	HW1.createGroup("Op_Att_average_SEL", "AttributionsSelection");

	HW1.addSeries("Total_Operations-Ins_a", "ComparisonsInsertion", "AttributionsInsertion");
	HW1.addSeries("Total_Operations-Sel_a", "ComparisonsSelection", "AttributionsSelection");
	HW1.addSeries("Total_Operations-Bbl_a", "ComparisonsBubble", "AttributionsBubble");

	HW1.createGroup("Total-AVG", "Total_Operations-Sel_a", "Total_Operations-Ins_a", "Total_Operations-Bbl_a");

	HW1.createGroup("Total-AVG_INS", "Total_Operations-Ins_a");

	HW1.reset("Average Case");

}