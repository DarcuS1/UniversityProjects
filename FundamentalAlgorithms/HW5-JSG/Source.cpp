/*
*@group 40321
*@student GELU-SAMUEL JOSAN
*
* Requierments :
* You are required to implement correctly and efficiently the insert and search operations in a hash table
* using open addressing and quadratic probing. You may find relevant information and pseudo-code in
* your course notes, or in the book (Cormen), in section 11.4 Open addressing.
*
* Personal interpretation:
*           As we can see in ost cases we can retrieve elements from a hash table in constant time beacause we just apply its hash function
*           but as the filling factor gets higher we see that it slows down this process beacuse there mught be room for collisions
*           in our case the elements were distributed through quadratic probing, which meant that we used a hash function that searches for
*           an empty slot with pretty good accuracy.
*           we observe that whilst the filling factor is going up the avg effort is also going up
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

#define SIZE 23
#define MAX_SIZE 10007
#define TRIAL_NO 3000
#define NO_TESTS 5

typedef struct {
	int id;
	char name[30];
}Entry;

Entry* item;
Entry* hashArray[MAX_SIZE];

const int c1 = 3;
const int c2 = 5;

void flagHashTable()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		if (hashArray[i] != NULL) {
			hashArray[i]->id = -1;
			//strcpy(hashArray[i]->name, "-1");
		}
	}
}

void flagHashTable2()
{
	for (int i = 0; i < SIZE; i++) {
		if (hashArray[i] != NULL) {
			hashArray[i]->id = -1;
			//strcpy(hashArray[i]->name, "-1");
		}
	}
}

int modHash(int key) {

	return key % MAX_SIZE;
}

int quadraHash(int key, int i)
{
	return (modHash(key) + c1 * i + c2 * i * i) % MAX_SIZE;
}


int modHash2(int key) {

	return key % SIZE;
}

int quadraHash2(int key, int i)
{
	return (modHash2(key) + c1 * i + c2 * i * i) % SIZE;
}

int insert(int key, char data[])
{
	int i = 0, j = 0;
	Entry* item = (Entry*)malloc(sizeof(Entry));
	strcpy(item->name, data);
	item->id = key;
	do
	{
		j = quadraHash(key, i);
		if (hashArray[j] == NULL || hashArray[j]->id == -1)
		{
			hashArray[j] = item;
			return j;
		}
		else
		{
			i++;
		}
	} while (i < MAX_SIZE);
	//perror("Overflow");
}

int insert2(int key, char data[])
{
	int i = 0, j = 0;
	Entry* item = (Entry*)malloc(sizeof(Entry));
	strcpy(item->name, data);
	item->id = key;
	do
	{
		j = quadraHash2(key, i);
		if (hashArray[j] == NULL || hashArray[j]->id == -1)
		{
			hashArray[j] = item;
			return j;
		}
		else
		{
			i++;
		}
	} while (i < SIZE);
	perror("Overflow");
}

int search(int key, int &maxEffort)
{
	int i = 0, j = 0;
	do
	{
		maxEffort++;
		j = quadraHash(key, i);
		if (hashArray[j] != NULL) 
		{
			if (hashArray[j]->id != -1)
			{
				if (hashArray[j]->id == key)
				{
					return j;
				}
			}
		}
		i++;
	} while (i < MAX_SIZE || hashArray == NULL);
	return NULL;
}

int search2(int key, int &i)
{
	int j = 0;
	do
	{
		i++;
		j = quadraHash2(key, i);
		if (hashArray[j] != NULL)
		{
			if (hashArray[j]->id != -1)
			{
				if (hashArray[j]->id == key)
				{
					return j;
				}
			}
		}
		
	} while (i < SIZE || hashArray == NULL);
	return NULL;
}


int delete1(int key) {

	int i = 0, j = 0;
	do
	{
		j = quadraHash(key, i);
		if (hashArray[j] != NULL) 
		{
			if (hashArray[j]->id != -1) 
			{
				if (hashArray[j]->id == key)
				{
					hashArray[j]->id = -1;
					return 1;
				}
			}
		}
		i++;
	} while (i < MAX_SIZE || hashArray == NULL);
	return NULL;
}

void display(int size)
{

	int i = 0;
	for (i = 0; i < size; i++)
	{
		if (hashArray[i] != NULL && hashArray[i]->id != -1) {
			printf(" (%d,%s)\n", hashArray[i]->id, hashArray[i]->name);
		}
		else {
			printf(" *~ \n");
		}
		
	}
	printf("\n\n\n");
}

void fillRationFinder() {
	int verify;
	float c = 0.0;
	int aka = 0;
	for (int j = 0; j < MAX_SIZE; j++) {
		if (hashArray[j] != NULL) {
			verify = search(hashArray[j]->id, aka);
			if (verify != NULL) {
				c++;
			}
		}
	}
	printf("\n Fill: %.2f", c / MAX_SIZE);
}



void demo()
{
	int valid;
	int i = 0, j = 0;
	int valid_dummy = 0 ;
	char dummyText[] = "el_a";
	for (i = 1; i < 21; i+=2)
	{
		insert(i, dummyText);
		dummyText[3]++;
	}
	display(20);
	for (j = 0; j < 30; j ++)
	{
		valid = search(j, valid_dummy);
		if (valid != NULL)
		{
			printf("\n Found the element :%s\n", hashArray[j]->name);
		}
		else
		{
			printf("\nElement: % d not found\n", j );
		}

	}
	for (i = 1; i < 11; i += 2)
	{
		delete1(i);
	}
	display(20);

	insert(9, dummyText);

	display(20);
	dummyText[3]++;

	insert(7, dummyText);

	display(20);
	dummyText[3]++;

	insert(5, dummyText);

	display(20);
	dummyText[3]++;
}

void singleFill()
{
	double avgFound=0.0;
	double maxFound=0.0;
	double avgNot=0.0; 
	double  maxNot = 0.0;
	double avg1; 
	double avg2; 
	double avg11;
	double avg22;

	float fillingFactor = 0.8;
	float fakeSize;
	char randChar[]="mama";
	int t, z=100;

	for (int i = 0; i < NO_TESTS; i++) 
	{
		fakeSize = fillingFactor * SIZE;
		for (t = 0; t < fakeSize / 2; t++)
		{
			insert2(t, randChar);
			randChar[3]++;
		}
		for (t = 0; t < fakeSize / 2; t++)
		{
			insert2(z, randChar);
			z++;
			randChar[3]++;
		}
		display(SIZE);
		int searchFound = 0;
		for (t = 0; t < fakeSize; t++)
		{
			search2(t, searchFound);
			avgFound += searchFound;
		}
		searchFound = 0;
		for (t = 0; t< fakeSize; t++)
		{
			search2(z*z, searchFound);
			avgNot += searchFound;
		}
		flagHashTable2();
	}

	avg1 = avgFound / fakeSize/2;
	avg2 = avgNot / fakeSize/2;

	avg11 = avg1 / 5;
	avg22 = avg2 / 5;

	printf("\nFilling factor : %.2f, avg found %.2lf, avg not found %.2lf\n", fillingFactor, avg11, avg22);
}

void testSearch()
{
	double fFactor[] = { 0.8, 0.85, 0.9 , 0.95, 0.99 };
	double fakeSize;
	char randTEXT[] = "randA";
	int i, k, j, alfa;
	alfa = MAX_SIZE + 1;

	double no_find;
	double no_no_find;

	double total1;
	double total2;

	double total11;
	double total22;

	for (i = 0; i < 5; i++)
	{
		fakeSize = fFactor[i] * MAX_SIZE;
		for (k = 0; k < 5; k++)
		{
			int get_no = 0;
			for (j = 0; j < fakeSize; j++)
			{
				insert(j, randTEXT);
			}
			for (j = 1500; j < 3000; j++)
			{
				search(j, get_no);
				no_find += get_no;
			}
			for (j = 10007; j < 11519; j++)
			{
				search(j , get_no);
				no_no_find += get_no;
			}
		}
		total1 = no_find / 5;
		total2 = no_no_find / 5;

		no_find = 0.0;
		no_no_find = 0.0;

		total11 = total1 / MAX_SIZE;
		total22 = total2 / MAX_SIZE;

		flagHashTable();

		printf("\nFill: %f, avg found : %lf, avg nofound :%lf\n", fFactor[i], total11, total22);
	}
}

int main()
{
	//testSearch();
	//demo();
	singleFill();
}