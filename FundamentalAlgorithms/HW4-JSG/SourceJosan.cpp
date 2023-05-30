/*
*@ Gelu-Samuel Josan
*@ group 30421
* You are required to implement correctly and efficiently an O(nlogk) method for merging k
sorted sequences, where n is the total number of elements. (Hint: use a heap, see seminar no. 2 notes).
*  Personal Interpretation :
*       Cases :
*        Heapify     :   O(lgn)
*
*        KwayMerge   :   O(nlgk)<->O(knlgk)
*
*        As we can see in every step try we make with a varaible length of the arrays the algorithm has O(nlogk) complexity,
*        we have the logk from heapify and k iterations of that trough k lists, and n iterations of n elements 
*        This is an out-place algorithm
* 
*        we build a min heap with the values of the lists, then extract from a dummy list the smallest element,
*        then we see in heapify if the element with the relative position is isn the smallest else we look for it through the lists, and
*        select that list to be the dummy first list, then repeat
*
*/
#include <stdio.h>
#include <stdlib.h>
#include"Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE2 10
#define STEP_SIZE 100
#define NO_TESTS 5
Profiler HW4("Klists merge");
typedef struct Node 
{
	int key;
	struct Node* next;
}Node;

typedef struct List 
{
	struct Node* first;
	struct Node* last;
}List;

void swapNode(Node** a, Node** b)
{
	Node* temp = *a;
	*a = *b;
	*b = temp;
}

Node* newNodes(int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = nullptr;
	newNode->key = data;
	return newNode;
}

void printList(Node* first) {
	struct Node* newNode = first;
	while (newNode != nullptr)
	{
		printf("%d -> ", newNode->key);
		newNode = newNode->next;
	}
	printf("NULL");
	printf("\n");
}

void insertLast(Node** first, Node** last, int data) {

	Node* newNode = newNodes(data);
	if (*last == nullptr)
	{
		*first = newNode;
		*last = *first;
	}
	else
	{
		(*last)->next = newNode;
		*last = newNode;
	}
}

void push(List* jsgList, int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(Node));
	newNode->key = data;
	newNode->next = jsgList->first;
	jsgList->first = newNode;
}

bool isEmpty(List* jsgList) {
	return jsgList->last == nullptr;
}

int pop(List* jsgList) {
	if (jsgList->first == nullptr)
	{
		return 0;
	}
	struct Node* newNode = jsgList->first;
	int value = jsgList->first->key;
	while (newNode != nullptr)
	{
		newNode = newNode->next;
	}
	free(newNode);
	return value;
}

void toList(List* jsgList, int arrList[], int k, int n)
{
	for (int j = 0; j < n / k; j++)
	{
		insertLast(&jsgList->first, &jsgList->last, arrList[j]);
	}
}

void getArray(List* jsgList, int k, int n)
{
	int arrayList[MAX_SIZE];
	FillRandomArray(arrayList, n / k, 10, 10000, false, ASCENDING);
	toList(jsgList, arrayList, k, n);
}

void Heapify(List* jsgLists[], int  i, int Hsize, int n, int n2) {

	Operation opps = HW4.createOperation("HeapifyOpps", n2);
	int min = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	opps.count();
	if (right < Hsize && jsgLists[right]->first->key < jsgLists[min]->first->key)
	{
		min = right;
	}
	opps.count();
	if (left < Hsize && jsgLists[left]->first->key < jsgLists[min]->first->key)
	{
		min = left;
	}
	if (min != i) {
		swapNode(&jsgLists[min]->first, &jsgLists[i]->first);
		opps.count(3);
		Heapify(jsgLists, min, Hsize, n, n2);
	}
}

void BuildHeap(List* jsgLists[], int Hsize, int n, int n2) {

	for (int i = (Hsize / 2 - 1); i >= 0; i--)
	{
		Heapify(jsgLists, i, Hsize, n, n2);
	}
}

void MinHeapKListMerge(List* jsgLists[], int k, int n, int n2)
{
	Operation opps = HW4.createOperation("KMergeOpps", n2);
	List* FinalList = (List*)malloc(sizeof(List));
	FinalList->first = nullptr;
	FinalList->last = nullptr;
	BuildHeap(jsgLists, k, n, n2);
	int heapsize = k;
	while (heapsize > 0) {
		Node* okNode = newNodes(1);
		opps.count();
		okNode = jsgLists[0]->first;
		opps.count();
		jsgLists[0]->first = jsgLists[0]->first->next;
		printf("The lists trough the algo: \n");
		printf("Final \n");
		printList(FinalList->first);
		printf("\n Source Lists :\n");
		for (int r = 0; r < k; r++)
		{
			printList(jsgLists[r]->first);
		}
		printf("\n");
		insertLast(&FinalList->first, &FinalList->last, okNode->key);
		opps.count();
		if (jsgLists[0]->first == nullptr)
		{
			free(jsgLists[0]->first);
			opps.count();
			jsgLists[0]->first = jsgLists[heapsize - 1]->first;
			heapsize--;
		}
		Heapify(jsgLists, 0, heapsize, n, n2);
	}
	printf("Final list:\n");
	printList(FinalList->first);
	free(FinalList->first);
}

void DemoMinHeapKListMerge(int k, int n)
{
	List* jsgLists1[10];
	for (int i = 0; i < k; i++)
	{
		jsgLists1[i] = (List*)malloc(sizeof(List));
		jsgLists1[i]->first = nullptr;
		jsgLists1[i]->last = nullptr;
		getArray(jsgLists1[i], k, n);
		printf("Initial Lists: \n");
		printList(jsgLists1[i]->first);
		printf("\n");
	}
	MinHeapKListMerge(jsgLists1, k, n, n);
}

int main()
{
	DemoMinHeapKListMerge(2, 10 * 2);
	/*List* jsgLists[MAX_SIZE];
	int g = 0;
	int s = 0;
	int i = 0;
	int k[] = { 5, 10, 100 };
	int kLen = sizeof(k) / sizeof(int);

	for (s = 0; s <= NO_TESTS; s++)
	{
		for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
		{
			for (i = 0; i < k[0]; i++)
			{
				jsgLists[i] = (List*)malloc(sizeof(List));
				jsgLists[i]->first = nullptr;
				jsgLists[i]->last = nullptr;
				getArray(jsgLists[i], k[0], g);
			}
			MinHeapKListMerge(jsgLists, k[0], g, g);
		}

	}
	HW4.divideValues("KMergeOpps", NO_TESTS);
	HW4.divideValues("HeapifyOpps", NO_TESTS);
	HW4.addSeries("OppsKWAY", "KMergeOpps", "HeapifyOpps");
	HW4.createGroup("TotalOpps", "OppsKWAY");
	for (s = 0; s <= NO_TESTS; s++)
	{
		for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
		{
			for (i = 0; i < k[1]; i++)
			{
				jsgLists[i] = (List*)malloc(sizeof(List));
				jsgLists[i]->first = nullptr;
				jsgLists[i]->last = nullptr;
				getArray(jsgLists[i], k[1], g);
			}
			MinHeapKListMerge(jsgLists, k[1], g, g);
		}

	}
	HW4.divideValues("KMergeOpps", NO_TESTS);
	HW4.divideValues("HeapifyOpps", NO_TESTS);
	HW4.addSeries("OppsKWAY2", "KMergeOpps", "HeapifyOpps");
	HW4.createGroup("TotalOpps2", "OppsKWAY2");
	for (s = 0; s <= NO_TESTS; s++)
	{
		for (g = STEP_SIZE; g <= MAX_SIZE; g += STEP_SIZE)
		{
			for (i = 0; i < k[2]; i++)
			{
				jsgLists[i] = (List*)malloc(sizeof(List));
				jsgLists[i]->first = nullptr;
				jsgLists[i]->last = nullptr;
				getArray(jsgLists[i], k[2], g);
			}
			MinHeapKListMerge(jsgLists, k[2], g, g);
		}

	}
	HW4.divideValues("KMergeOpps", NO_TESTS);
	HW4.divideValues("HeapifyOpps", NO_TESTS);
	HW4.addSeries("OppsKWAY3", "KMergeOpps", "HeapifyOpps");
	HW4.createGroup("TotalOpps3", "OppsKWAY3", "OppsKWAY2", "OppsKWAY");
	HW4.reset("Third_Case");*/
	/*g = MAX_SIZE;
	for (s = 0; s <= NO_TESTS; s++)
	{
		for (int k2 = 10; k2 <= 500; k2+=10)
		{
			for (i = 0; i < k2; i++)
			{
				jsgLists[i] = (List*)malloc(sizeof(List));
				jsgLists[i]->first = nullptr;
				jsgLists[i]->last = nullptr;
				getArray(jsgLists[i], k2, g);
			}
			MinHeapKListMerge(jsgLists, k2, g);
		}
	}
	HW4.divideValues("KMergeOpps", NO_TESTS);
	HW4.divideValues("HeapifyOpps", NO_TESTS);

	HW4.addSeries("OppsKWAY4", "KMergeOpps", "HeapifyOpps");

	HW4.createGroup("TotalKVariabil", "OppsKWAY4");
	HW4.reset("Fourth_Case");*/
	return 0;
}
