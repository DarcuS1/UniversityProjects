/**
*
*@ Gelu-Samuel Josan
* @ group 30421
*
You are required to implement correctly and efficiently iterative and recursive binary tree
traversal, as well as a hibrid Quicksort.

*   Personal Interpretation:
*
*
*    For building the tree we use a divide et impera strategy, and get the mid element, then iterate trough all subsets, insertaing mids,
     so we get a balanced bst;
    
*    The traversals are O(n) because we iterate trough all the elements of an n node tree
*    Quicksort is a good algorithm but for small arrays it can be slower than others, so we use insert for that, because we can see that it performs better in 
*    the case with few elements, i found a 5-25 range to be the highest we should use insert over quick
* 
*    QS-O(nlgn), O(n^2)
*    Hybrid is better but still like QS if the array is big
* 
*    As we can see from the results of the execution time the iterative traversal is a bit better tha recursive but not by much,
*    and in the case of quickvs hybrid we can see that hybrid is quite good compared to qs normal form
*    
*
*/



#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
#include<stack>
#include"Profiler.h"
using namespace std;

Profiler HW8("TREEandSORTS");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NO_TESTS 100

int control = 0;

void printArray(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d  ", a[i]);
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

void insertSort(int array[], int n, int n1)
{
    Operation opps = HW8.createOperation("OppsInsIte", n1);
    int min = 0, j = 0;
    int i;
    for (i = 1; i < n; i++)
    {
        min = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > min)
        {
            opps.count();
            array[j + 1] = array[j];
            opps.count();
            j--;
        }
        if (j >= 0)
        {
            opps.count();
        }
        array[j + 1] = min;
        opps.count();
    }
}

int partition(int array[], int low, int high, int n)
{
    Operation opp = HW8.createOperation("OppPartition", n);

    //int pivot = a[low];
    int pivot = array[(low + high) / 2];
    int g = low - 1;
    int s = high + 1;
    while (1)
    {
        do
        {
            opp.count();
            g++;
        } while (array[g] < pivot);

        do
        {
            opp.count();
            s--;
        } while (array[s] > pivot);

        if (g >= s)
        {
            return s;
        }
        opp.count(3);
        swap(&array[g], &array[s]);
    }
}

int partition2(int array[], int low, int high, int n)
{
    Operation opp = HW8.createOperation("OppPartition2", n);
    //int pivot = a[low];
    int pivot = array[(low + high) / 2];
    int g = low - 1;
    int s = high + 1;
    while (1)
    {
        do
        {
            opp.count();
            g++;
        } while (array[g] < pivot);

        do
        {
            opp.count();
            s--;
        } while (array[s] > pivot);

        if (g >= s)
        {
            return s;
        }
        opp.count(3);
        swap(&array[g], &array[s]);
    }
}

void quickSort2(int array[], int l, int r, int n1)
{
    if (l >= r)
    {
        return;
    }
    int pivot = partition2(array, l, r, n1);
    quickSort2(array, l, pivot, n1);
    quickSort2(array, pivot + 1, r, n1);
}

void quickSort(int array[], int l, int r, int n1)
{
    if (l >= r)
    {
        return;
    }
    int pivot = partition(array, l, r, n1);
    quickSort(array, l, pivot, n1);
    quickSort(array, pivot + 1, r, n1);
}

typedef struct BT
{
    int key;
    BT* left;
    BT* right;
}BT;

void print_in_order(BT* root, int n)
{
    Operation opp = HW8.createOperation("InorderIte", n);
    BT* back = NULL;
    BT* nodCurr = root;
    while (nodCurr != NULL)
    {
        if (nodCurr->left == NULL)
        {
            opp.count();
            //cout << nodCurr->key<<" ";
            nodCurr = nodCurr->right;
        }
        else 
        {
            back = nodCurr->left;
            while (back->right != NULL && back->right != nodCurr)
            {
                back = back->right;
            }

            if (back->right == NULL)
            {
                back->right = nodCurr;
                nodCurr = nodCurr->left;
            }
            else
            {
                
                opp.count();
                //printf("%d ", nodCurr->key);
                back->right = NULL;
                nodCurr = nodCurr->right;
            }
        }
    }
}
void print_in_order2(BT* root, int n)
{
    BT* back = NULL;
    BT* nodCurr = root;
    while (nodCurr != NULL) 
    {
        if (nodCurr->left == NULL) 
        {
           // cout << nodCurr->key;
            nodCurr = nodCurr->right;
        }
        else {
            back = nodCurr->left;
            while (back->right != NULL && back->right != nodCurr)
            {
                back = back->right;
            }

            if (back->right == NULL) 
            {
                back->right = nodCurr;
                nodCurr = nodCurr->left;
            }
            else 
            {
                
               // printf("%d ", nodCurr->key);
                back->right = NULL;
                nodCurr = nodCurr->right;
            }
        }
    }
}


void inorder(BT* root, int n)
{
    Operation opp = HW8.createOperation("InorderRec", n);
    if (root == NULL)
    {
        return;
    }
    inorder(root->left, n);
    opp.count();
   // cout << root->key << " ";
    inorder(root->right, n);
}
#pragma optimize("",off)
void inorder2(BT* root, int n)
{
    if (root == NULL)
    {
        return;
    }
    inorder2(root->left, n);
    // cout << root->key << " ";
    inorder2(root->right, n);
}
#pragma optimize("",on)

BT* buildBT(int *array, int l, int r)
{

    if (l > r)
    {
        return NULL;
    }
        
    int mij = (l + r) / 2;

    BT* root = new BT{ array[mij],NULL,NULL };

    root->left = buildBT(array, l, mij - 1);
    root->right = buildBT(array, mij + 1, r);

    return root;
}

void hybridSort(int array[],int l, int r, int n)
{
    Operation opps = HW8.createOperation("HybridOpps", n);
    if (r - l <= control)
    {
        int min = 0, j = 0;
        int i;
        for (i = l + 1; i < r; i++)
        {
            min = array[i];
            j = i - 1;
            while (j >= 0 && array[j] > min)
            {
                opps.count();
                array[j + 1] = array[j];
                opps.count();
                j--;
            }
            if (j >= 0)
            {
                opps.count();
            }
            array[j + 1] = min;
            opps.count();
        }
    }
    else
    {
        if (l >= r)
        {
            return;
        }
        int pivot = partition(array, l, r, n);
        hybridSort(array, l, pivot, n);
        hybridSort(array, pivot + 1, r, n);
    }
}

void inorder_traversal(BT* root)
{
    BT* current = root;
    BT* prev = NULL;
    while (current != NULL) {
        if (current->left == NULL) {
            printf("%d ", current->key);
            current = current->right;
        }
        else {
            prev = current->left;
            while (prev->right != NULL && prev->right != current) {
                prev = prev->right;
            }

            if (prev->right == NULL) {
                prev->right = current;
                current = current->left;
            }
            else {
                prev->right = NULL;
                printf("%d ", current->key);
                current = current->right;
            }
        }
    }
}

void demo1()
{
    BT* root = NULL;
    int array[11] = { 0 };
    int n = sizeof(array) / sizeof(int);
    int i;
    for (i = 1; i <= n; i++)
    {
        array[i - 1] = i;
    }
    root = buildBT(array, 0, n - 1);

    print_in_order(root, n);
    cout << endl;
    inorder(root, n);
    cout << endl;

    FillRandomArray(array, 10, 0, 100, false, 0);
    cout << endl;
    printArray(array, n);
    quickSort(array, 0, 10, n);
    printArray(array, n);
    cout << endl;
    FillRandomArray(array, 10, 0, 100, false, 0);
    printArray(array, n);
    hybridSort(array, 0, 10, n);
    printArray(array, n);
}

void profilerTasks()
{
    int ARRAY[MAX_SIZE];
    int ARRAY_AUX[MAX_SIZE];
    int g = 0;
    int s = 0;
   /* for (s = 0; s <= NO_TESTS; s++)
    {
        FillRandomArray(ARRAY, MAX_SIZE, 10, 100000, false, 0);
        for (g = 0; g <= 30; g += 1)
        {
            control = g;
            copyArray(ARRAY, ARRAY_AUX, MAX_SIZE);
            hybridSort(ARRAY_AUX, 0, MAX_SIZE-1,g);
           
            copyArray(ARRAY, ARRAY_AUX, MAX_SIZE);
            quickSort2(ARRAY_AUX, 0, MAX_SIZE-1, g);
        }
        
    }
    HW8.divideValues("OppPartition", NO_TESTS);
    HW8.divideValues("HybridOpps", NO_TESTS);
    HW8.divideValues("OppPartition2", NO_TESTS);

    HW8.addSeries("TotalHybrid", "HybridOpps", "OppPartition");

    HW8.createGroup("TotalQS", "OppPartition2");

    HW8.createGroup("TotalQSHybrid", "TotalHybrid");

    HW8.createGroup("Total", "OppPartition2", "TotalHybrid");*/

    /*for (s = 0; s <= NO_TESTS; s++)
    {
        control=25;
        FillRandomArray(ARRAY, MAX_SIZE, 10, 100000, false, 0);
        for (g = 0; g <= 30; g += 1)
        {
            
            copyArray(ARRAY, ARRAY_AUX, MAX_SIZE);
            hybridSort(ARRAY_AUX, 0, g, g);
            
            copyArray(ARRAY, ARRAY_AUX, MAX_SIZE);
            quickSort2(ARRAY_AUX, 0, g, g);
        }

    }

    HW8.divideValues("OppPartition", NO_TESTS);
    HW8.divideValues("HybridOpps", NO_TESTS);
    HW8.divideValues("OppPartition2", NO_TESTS);

    HW8.addSeries("TotalHybrid2", "HybridOpps", "OppPartition");

    HW8.createGroup("TotalQS2", "OppPartition2");

    HW8.createGroup("TotalQSHybrid2", "TotalHybrid2");

    HW8.createGroup("Total2", "OppPartition2", "TotalHybrid2");*/

    /*
    for (g = STEP_SIZE; g <= 8000; g += STEP_SIZE)
    {
        BT* root = NULL;
        FillRandomArray(ARRAY, g, 10, 10000, true, 1);
        copyArray(ARRAY, ARRAY_AUX, g);
        root = buildBT(ARRAY_AUX, 0, g);

        HW8.startTimer("array_rec", g);
        for (s = 0; s <= 1000; s++)
        {
            inorder2(root, g);
        }
        HW8.stopTimer("array_rec", g);

        HW8.startTimer("array_ite", g);
        for (s = 0; s <= 1000; s++)
        {
            print_in_order2(root, g);
        }
        HW8.stopTimer("array_ite", g);

        delete root;
    }
    
    HW8.createGroup("AVG_execIN", "array_rec", "array_ite");

    
     
        for (g = STEP_SIZE; g <= 8000; g += STEP_SIZE)
        {
            FillRandomArray(ARRAY, g, 10, 100000, false, 1);
            control = 25;
            copyArray(ARRAY, ARRAY_AUX, g);

            HW8.startTimer("array_hybrid", g);
            for (s = 0; s <= 100; s++)
            {
                hybridSort(ARRAY_AUX, 0, g, g);
            }
            HW8.stopTimer("array_hybrid", g);

            copyArray(ARRAY, ARRAY_AUX, g);

            HW8.startTimer("array_qs", g);
            for (s = 0; s <= 100; s++)
            {
                quickSort2(ARRAY_AUX, 0, g, g);
            }
            HW8.stopTimer("array_qs", g);
        }
    
    HW8.createGroup("AVG_execQs-vs-Hy", "array_hybrid", "array_qs");

    for (s = 0; s <= NO_TESTS; s++)
    {
        for (g = STEP_SIZE; g <= 8000; g += STEP_SIZE)
        {
            BT* root = NULL;
            FillRandomArray(ARRAY, g, 10, 10000, true, 1);
            copyArray(ARRAY, ARRAY_AUX, g);
            root = buildBT(ARRAY_AUX, 0, g);
            inorder(root, g);
            print_in_order(root, g);
            delete root;
        }
    }
    HW8.divideValues("InorderRec", NO_TESTS);
    HW8.divideValues("InorderIte", NO_TESTS);
    HW8.createGroup("Print_oppsIte", "InorderIte");
    HW8.createGroup("Print_oppsrec", "InorderRec");

    HW8.createGroup("Total_Print", "InorderIte", "InorderRec");*/

    HW8.showReport();
}

int main()
{
    demo1();
   // profilerTasks();
    return 0;
}