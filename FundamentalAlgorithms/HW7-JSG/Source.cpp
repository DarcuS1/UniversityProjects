/**
*
*@ Gelu-Samuel Josan
* @ group 30421
* 
You are required to implement correctly and efficiently the management operations of an order
statistics tree (chapter 14.1 from the book1).
You have to use a balanced, augmented Binary Search Tree. Each node in the tree holds, besides
the necessary information, also the size field (i.e. the size of the sub-tree rooted at the node).

*   Personal Interpretation:
* 
* 
*    For building the tree we use a divide et impera strategy, and get the mid element, then iterate trough all subsets, insertaing mids, 
     so we get a balanced bst, I also compiute the size there, with seeing is we have either left or right or both and add the size after the formula
	  size= size.left+size.right+1;
* 
*    For delete I first select the element to be found, then go trough with the normal delete of the key
* 
*    Build Tree  is for both :O(n)
*    Select relative to the tree, in my case it is O(logn), because we have a balanced bst, and an avl
*    in which the maximum height is log(n), so select goes trough max log(n)
*    Delete is O(logn) still, it represents select + delete
* 
*    If we try from(1 to n) random selects and deletes we get  O(n)
* 
*/

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include"Profiler.h"
#include<time.h>

#define MAX_SIZE 10000
#define NO_TESTS 5
#define STEP_SIZE 100

Profiler HW7("Order-Statistic");

typedef struct BST
{
	int key;
	int size;
	BST* p; 
	BST* left;
	BST* right;
}BST;

BST* nil= new BST{-99,-99,NULL,NULL,NULL};

BST* osSelect(BST* root, int i, int n)
{
	Operation opp = HW7.createOperation("SelectOpps", n);
	if (root != NULL)
	{
		int r;
		if (root->left != NULL)
		{
			r = root->left->size + 1;
		}
		else
		{
			r = 1;
		}
		opp.count();
		if (i == r)
		{
			return root;
		}
		else {
			opp.count();
			if (i < r)
			{
				return osSelect(root->left, i,n);
			}
			else {
				
				return osSelect(root->right, i - r,n);
			}
		}
	}
	else return NULL;
}

BST* getGoodNode(BST* currNode)
{
	BST* dummyCurr = currNode;
	while (dummyCurr->left != NULL)
	{
		dummyCurr = dummyCurr->left;
	}
	return dummyCurr;
}

BST* osDelete(BST* root, int key, int n)
{
	Operation opp = HW7.createOperation("DeleteOpps", n);

	if (root != NULL)
	{

		opp.count();
		if (root->key > key)
		{

			root->left = osDelete(root->left, key, n);
			opp.count();
		}
		else
		{
			opp.count();
			if (root->key < key)
			{
				root->right = osDelete(root->right, key, n);
				opp.count();
			}
			else
			{
				if (root->right == NULL)
				{
					BST* temp = root->left;
					if (root->left != NULL && root->right != NULL) {
						root->size = root->left->size + root->right->size + 1;
					}
					else {
						if (root->left != NULL) {
							root->size = root->left->size + 1;
						}

						if (root->right != NULL) {
							root->size = root->right->size + 1;
						}
					}
					opp.count();
					free(root);
					return temp;
				}
				else
				{
					if (root->left == NULL) {

						BST* temp = root->right;
						if (root->left != NULL && root->right != NULL) {
							root->size = root->left->size + root->right->size + 1;
						}
						else {
							if (root->left != NULL) {
								root->size = root->left->size + 1;
							}

							if (root->right != NULL) {
								root->size = root->right->size + 1;
							}
						}
						opp.count();
						free(root);
						return temp;
					}
				}
				BST* temp = getGoodNode(root->right);
				opp.count();
				root->key = temp->key;
				root->right = osDelete(root->right, temp->key, n);
			}
		}
		root->size--;
		return root;
	}
	else
	{
		return root;
	}
	
}

BST* osDeleteDirect(BST* root, int key, int n)
{
	BST* aux = root;
	aux = osSelect(root, key, n);
	osDelete(root, aux->key, n);
	return NULL;
}

void printRank(BST* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->left != NULL) {
		printRank(root->left);
	}
	std::cout << root->size << " ";
	if (root->right != NULL) {
		printRank(root->right);
	}
}

void inorder(BST* root) 
{
	if (root == NULL)
	{
		
		return;
	}
	inorder(root->left);
	std::cout << root->key << " ";
	inorder(root->right);
}

BST* buildTreefromArray(int array[], int left, int right)
{
	int mij;
	if (left > right)
	{
		return NULL;
	}
	mij = (left + right) / 2;
	BST* root = new BST{ mij,1,NULL,NULL,NULL };

	root->left = buildTreefromArray(array, left, mij - 1);
	root->right = buildTreefromArray(array, mij + 1, right);

	if (root->left != NULL && root->right != NULL) {
		root->size = root->left->size + root->right->size + 1;
	}
	else {
		if (root->left != NULL) {
			root->size = root->left->size + 1;
		}

		if (root->right != NULL) {
			root->size = root->right->size + 1;
		}
	}
	return root;
}

void print2WAY(BST* root1, int* level)
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

void demo()
{
	int arrayDummy[100];
	int end = 0;
	int start = 10;
	FillRandomArray(arrayDummy, start, 0, 30, true, 1);
	BST* root = NULL;
	int level = 0;
	int n = 11;
	int ith = 6;

	root = buildTreefromArray(arrayDummy, 1, start);
	std::cout << root->key << std::endl;
	BST* test = new BST;
	test = osSelect(root, ith,n);
	if (test != NULL)
	{
		printf("The %d'th key is %d \n", ith, test->key);
	}
	else printf("nu merge \n");

	int kk = 1;;
	inorder(root);
	std::cout << std::endl;
	printRank(root);
	std::cout << std::endl;
	print2WAY(root, &level);

	std::cout << std::endl;
	inorder(root);
	kk = 1;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	osDeleteDirect(root, kk,n);
	std::cout << std::endl;
	print2WAY(root, &level);

	std::cout << std::endl;
	inorder(root);
	kk = 8;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	
	osDeleteDirect(root, kk,n);
	std::cout << std::endl;
	print2WAY(root, &level);

	
	std::cout << std::endl;
	inorder(root);
	kk = 2;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	osDeleteDirect(root, kk,n);
	std::cout << std::endl;
	print2WAY(root, &level);


	std::cout << std::endl;
	inorder(root);
	kk = 3;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	osDeleteDirect(root, kk, n);
	std::cout << std::endl;
	print2WAY(root, &level);

	inorder(root);
	std::cout << std::endl;
	printRank(root);
	std::cout << std::endl;
	ith = 3;
	test = osSelect(root, ith,n);
	if (test != NULL)
	{
		printf("The %d'th key is %d \n", ith, test->key);
	}
	else printf("nu mergen \n");

}

/// <summary>
/// AVL starts here
/// </summary>

typedef struct AVL
{
	int key;
	int size;
	int height;
	struct AVL* left;
	struct AVL* right;
	struct AVL* p;
}AVL;

AVL* nilAVL = new AVL{ -99,-99,0,NULL,NULL,NULL };

int calcRank(AVL* root)
{
	if (root == NULL)
	{
		return 0;
	}
	calcRank(root->left);
	calcRank(root->right);
	if (root->left != NULL && root->right != NULL) {
		root->size = root->left->size + root->right->size + 1;
	}
	else {
		if (root->left != NULL) {
			root->size = root->left->size + 1;
		}

		if (root->right != NULL) {
			root->size = root->right->size + 1;
		}
	}
}

int heightAVL(AVL* currNode)
{
	if (currNode == NULL)
	{
		return 0;
	}
	return currNode->height;
}

int maxAVL(int aValue, int bValue)
{
	return (aValue > bValue) ? aValue : bValue;
}

void inorderAVL(AVL* root)
{
	if (root == NULL)
	{

		return;
	}
	inorderAVL(root->left);
	std::cout << root->key << "  ";
	inorderAVL(root->right);
}

AVL* rightRotate(AVL* currNode)
{
	AVL* dummyNode = currNode->left;
	AVL* rotaNode = dummyNode->right;

	dummyNode->right = currNode;
	currNode->left = rotaNode;

	currNode->height =  maxAVL(heightAVL(currNode->left), heightAVL(currNode->right)) + 1;
	dummyNode->height = maxAVL(heightAVL(dummyNode->left), heightAVL(dummyNode->right)) + 1;

	return dummyNode;
}

AVL* leftRotate(AVL* currNode)
{
	AVL* dummyNode = currNode->right;
	AVL* rotaNode = dummyNode->left;

	dummyNode->left = currNode;
	currNode->right = rotaNode;

	currNode->height = maxAVL(heightAVL(currNode->left), heightAVL(currNode->right)) + 1;
	dummyNode->height = maxAVL(heightAVL(dummyNode->left), heightAVL(dummyNode->right)) + 1;

	return dummyNode;
}

int computeIfBalanced(AVL* currNode)
{
	if (currNode == NULL)
	{
		return 0;
	}
	return heightAVL(currNode->left) - heightAVL(currNode->right);
}

AVL* insertAVL(AVL* currNode, int key)
{

	if (currNode == NULL)
	{
		return new AVL{ key, 1, 1, NULL, NULL ,NULL };
	}
	if (key < currNode->key)
	{
		currNode->left = insertAVL(currNode->left, key);
	}
	else {
		if (key > currNode->key)
		{
			currNode->right = insertAVL(currNode->right, key);
			
		}
		else
		{
			return currNode;
		}
	}
	
	currNode->height = 1 + maxAVL(heightAVL(currNode->left), heightAVL(currNode->right));
	int balVal = computeIfBalanced(currNode);

	if (balVal < -1 && key < currNode->right->key)
	{
		currNode->right = rightRotate(currNode->right);
		return leftRotate(currNode);
	}

	if (balVal < -1 && key > currNode->right->key)
	{
		return leftRotate(currNode);
	}

	if (balVal > 1 && key < currNode->left->key  )
	{
		return rightRotate(currNode);
	}

	if (balVal > 1 && key > currNode->left->key)
	{
		currNode->left = leftRotate(currNode->left);
		return rightRotate(currNode);
	}

	
	
	return currNode;
}

void printRankAVL(AVL* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->left != NULL) {
		printRankAVL(root->left);
	}
	std::cout << root->size << "  ";
	if (root->right != NULL) {
		printRankAVL(root->right);
	}
}

AVL* buildTreeAVL(AVL* root1, int n)
{
	int i;
	root1 = insertAVL(root1, n / 2 + 1);

	for (i = 1; i <= n; i++)
	{
		if (i != n / 2 + 1)
		{
			root1 = insertAVL(root1, i);

		}
	}
	return root1;
}

void print2WAYAVL(AVL* root1, int* level)
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
		(*level) += 3;
		print2WAYAVL(root1->left, level);
		(*level) -= 3;
	}

	if (root1->right != NULL)
	{
		(*level) += 3;
		print2WAYAVL(root1->right, level);
		(*level) -= 3;
	}

}

AVL* osSelectAVL(AVL* root, int i, int n)
{
	Operation opp = HW7.createOperation("AVL_SELECT", n);
	if (root != NULL)
	{
		int r;
		if (root->left != NULL)
		{
			r = root->left->size + 1;
		}
		else
		{
			r = 1;
		}
		opp.count();
		if (i == r)
		{
			return root;
		}
		else {
			opp.count();
			if (i < r)
			{
			
				return osSelectAVL(root->left, i, n);
			}
			else 
			{
			
				return osSelectAVL(root->right, i - r, n);
			}
		}
	}
	else return NULL;
}

AVL* getGoodNodeAVL(AVL* currNode)
{
	AVL* dummyCurr = currNode;
	while (dummyCurr->left != NULL)
	{
		dummyCurr = dummyCurr->left;
	}
	return dummyCurr;
}

AVL* osDeleteAVL(AVL* root, int key, int n)
{
	Operation opp = HW7.createOperation("AVL_DELETE", n);
	if (root == NULL)
	{
		return root;
	}
	opp.count();
	if (key< root->key)
	{
		opp.count();
		root->left = osDeleteAVL(root->left, key,n);
	}
	else {
		opp.count();
		if (key > root->key)
		{
			opp.count();
			root->right = osDeleteAVL(root->right, key,n);
		}
		else
		{
			if ((root->left == NULL) || (root->right == NULL))
			{ 
				AVL* dummyTemp = root->left ? root->left : root->right;
				if (dummyTemp == NULL)
				{
					dummyTemp = root;
					root = NULL;
				}
				else
				{
					root = dummyTemp;
					free(dummyTemp);
				}
			}
			else
			{
			AVL* dummyTemp = getGoodNodeAVL(root->right);
			root->key = dummyTemp->key;
			opp.count();
			root->right = osDeleteAVL(root->right, dummyTemp->key,n);
			}
		}
	}

	if (root == NULL)
	{
		return root;
	}

	
	root->height = 1 + maxAVL(heightAVL(root->left),heightAVL(root->right));

	
	int balVal = computeIfBalanced(root);

	

	if (balVal < -1 && computeIfBalanced(root->right) <= 0)
	{
		return leftRotate(root);
	}


	if (balVal > 1 && computeIfBalanced(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}


	if (balVal < -1 && computeIfBalanced(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	if (balVal > 1 && computeIfBalanced(root->left) >= 0)
	{
		return rightRotate(root);
	}

	return root;
}

AVL* osDeleteDirectAVL(AVL* root, int key, int n)
{
	AVL* aux = root;
	aux = osSelectAVL(root, key, n);
	osDeleteAVL(root, aux->key, n);
	calcRank(root);
	return NULL;
}

void demo2()
{
	AVL* root = NULL;

	int n = 11;
	int level = 0;
	int ith = 5;
	root = buildTreeAVL(root, n);
	calcRank(root);
	inorderAVL(root);
	printf("\n");
	printf("\n");
	printRankAVL(root);
	printf("\n");

	AVL* test = NULL;
	test = osSelectAVL(root, ith,n);
	if (test != NULL)
	{
		printf("The %d'th key is %d \n", ith, test->key);
	}
	else printf("nu mergen \n");

	print2WAYAVL(root, &level);
	printf("\n");
	int kk;
	std::cout << std::endl;
	inorderAVL(root);
	kk = 1;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	osDeleteDirectAVL(root, kk, n);
	std::cout << std::endl;
	print2WAYAVL(root, &level);

	std::cout << std::endl;
	inorderAVL(root);
	kk = 8;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	osDeleteDirectAVL(root, kk, n);
	std::cout << std::endl;
	print2WAYAVL(root, &level);

	std::cout << std::endl;
	inorderAVL(root);
	kk = 5;
	std::cout << std::endl;
	printf("Deleting the %d'th node :", kk);
	osDeleteDirectAVL(root, kk, n);
	std::cout << std::endl;
	print2WAYAVL(root, &level);
	printf("\n");

	ith = 3;
	test = osSelectAVL(root, ith, n);
	if (test != NULL)
	{
		printf("The %d'th key is %d \n", ith, test->key);
	}
	else printf("nu mergen \n");
}

void profilerTasks()
{
	int nValue = MAX_SIZE;
	int g;
	int s;
	int j;
	int random;
	int array[MAX_SIZE];

	for (g = 0; g < NO_TESTS; g++)
	{
		for (s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
		{
			FillRandomArray(array, s, 0, 50000, true, 1);
			BST* newRoot = NULL;
			newRoot = buildTreefromArray(array, 0, s);
			for (j = s ; j >= 1; j --)
			{
				srand(time(0));
				random = rand();
				osSelect(newRoot, random, s);
				osDelete(newRoot, random, s);
			}
			delete newRoot;
		}
	}
	HW7.divideValues("SelectOpps", NO_TESTS);
	HW7.divideValues("DeleteOpps", NO_TESTS);

	HW7.createGroup("SelectOpp", "SelectOpps");
	HW7.createGroup("DeleteOpp", "DeleteOpps");
	HW7.reset();
}

void profilerTasksAVL()
{
	int nValue = MAX_SIZE;
	int g;
	int s;
	int j;
	int random;

	for (g = 0; g < NO_TESTS; g++)
	{
		for (s = STEP_SIZE; s <= MAX_SIZE; s += STEP_SIZE)
		{
			AVL* newRoot = NULL;
			newRoot = buildTreeAVL(newRoot, s);
			for (j = s; j >= 1; j--)
			{
			srand(time(0));
			random = rand();
			osSelectAVL(newRoot, random, s);
			osDeleteAVL(newRoot, random, s);
			}
			delete newRoot;
			
		}
	}
		HW7.divideValues("AVL_SELECT", NO_TESTS);
		HW7.divideValues("AVL_DELETE", NO_TESTS);

		HW7.createGroup("SelectOppAVL", "AVL_SELECT");
		HW7.createGroup("DeleteOppAVL", "AVL_DELETE");
		HW7.reset();
	
}

int main()
{
	//demo();
	//demo2();
	//profilerTasksAVL();
	//profilerTasks();
	return 0;
}
	