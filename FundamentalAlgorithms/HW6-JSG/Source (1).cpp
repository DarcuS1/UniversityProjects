/*
*@ Gelu-Samuel Josan
*@ group 30421
      You are required to implement correctly and efficiently linear time transformations between
      three different representations for a multi-way tree:
       R1: parent representation: for each key you are given the parent key, in a vector.
       R2: multi-way tree representation: for each node you have the key and a vector of
        children nodes
       R3: binary tree representation: for each node, you have the key, and two pointers: one to
        the first child node, and one to the brother on the right (i.e. the next brother node)

*  Personal Interpretation :
* 
*    We perform each transformation in O(n) complexity
*    For oarents to multiy way approach I used the following:
*      I initialized a list of items with each possible key node, then when we had a node that had children we would 
*         put them in the vector as they come, the root case was solved separately
* 
*    In the second case I used a method of traversal of the mway tree, fisrt go as left as possible starting with root, then add each 
*     node at right is they exist in children vector as right sibling, rest as left children.
*/
#include<iostream>
#include <vector>
#include"Profiler.h"
using namespace std;
#define MAX_SIZE 100
Profiler HW6("Mway Representations");

/////////////// 0 1 2 3 4 5 6 7  8 9  10
int mTree[] = { 0,2,7,5,2,7,7,-1,5,2, 5 ,6};
int n_mTree = sizeof(mTree) / sizeof(int);
int mTreeAux[11] = { 0 };

typedef struct MWay
{
    int key;
    vector<MWay*> children;
}MWay;

typedef struct MTreeB
{
    int key;
    MTreeB* left;
    MTreeB* right;
}MTreeB;


int findRoot(int parents[])
{
    for (int i = 1; i < n_mTree; i++)
    {
        if (parents[i] == -1)
        {
            return i;
        }
    }
}

void printfromVector(int parents[])
{
    /*int root = findRoot(parents);
    int aux[MAX_SIZE] = { 0 };
    for (int k = 0; k < *level; k++)
    {
        cout << " ";
    }
    cout << root <<endl;
    (*level)++;
    for (int i = 1; i < n_mTree; i++)
    {
        if (parents[i] == root)
        {
            cout << i << endl;
            for (int z = 1; z < n_mTree; z++)
            {
                aux[z] = parents[z];
            }
            parents[root] = -2;
            parents[i] = -1;
            printfromVector(aux, level);
        }

        int ok = 1;
        for (int i = 1; i < n_mTree; i++)
        {
            if (parents[i] != -2)
            {
                ok = 0;
            }
        }
        if (ok == 1)
        {
            break;
        }

    }*/
    cout << "NODES :";
    for (int z = 1; z < n_mTree; z++)
    {
        cout <<" "<< z << "  ";
    }
    cout << endl;
    cout << "PRENT :";
    for (int z = 1; z < n_mTree; z++)
    {
        cout << " " << parents[z] << "  ";
    }
}

MWay* build2(int mTree1[])
{
    MWay* root = nullptr;
    MWay* item[MAX_SIZE];
    int i;
    for (i = 1; i < n_mTree; i++)
    {
        mTreeAux[mTree1[i]]++;
        MWay* aux = new MWay;
        aux->key = i;
        item[i] = aux;
    }
    for (i = 1; i < n_mTree; i++)
    {

        if (mTree1[i] == -1)
        {
            root = item[i];
        }
        else
        {
            MWay* aux = new MWay;
            aux = item[mTree[i]];
            aux->children.push_back(item[i]);
        }
    }
    return root;
}


void printMWAY(MWay* root, int *level)
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

void print2WAY(MTreeB* root1, int* level)
{
    int i;
    for (int k = 0; k < *level; k++)
    {
        printf(" ");
    }
    printf("%d ", root1->key);
    printf("\n");
 
    if (root1->left != NULL)
    {
        (*level) += 2;
        print2WAY(root1->left, level);
        (*level) -= 2;
    }

    if (root1->right != NULL)
    {
        (*level) += 2;
        print2WAY(root1->right, level);
        (*level) -= 2;
    }
  
}

void print2WAYasM(MTreeB* root1, int* level)
{
    int i;
    for (int k = 0; k < *level; k++)
    {
        printf(" ");
    }
    printf("%d ", root1->key);
    printf("\n");
    if (root1->left != NULL)
    {
        (*level) += 2;
        print2WAYasM(root1->left, level);
        (*level) -= 2;
    }
    if (root1->right != NULL)
    {
        print2WAYasM(root1->right, level);
    }

}

MTreeB* build3(MWay* root)
 {
     if (root==NULL)
     {
         return NULL;
     }
     MTreeB* dummy = new MTreeB{ root->key };
     if (root->children.size()) {
         dummy->left = build3(root->children[0]);
     }
     MTreeB* bro = dummy->left;
     for (int i = 1; i < root->children.size(); ++i) {
         bro->right = build3(root->children[i]);
         bro = bro->right;
     }
     return dummy;
 }

int main()
{
    printfromVector(mTree);
    cout << endl;
    MWay* test;
    MTreeB* test2;
    int level = 0;

    test = build2(mTree);
    printMWAY(test,&level);
    cout << endl;

    test2 =build3(test);
    level = 0;
    print2WAY(test2, &level);
    cout << endl;

    level = 0;
    print2WAYasM(test2, &level);
}

