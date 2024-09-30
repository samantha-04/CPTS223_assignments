#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;


/* ----------------------------------------------------------------------------
---- Below is declaration of BST class, referring to textbook, Figure 4.16 ----
---------------------------------------------------------------------------- */

template <typename Comparable>
class BST
{
public:
	BST();
	~BST();
	void makeEmpty();

	const Comparable & findMin() const;
	const Comparable & findMax() const;

	bool contains(const Comparable & x) const;
	void insert(const Comparable & x);
	void remove(const Comparable & x);
	int treeSize() const;
	int treeHeight() const;
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element(theElement), left(lt), right(rt) {}
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt): element(move(theElement)), left(lt), right(rt) {}
	};

	BinaryNode *root;

	BinaryNode * findMin( BinaryNode * t ) const;
	BinaryNode * findMax( BinaryNode * t ) const;
	bool contains(const Comparable & x, BinaryNode* t) const;//helper
	void insert(const Comparable & x, BinaryNode* &t); //helper
    void remove(const Comparable & x, BinaryNode* &t);//helper 
	void makeEmpty( BinaryNode * & t );
	int treeSize(BinaryNode* t) const; //added for recursive call 
	int treeHeight(BinaryNode* t) const; //added for recursive call
	void printInOrder(BinaryNode* t) const; //added for recursive call
	void printMaxPath(BinaryNode* t) const; //added for recursive call
};


/* --------------------------------------------------------------
---- Below is implementation of public and private functions ----
-------------------------------------------------------------- */

// constructor
template<typename Comparable>
BST<Comparable>::BST() : root(NULL) {}

// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
	makeEmpty();
}

// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode *& t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// // public findMin
template <typename Comparable>
const Comparable & BST<Comparable>::findMin() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax
template <typename Comparable>
const Comparable & BST<Comparable>::findMax() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMin(t->right);
    }
}

//public contains
template<typename Comparable>
bool BST<Comparable>::contains(const Comparable & x) const 
{
    return contains(x, root); //calls the helper function
}

//private helper function 
template<typename Comparable>
bool BST<Comparable>::contains(const Comparable & x, BinaryNode* t) const
{
    if (t == nullptr)
	{ //base case: not found
        return false;
	}
    else if (x < t->element) //search left subtree
	{
        return contains(x, t->left);
	}
    else if (t->element < x) //search right subtree
	{
        return contains(x, t->right);
	}
    else //match!
	{
        return true;
	}
}


// public insert
template<typename Comparable>
void BST<Comparable>::insert(const Comparable & x) 
{
    insert(x, root); //calls helper
}

//private insert
template<typename Comparable>
void BST<Comparable>::insert(const Comparable & x, BinaryNode* &t)
{
    if (t == nullptr) //empty tree
	{
        t = new BinaryNode(x, nullptr, nullptr);
	}
    else if (x < t->element) //insert in left subtree
	{
        insert(x, t->left);
	}
    else if (t->element < x) //insert in right subtree
	{
        insert(x, t->right);
	}
}

// public remove
template<typename Comparable>
void BST<Comparable>::remove(const Comparable & x) 
{
	remove(x, root);
}

//private remove
template<typename Comparable>
void BST<Comparable>::remove(const Comparable & x, BinaryNode* &t)
{
	if (t == nullptr)
	{
		return; //item not found, do nothing
	}
	if (x < t->element) //search left subtree
	{
		remove(x, t->left);
	}
	else if (t->element < x) //search right subtree
	{
		remove(x, t->right);
	}
	else if (t->left != nullptr && t->right != nullptr) //two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		BinaryNode *oldNode = t; //node to be deleted
		t = (t->left != nullptr) ? t->left : t->right; //bypass the node
		delete oldNode; //delete the node
	}
}

// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const 
{
    return treeSize(root);
}

//private treeSize
template <typename Comparable>
int BST<Comparable>::treeSize(BinaryNode* t) const 
{
    if (t == nullptr) //empty tree
    {
        return 0;
    }

    //recursively count the size of the left and right subtrees
    return 1 + treeSize(t->left) + treeSize(t->right);
}


// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const
{
    return treeHeight(root);
}

//private treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight(BinaryNode* t) const
{
    if (t == nullptr)
    {
        return -1; //one node is height of zero, so no tree is height of -1
    }
    
    //calculate the height of the left and right subtrees (recursive)
    int leftHeight = treeHeight(t->left);
    int rightHeight = treeHeight(t->right);
    
    // the height is the larger of the two, plus 1 for the current node
	if (rightHeight > leftHeight)
	{
		return 1 + rightHeight;
	}
    
	if (leftHeight >= rightHeight)
	{
		return 1 + leftHeight;
	}


}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const 
{
	printInOrder(root);
}

//private printInOrder
template <typename Comparable>
void BST<Comparable>::printInOrder(BinaryNode *t) const
{
	if (t == nullptr) 
	{
        return;  //if the node is null, return
    }

    //recursively go to left subtree
    printInOrder(t->left);

    //print the current node's element
    cout << t->element << " ";

    //recursively go to right subtree
    printInOrder(t->right);
}


// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const 
{
	if (root == nullptr) 
	{
        return; //empty, nothing to print
    }

    queue<BinaryNode*> nodeQueue;
    nodeQueue.push(root); //start with the root node

    while (!nodeQueue.empty()) 
	{
        BinaryNode* current = nodeQueue.front();
        nodeQueue.pop();

        //print the current node's element
        cout << current->element << " ";

        //enqueue the left and right children if they exist
        if (current->left != nullptr)
		{
            nodeQueue.push(current->left);
        }
        if (current->right != nullptr) 
		{
            nodeQueue.push(current->right);
        }
    }

    cout << endl; //space
}

// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const 
{
    printMaxPath(root);
    cout << endl; 
}

//private printMaxPath 
template <typename Comparable>
void BST<Comparable>::printMaxPath(BinaryNode* t) const 
{
    if (t == nullptr) 
	{
        return;
    }

    //print the current node
    cout << t->element << " ";

    //recursively move down 
    if (treeHeight(t->left) > treeHeight(t->right))
	{
        printMaxPath(t->left);
    } 
	else 
	{
        printMaxPath(t->right);
    }
}
 #endif
