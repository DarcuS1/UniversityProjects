/**
*
*@ Gelu-Samuel Josan
* @ group 30421
*
* In this session you are required to implement and analyse DFS (depth-First
Search), as presented in section 23 of Introduction to Algorithms by Th. Cormen et a

Personal Interpretation
			DFS:
			we start by initializing all nodes, with -1 for time, indexes, adn whit WHITE color, then wee go recursevely on depth
			to teh next in depth neighborn of the node
			The complexity of this algorithm is O(V+E)

			For topological sort we just sort the finializeing times
			We ca use dfs to find the connex components also,,but we also have tarjan
*
*/

#include<iostream>
#include<stack>
#include<list>
#include<algorithm>

#include<stdlib.h>
#include<stdio.h>
#include "Profiler.h"

using namespace std;

Profiler HW11("DFS-TARJAN");
#define STEP_SIZE 100
#define STEP_SIZE2 10
#define NO_TESTS 5

int timeT = 0;

enum COLOR_TYPE
{
	WHITE,
	GRAY,
	BLACK
};

typedef struct Node
{
	int key;
	int no_neighb;
	Node** adjNodes;
	int timeToFind;
	int timeToFinalize;
	int index;
	int lowIndex;
	COLOR_TYPE color;
	int presentOnStack;
	Node* dad;
	int CMP;
	Node* next;
}Node;

stack<Node*> dfsStack;

typedef struct Graph
{
	int noNodes;
	Node** v;
}Graph;

int index = 0;

Graph* dfsGraph;

Node* createNode(int key)
{
	Node* node = new Node;
	node->key = key;
	node->no_neighb = 0;
	node->adjNodes = NULL;
	node->timeToFind = -1;
	node->timeToFinalize = -1;
	node->index = -1;
	node->lowIndex = -1;
	node->color = WHITE;
	node->presentOnStack = 0;
	node->CMP = 0;
	node->next = NULL;
	return node;
}

Graph* createGraph(int noNodes)
{
	Graph* G = new Graph;
	G->noNodes = noNodes;
	G->v = new Node * [noNodes];
	for (int i = 0; i < noNodes; i++)
	{
		G->v[i] = createNode(i);
	}
	return G;
}

void addEdge(Graph* G,int u, int v)
{
	G->v[u]->no_neighb++;
	Node** adjNodes = new Node * [G->v[u]->no_neighb];
	for (int i = 0; i < G->v[u]->no_neighb - 1; i++)
	{
		adjNodes[i] = G->v[u]->adjNodes[i];
	}
	adjNodes[G->v[u]->no_neighb - 1] = G->v[v];
	delete[] G->v[u]->adjNodes;
	G->v[u]->adjNodes = adjNodes;
}

void printGraph( Graph* graph) {
	int v,i;
	for (v = 0; v < graph->noNodes; v++) {
		Node* temp = graph->v[v];
		printf("\n Vertex %d", v);
		for (i = 0; i < temp->no_neighb; i++)
		{
			printf(": %d ", temp->adjNodes[i]->key);
		}
		printf("\n");
	}
}

void initGraph(Graph* G)
{
	for (int i = 0; i < G->noNodes; i++)
	{
		G->v[i]->timeToFind = -1;
		G->v[i]->timeToFinalize = -1;
	}
	for (int i = 0; i < G->noNodes; i++)
	{
		G->v[i]->color = WHITE;
	}
	for (int i = 0; i < G->noNodes; i++)
	{
		G->v[i]->index = -1;
		G->v[i]->lowIndex = -1;
	}
	for (int i = 0; i < G->noNodes; i++)
	{
		G->v[i]->presentOnStack = 0;
	}
}

void DFSVisit(Node* u, int* time, stack<Node*> &S)
{
	std::cout << u->key << " ";
	dfsGraph ->v[index] = u;
	index++;
  u->color = GRAY;
  u->timeToFind = ++(*time);
  S.push(u);
  u->presentOnStack = 1;
  u->lowIndex = u->index = S.size() - 1;
  for (int i = 0; i < u->no_neighb; i++)
  {
    Node* v = u->adjNodes[i];
    if (v->color == WHITE)
    {
      DFSVisit(v, time, S);
      u->lowIndex = min(u->lowIndex, v->lowIndex);
    }
    else if (v->presentOnStack)
    {
      u->lowIndex = min(u->lowIndex, v->index);
    }
  }


  if (u->lowIndex == u->index)
  {

	  Node* w = NULL;
	  do
	  {
		  w = S.top();
		  S.pop();
		  w->presentOnStack = 0;
		 // cout << w->key << " ";
	  } while (w != u);
	  cout << endl;
	  dfsGraph ->v[index - 1]->CMP++;
  }

  u->color = BLACK;
  u->timeToFinalize = ++(*time);
}
void DFS(Graph* G)
{
	initGraph(G);
	int time = 0;
	stack<Node*> S;
	for (int i = 0; i < G->noNodes; i++)
	{
		
		if (G->v[i]->color == WHITE)
		{
			DFSVisit(G->v[i], &time, S);
		}
	}
}

void getDFSgraph(Graph* G)
{
	int i;
	for (i = 0; i < G->noNodes-1; G++)
	{
		if (G->v[i]->CMP == 0) {
			addEdge(G, i, i + 1);
		}
	}
}

void DFSVisit2(Node* u, int* time, stack<Node*>& S, int n)
{
	Operation opp = HW11.createOperation("DFS-VISIT", n);

	u->color = GRAY;
	opp.count();
	u->timeToFind = ++(*time);
	opp.count();
	S.push(u);
	opp.count();
	u->presentOnStack = 1;
	opp.count();
	u->lowIndex = u->index = S.size() - 1;
	for (int i = 0; i < u->no_neighb; i++)
	{
		opp.count();
		Node* v = u->adjNodes[i];
		if (v->color == WHITE)
		{
			opp.count();
			DFSVisit2(v, time, S, n);
			opp.count();
			u->lowIndex = min(u->lowIndex, v->lowIndex);
		}
		else if (v->presentOnStack)
		{
			opp.count();
			u->lowIndex = min(u->lowIndex, v->index);
		}
	}

	opp.count();
	if (u->lowIndex == u->index)
	{
		opp.count();
		Node* w = NULL;
		do
		{
			opp.count();
			w = S.top();
			S.pop();
			w->presentOnStack = 0;

			opp.count();
		} while (w != u);
	}
	opp.count();
	u->color = BLACK;
	opp.count();
	u->timeToFinalize = ++(*time);
}
void DFS2(Graph* G, int n)
{
	Operation opp = HW11.createOperation("DFS", n);
	initGraph(G);
	int time = 0;
	opp.count();
	stack<Node*> S;
	for (int i = 0; i < G->noNodes; i++)
	{

		if (G->v[i]->color == WHITE)
		{
			opp.count();
			DFSVisit2(G->v[i], &time, S,n);
		}
	}
}

bool compare( Node* a,  Node* b)
{
	return a->timeToFinalize < b->timeToFinalize;
}

void TS(Graph* graph)
{
	cout << "DFS :" << endl;
	DFS(graph);
	cout << "Topological Sort" << endl;
	list<Node*> list1;
	Node* newNode;
	int i;
	for (i = 0; i < graph->noNodes; i++)
	{
		newNode = graph->v[i];
		list1.push_back(newNode);
	}
	stable_sort(list1.begin(), list1.end(), compare);

	for (Node* element : list1)
	{
		cout << element->key << endl;
	}
}

void TarjanVisit(Node* u, int* time, stack<Node*>& S)
{
	
	u->color = GRAY;
	u->timeToFind = ++(*time);
	S.push(u);
	u->presentOnStack = 1;
	u->lowIndex = u->index = S.size() - 1;
	for (int i = 0; i < u->no_neighb; i++)
	{
		Node* v = u->adjNodes[i];
		if (v->color == WHITE)//or lowIndex=-1
		{
			TarjanVisit(v, time, S);
			u->lowIndex = min(u->lowIndex, v->lowIndex);
		}
		else if (v->presentOnStack)
		{
			u->lowIndex = min(u->lowIndex, v->index);
		}
	}
	if (u->lowIndex == u->index)
	{
		Node* w = NULL;
		do
		{
			w = S.top();
			S.pop();
			w->presentOnStack = 0;
			cout << w->key << " ";
		} while (w != u);
		cout << endl;
	}
	u->color = BLACK;
	u->timeToFinalize = ++(*time);
}

void Tarjan(Graph* G)
{
	initGraph(G);
	int time = 0;
	stack<Node*> S;
	for (int i = 0; i < G->noNodes; i++)
	{
		if (G->v[i]->color == WHITE)
		{
			TarjanVisit(G->v[i], &time, S);
		}
	}
}

void DEMO()
{
	Graph* newGraphDFS = createGraph(6);
	dfsGraph = createGraph(6);
	getDFSgraph(dfsGraph);
	addEdge(newGraphDFS, 0, 1);
	addEdge(newGraphDFS, 0, 3);
	addEdge(newGraphDFS, 1, 2);
	addEdge(newGraphDFS, 2, 3);
	addEdge(newGraphDFS, 3, 1);
	addEdge(newGraphDFS, 4, 3);
	addEdge(newGraphDFS, 4, 5);
	addEdge(newGraphDFS, 5, 5);


	cout << " ---  " << "   ---   " << "  --- " << endl
		<< "| 0 |-" << "->| 1 |-" << "->| 2 |" << endl
		<< " ---  " << "   ---   " << "  --- " << endl << " |      o       /" << endl
		<< " |" << "     /     /" << endl << " \\/  <]-" << "  -  " << endl
		<< " ---  " << "   ---   " << "  --- " << endl
		<< "| 3 |" << "<--| 4 |" << "-->| 5 |" << endl
		<< " ---  " << "   ---   " << "  --- " << endl;;

	printGraph(newGraphDFS);
	cout << endl;

	//DFS(newGraphDFS);
	cout << endl;
	TS(newGraphDFS);
	cout << endl << "Tarjan :" << endl;
	Tarjan(newGraphDFS);
}

void initMatrix(int a[][4501])
{
	int i, j;
	for (i = 0; i < 4500; i++);
	{
		for (j = 0; j < 4500; j++);
		{
			a[i][j] = 1;
		}
	}
}

void addrandomEdges(Graph* G, int size)
{
	//int validity[4501][4501] = { 1 };
	//int i,a,b;
	//srand(time(0));
//	for (i = 0; i < size; i++);
	//{
	//	a = rand() % size;
	//	b = rand() % size;
		//if (validity[a][b] == 1)
		//{
			//addEdge(G, a, b);
		//	validity[a][b] = 0;
	//	}
		//else {
		//	while (validity[a][b] != 1)
	//		{
	//			a = rand() % size;
	//			b = rand() % size;
	//		}
	//		addEdge(G, a, b);
	//		validity[a][b] = 0;
	//	}
	//}
	//initMatrix(validity);


			Node* node = G->v[0];
			node->no_neighb = size;
			node->adjNodes = (Node**)malloc(sizeof(Node*) * size);
			for (int j = 0; j < size; j++)
			{
				int idx = rand() % G->noNodes;
				node->adjNodes[j] = G->v[idx];
			}
}

void PROFILER()
{
	int j, s, g;
	for (j = 0; j < NO_TESTS; j++)
	{
		Graph* graph = createGraph(100);
		for (s = 1000; s < 4501; s += 100)
		{ 
			addrandomEdges(graph,s);
			DFS2(graph,s);
		}
		//delete(graph);
	}

	HW11.divideValues("DFS_VISIT", NO_TESTS);
	HW11.divideValues("DFS", NO_TESTS);

	HW11.addSeries("DFS-TOTAL1", "DFS", "DFS-VISIT");

	HW11.createGroup("DFS-varuableEdges", "DFS-TOTAL1");
   HW11.reset();



	for (j = 0; j < NO_TESTS; j++)
	{
		for (s = 100; s < 201; s += 10)
		{
			Graph* graph = createGraph(s);
			addrandomEdges(graph, 4500);
			DFS2(graph,s);
			//delete(graph);
		}

	}
	HW11.divideValues("DFS_VISIT", NO_TESTS);
	HW11.divideValues("DFS", NO_TESTS);

	HW11.addSeries("DFS-TOTAL2", "DFS", "DFS-VISIT");

	HW11.createGroup("DFS-varuableVertices", "DFS-TOTAL2");

    HW11.reset();
	//HW11.showReport();

}

int main()
{
	DEMO();
	//PROFILER();

}