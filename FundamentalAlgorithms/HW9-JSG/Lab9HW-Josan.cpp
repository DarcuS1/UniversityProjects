/**
*
*@ Gelu-Samuel Josan
* @ group 30421
*
You are required to implement correctly and efficiently the base operations for disjoint set
(chapter 21.1 from book ) and the Kruskal’s algorithm (searching for the minimum spanning 1
tree - chapter 23.2) using disjoint sets.


*   Personal Interpretation:
*
*               
                We initialize disjoint sets for all the possible vertices, then we sort the graph edges
                then we take them starting from minimum and use findset and union to assemble the mst
                The find and union functions can take O(V) worst time
                In kruskal the sort is bubble, so O(n^2) worst
                The make operation is constant, O(1)
                Auxiliary space is O(V + E)

                A disjoint-set forest with union by rank and path compression can perform 
                a sequence of m MAKE-SET, UNION, and FIND-SET operations in worst-case time O(m * alpha(n)) 
                
* 
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include"Profiler.h"

Profiler HW9("DSETS");

#define MAX_SIZE 200
#define STEP_SIZE 10
#define NO_TESTS 5
#define n 500

int matrix[MAX_SIZE][MAX_SIZE];

typedef struct DSet
{
    DSet* parent;
    int rank;
}DSet;

void makeSet(DSet* currentSet)
{
    currentSet->parent = currentSet;
    currentSet->rank = 0;
}
void makeSet2(DSet* currentSet, int n2)
{
    Operation opp = HW9.createOperation("makeSetOpp", n2);
    opp.count(2);
    currentSet->parent = currentSet;
    currentSet->rank = 0;
}

void linkDSet(DSet* currentSet, DSet* setToUnite)
{
    if (currentSet->rank > setToUnite->rank)
    {
        setToUnite->parent = currentSet;
    }
    else
    {
        currentSet->parent = setToUnite;
        if (currentSet->rank == setToUnite->rank)
        {
            setToUnite->rank++;
        }
    }
}
void linkDSet2(DSet* currentSet, DSet* setToUnite, int n2)
{
    Operation opp = HW9.createOperation("linkSetOpp", n2);
    opp.count();
    if (currentSet->rank > setToUnite->rank)
    {
        opp.count();
        setToUnite->parent = currentSet;
    }
    else
    {
        opp.count();
        currentSet->parent = setToUnite;
        opp.count();
        if (currentSet->rank == setToUnite->rank)
        {
            opp.count();
            setToUnite->rank++;
        }
    }
}

DSet* findDSet(DSet* currentSet)
{
    if (currentSet != currentSet->parent)
    {
        currentSet->parent = findDSet(currentSet->parent);
    }
    return currentSet->parent;
}
DSet* findDSet2(DSet* currentSet, int n2)
{
    Operation opp = HW9.createOperation("findSetOpp", n2);
    opp.count();
    if (currentSet != currentSet->parent)
    {
        opp.count();
        currentSet->parent = findDSet2(currentSet->parent,n2);
    }
    return currentSet->parent;
}

void unionDSet(DSet* currentSet, DSet* setToUnite)
{
    linkDSet(findDSet(currentSet), findDSet(setToUnite));
}
void unionDSet2(DSet* currentSet, DSet* setToUnite,int n2)
{
    linkDSet2(findDSet2(currentSet,n2), findDSet2(setToUnite,n2),n2);
}

typedef struct GraphEdge
{
    int headVertex;
    int tailVertex;
    int weight;
    
}GraphEdge;

int computeEdgeValue(const void* a, const void* b)
{
    GraphEdge* edgeA1 = (GraphEdge*)a;
    GraphEdge* edgeB1 = (GraphEdge*)b;
    return edgeB1->weight - edgeA1->weight;
}

void sortArrayOfGraphEdges(GraphEdge* array, int arraySize)
{
    int i, j;
    for (i = 0; i < arraySize - 1; i++)
    {
        for (j = 0; j < arraySize - i - 1; j++)
        {

            if (array[j].weight > array[j + 1].weight)
            {
                GraphEdge temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

GraphEdge* kruskal(GraphEdge* edges, int numEdges, int numVertices)
{
    DSet* sets = (DSet*)malloc(numVertices * sizeof(DSet));
   // DSet* sets = new DSet;
    int i;
    for (i = 0; i < numVertices; i++) 
    {
        makeSet(&sets[i]);
    }

   // qsort(edges, numEdges, sizeof(GraphEdge), computeEdgeValue);
    sortArrayOfGraphEdges(edges, numEdges);
    GraphEdge* mst = (GraphEdge*)malloc(numVertices * sizeof(GraphEdge));
   // GraphEdge* mst = new GraphEdge;
    int mstIndex = 0;

    for ( i = 0; i < numEdges; i++) 
    {
        GraphEdge edge = edges[i];
        int u = edge.headVertex;
        int v = edge.tailVertex;
        int weight = edge.weight;

        if (findDSet(&sets[u]) != findDSet(&sets[v])) 
        {
            mst[mstIndex++] = edge;
            unionDSet(&sets[u], &sets[v]);
        }
    }
    return mst;
}
GraphEdge* kruskal2(GraphEdge* edges, int numEdges, int numVertices, int n2)
{
    DSet* sets = (DSet*)malloc(numVertices * sizeof(DSet));
    for (int i = 0; i < numVertices; i++) 
    {
        makeSet2(&sets[i],n2);
    }

    qsort(edges, numEdges, sizeof(GraphEdge), computeEdgeValue);

    GraphEdge* mst = (GraphEdge*)malloc(numVertices * sizeof(GraphEdge));
    int mstIndex = 0;

    for (int i = 0; i < numEdges; i++)
    {
        GraphEdge edge = edges[i];
        int u = edge.headVertex;
        int v = edge.tailVertex;
        int weight = edge.weight;
        if (findDSet2(&sets[u],n2) != findDSet2(&sets[v],n2)) 
        {
            mst[mstIndex++] = edge;
            
            unionDSet2(&sets[u], &sets[v],n2);
        }
    }
    return mst;
}

void printDSet(DSet* set, int numElements)
{
    for (int i = 0; i < numElements; i++) {
        DSet* elem = &set[i];
        DSet* rep = findDSet(elem);
            printf("Element %d has rank %d\n", i, elem->rank);
        
    }
}

bool chechIFConnected(int n1, int matrix[][MAX_SIZE]) {
 
    bool visited[MAX_SIZE];
    int queue[MAX_SIZE];
    int front = 0;
    int rear = 0;
    for (int i = 0; i < n1; i++) 
    {
        visited[i] = false;
    }
    visited[0] = true;
    queue[rear] = 0;
    rear++;
    while (front < rear) 
    {
        int u = queue[front];
        front++;
        for (int v = 0; v < n1; v++) 
        {
            if (matrix[u][v] != 0 && !visited[v]) 
            {
                visited[v] = true;
                queue[rear] = v;
                rear++;
            }
        }
    }
    for (int i = 0; i < n1; i++) 
    {
        if (!visited[i]) 
        {
            return false;
        }
    }
    return true;
}

int noOf1s(int n1, int matrix[][MAX_SIZE]) {
    int count = 0;
    for (int i = 0; i < n1; i++) {
    
        for (int j = 0; j < n1; j++) {
            if (matrix[i][j] == 1) {
             
                count++;
            }
        }
    }
    return count;
}

void createAdjBinMatrix(int n1, int matrix[][MAX_SIZE]) {
    srand(time(0));
    int num_ones = 0;
    int i, j;
    for (i = 0; i < n1; i++) {

        for (j = 0; j < n1; j++) {

            matrix[i][j] = 0;

        }
    }
    while (noOf1s(n1, matrix) < (4 * n1) )
    {
        i = rand() % n1;
        j = rand() % n1;
        matrix[i][j] = 1;
       // matrix[j][i] = 1;
    }
    if (noOf1s(n1, matrix) > (4 * n1))
    {
        matrix[j][i] = 0;
    }
}

void makeEdgesWGraph(GraphEdge edges[], int n1, int matrix[][MAX_SIZE])
{
    int i;
    int s = 0;
    int j;
    int aa = 0;
    createAdjBinMatrix(n1, matrix);
    if (chechIFConnected(n1, matrix))
    {
        for (i = 0; i < n1; i++) {
            srand(time(0));
            for (j = 0; j < n1; j++) {

                if (matrix[i][j] == 1)
                {
                    edges[s].headVertex = j;
                    edges[s].tailVertex = i;
                    edges[s].weight = aa;
                    s++;
                }
                aa = (rand() % 500);
            }
        }
    }
    else
    {
        while (!chechIFConnected(n1, matrix))
        {
            createAdjBinMatrix(n1, matrix);
        }
        for (i = 0; i < n1; i++) {
            srand(time(0));
            for (j = 0; j < n1; j++) {

                if (matrix[i][j] == 1)
                {
                    edges[s].headVertex = j;
                    edges[s].tailVertex = i;
                    edges[s].weight = aa;
                    s++;
                }
                aa = (rand() % 500);
            }
        }

    }
}

void printBinMatrix(int n1, int matrix[][MAX_SIZE]) {

    for (int i = 0; i < n1; i++) {

        for (int j = 0; j < n1; j++) {

            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }

    if (chechIFConnected(n1, matrix)) {
        printf("The graph is connected\n");
    }
    else {
        printf("The graph is not connected\n");
    }
    std::cout << noOf1s(n1, matrix)<<std::endl;
}

void demo1()
{
    DSet sets[10];

    for (int i = 0; i < 10; i++) {
        makeSet(&sets[i]);
    }
    std::cout << "Union 0 and 1" << std::endl;
    unionDSet(&sets[0], &sets[1]);
    std::cout << "Union 2 and 3" << std::endl;
    unionDSet(&sets[2], &sets[3]);
    std::cout << "Union 0 and 2" << std::endl;
    unionDSet(&sets[0], &sets[2]);

    if (findDSet(&sets[0]) == findDSet(&sets[3])) {
        printf("Elements 0 and 3 are in the same set\n");
    }
    else {
        printf("Elements 0 and 3 are in different sets\n");
    }

    if (findDSet(&sets[0]) == findDSet(&sets[2])) {
        printf("Elements 0 and 2 are in the same set\n");
    }
    else {
        printf("Elements 0 and 2 are in different sets\n");
    }

    if (findDSet(&sets[1]) == findDSet(&sets[3])) {
        printf("Elements 1 and 3 are in the same set\n");
    }
    else {
        printf("Elements 1 and 3 are in different sets\n");
    }

    if (findDSet(&sets[5]) == findDSet(&sets[6])) {
        printf("Elements 5 and 6 are in the same set\n");
    }
    else {
        printf("Elements 5 and 6 are in different sets\n");
    }

}

void demo2()
{
    std::cout << "We have the following graph" << std::endl;
    std::cout<<"   "
             " 10\n"
      "  0--------1--\\  2\n"
      "  |  \     |    \\  \n"
      " 6|   5\   |15   | 4\n"
      "  |      \ |    / \n"
      "  2--------3--/  3\n"
          "    4     \n"
    <<std::endl;
    GraphEdge edges[] = 
    {
            {0, 1, 10},
            {1, 3, 15},
            {2, 3, 4},
            {2, 0, 6},
            {1, 4, 2},
            {0, 3, 5},
            {4, 3, 3}
           
    };
        int numEdges = 7;
        int numVertices = 5;

        GraphEdge* mst = kruskal(edges, numEdges, numVertices);

        printf("The edges in the MST are:\n");
        for (int i = 0; i < numVertices - 1; i++) {
            GraphEdge edge = mst[i];
            printf("(%d, %d) with weight %d\n", edge.headVertex, edge.tailVertex, edge.weight);
        }
}

void demo3()
{
    int n1 = 10;
    createAdjBinMatrix(n1, matrix);
    printBinMatrix(n1, matrix);
}

void profilerTasks()
{
    int j=0;
    int i=0;
    int s=0;
    GraphEdge edges[4*MAX_SIZE];
    int numEdges;
    int numVertices;
    GraphEdge* mst;
    for (j = 0; j < NO_TESTS; j++)
    {
        for (s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
        {
            makeEdgesWGraph(edges, s, matrix);
            numEdges = 4*s;
            numVertices = s;
            mst = kruskal2(edges, numEdges, numVertices,s);
        }
    }
    HW9.divideValues("makeSetOpp", NO_TESTS);
    HW9.divideValues("linkSetOpp", NO_TESTS);
    HW9.divideValues("findSetOpp", NO_TESTS);

    HW9.createGroup("MakeSet", "makeSetOpp");
    HW9.createGroup("LinkSet", "linkSetOpp");
    HW9.createGroup("FindSet", "findSetOpp");

    HW9.showReport();
}

int main()
{
   // demo1();
   // demo3();
  //  demo2();
    //profilerTasks();
    return 0;
}

