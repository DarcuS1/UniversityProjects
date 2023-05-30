#include<iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include "bfs.h"
#include<queue>

#define MAX_SIZE 500
typedef struct MWay
{
    int key;
    std::vector<MWay*> children;
}MWay;

int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4

    int rowVal = p.row, colVal = p.col;
    int neighbNo = 0, i = 0;
    if (rowVal <= grid->rows && rowVal >= 0 && colVal <= grid->cols && colVal >= 0) {
        if (grid->mat[rowVal][colVal] != 1)
        {
            Point dummyPoint;
            dummyPoint.row = rowVal - 1;
            dummyPoint.col = colVal;
            if (grid->mat[rowVal - 1][colVal] != 1)
            { // down
                neighb[i] = dummyPoint;
                neighbNo++; i++;
            }

            dummyPoint.row = rowVal + 1;
            dummyPoint.col = colVal;
            if (grid->mat[rowVal + 1][colVal] != 1)
            { // up 
                neighb[i] = dummyPoint;
                neighbNo++; i++;
            }

            dummyPoint.row = rowVal;
            dummyPoint.col = colVal - 1;
            if (grid->mat[rowVal][colVal - 1] != 1)
            { // l 
                neighb[i] = dummyPoint;
                neighbNo++; i++;
            }
           
            dummyPoint.row = rowVal;
            dummyPoint.col = colVal + 1;
            if (grid->mat[rowVal][colVal + 1] != 1)
            { // r 
                neighb[i] = dummyPoint;
                neighbNo++; i++;
            }
            
        }
    }

    return neighbNo;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[4];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}

void free_edges(Graph* graph)
{
    if (graph->v != NULL) {
        for (int i = 0; i < graph->nrNodes; ++i) {
            if (graph->v[i] != NULL) {
                if (graph->v[i]->adj != NULL) {
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
            }
        }
    }
}

void bfs(Graph *graph, Node *s, Operation *op)
{
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();

    Node* dummyNodez;
    std::queue<Node*> Que;
    int i;

    s->dist = 0;
    s->parent = NULL;
    s->color = COLOR_GRAY;
   

    if (op != NULL) op->count();
    Que.push(s);

    if (op != NULL) op->count();
    while (!Que.empty())
    {
        if (op != NULL) op->count();
        dummyNodez = Que.front();
        Que.pop();

        for (i = 0; i < dummyNodez->adjSize; i++) 
        {
            if (op != NULL) op->count();
            if (dummyNodez->adj[i]->color == COLOR_WHITE) 
            {
                if (op != NULL) op->count(4);
                dummyNodez->adj[i]->color = COLOR_GRAY;
                dummyNodez->adj[i]->dist = dummyNodez->dist + 1;
                dummyNodez->adj[i]->parent = dummyNodez;
                Que.push(dummyNodez->adj[i]);
            }
        }
        if (op != NULL) op->count();
        dummyNodez->color = COLOR_BLACK;
    }
}

void printfromVector(int parents[], int nrNodes, Point rearGuard[])
{
    int z;
    std::cout << "COORD :";
    for (z = 0; z < nrNodes; z++)
    {
        std::cout << "(" << rearGuard[z].row << ")"<< "(" << rearGuard[z].col << ")"<<" ";
    }
    std::cout << std::endl;
    std::cout << "PRENT :";
    for (z = 0; z < nrNodes; z++)
    {
        std::cout << "    " << parents[z] << "  ";
    }
    std::cout << std::endl;
    std::cout << "NODES :";
    for (z = 0; z < nrNodes; z++)
    {
        std::cout << "    " << z << "  ";
    }
}

MWay* build2(int mTree1[], int noNodes)
{
    MWay* root = nullptr;
    MWay* item[MAX_SIZE];
    int mTreeAux[MAX_SIZE] = { 0 };
    int i;
    for (i = 1; i < noNodes; i++)
    {
        mTreeAux[mTree1[i]]++;
        MWay* temp = new MWay;
        temp->key = i;
        item[i] = temp;
    }
    for (i = 1; i < noNodes; i++)
    {

        if (mTree1[i] == -1)
        {
            root = item[i];
        }
        else
        {
            if (mTreeAux[mTree1[i]] > 0)
            {
                item[mTree1[i]]->children.push_back(item[i]);
            }
        }
    }
    return root;
}

void printMWAY(MWay* root, int* level)
{
    int i;
    for (int k = 0; k < *level; k++)
    {
        printf(" ");
    }
    printf("%d ", root->key);
    printf("\n");
    if (!root->children.empty())
    {
        (*level) += 3;
        for (int j = 0; j < root->children.size(); j++)
        {
            printMWAY(root->children[j], level);
        }
        (*level) -= 3;
    }
}

void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs
        int level = 0;
       
        printfromVector(p, n, repr);
        std::cout << std::endl;
         MWay* newRoot = build2(p, n);
         printMWAY(newRoot, &level);
    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000
   //return -1;

    Node** queue = (Node**)malloc(sizeof(Node*) * graph->nrNodes);
    int headNode = 0;
    int tailNode = 0;
 
    for (int i = 0; i < graph->nrNodes; i++) 
    {
        Node* node = graph->v[i];
        node->dist = -1;
        node->parent = NULL;
    }

    start->dist = 0;
    queue[tailNode++] = start;

    while (headNode != tailNode)
    {
        Node* node = queue[headNode++];
        for (int i = 0; i < node->adjSize; i++) 
        {
            Node* neighbor = node->adj[i];
            if (neighbor->dist == -1)
            {
                neighbor->dist = node->dist + 1;
                neighbor->parent = node;
                queue[tailNode++] = neighbor;
            }
        }
    }
 
    if (end->dist == -1) 
    {
        free(queue);
        return -1;
    }

    int idx = 0;
    Node* curr = end;
    while (curr != start) 
    {
        path[idx++] = curr;
        curr = curr->parent;
    }
    path[idx++] = start;

    for (int i = 0; i < idx / 2; i++)
    {
        Node* temp = path[i];
        path[i] = path[idx - i - 1];
        path[idx - i - 1] = temp;
    }

    free(queue);
    return idx;
}

bool isConnected(Graph graphCON, Node* start)
{
    std::queue<Node*> Quw;
    int i;
    for (i = 0; i < graphCON.nrNodes; i++)
    {
        graphCON.v[i]->color = COLOR_WHITE;
        graphCON.v[i]->dist = INFINITY;
        graphCON.v[i]->parent = NULL;
    }
    start->color = COLOR_GRAY;
    start->dist = 0;
   
    Quw.push(start);
    while (!Quw.empty())
    {
        Node* u = Quw.front();
        Quw.pop();
        for (i = 0; i < u->adjSize; i++) 
        {
            Node* v = u->adj[i];
            if (v->color == COLOR_WHITE)
            {
                v->color = COLOR_GRAY;
                v->dist = u->dist + 1;
                v->parent = u;
                Quw.push(v);
            }
        }
        u->color == COLOR_BLACK;
    }
    for (i = 0; i < graphCON.nrNodes; i++)
    {
        if (graphCON.v[i]->color == COLOR_WHITE)
        {
            return false;
        }
    }
    return true;
}

void generateRandomAdjacentNodes(Graph* graph, int n) {
    for (int i = 0; i < graph->nrNodes; i++) 
    {
        Node* node = graph->v[i];
        node->adjSize = n;
        node->adj = (Node**)malloc(sizeof(Node*) * n);
        for (int j = 0; j < n; j++) 
        {
            int idx = rand() % graph->nrNodes;
            node->adj[j] = graph->v[idx];
        }
    }
}

void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for(n=1000; n<=4500; n+=100)
    {
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i)
        {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected
        generateRandomAdjacentNodes(&graph, n);
        if (isConnected(graph, graph.v[0]))
        {
            bfs(&graph, graph.v[0], &op);
            free_graph(&graph);
        }
        else
        {
            while (!isConnected(graph, graph.v[0]))
            {
                free_graph(&graph);
                generateRandomAdjacentNodes(&graph, n);

            }
            bfs(&graph, graph.v[0], &op);
            free_graph(&graph);
        }
        
    }

    // vary the number of vertices
    for(n=100; n<=200; n+=10)
    {
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i)
        {
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected
        generateRandomAdjacentNodes(&graph, 4500);

        //if (isConnected(graph, graph.v[0]))
        //{
        //    bfs(&graph, graph.v[0], &op);
        //    free_graph(&graph);
        //}
        //else
        //{
        //    while (!isConnected(graph, graph.v[0]))
        //    {
        //        free_graph(&graph);
        //        generateRandomAdjacentNodes(&graph, 4500);
        //    }
        //    bfs(&graph, graph.v[0], &op);
        //    free_graph(&graph);
        //}
        bfs(&graph, graph.v[0], &op);
            free_graph(&graph);
    }

    p.showReport();
}
