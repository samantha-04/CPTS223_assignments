
#include <iostream>
#include <limits>
#include <vector>
using namespace std;


template <typename Comparable>
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void makeEmpty();
    const Comparable & findMin() const;
    const Comparable & findMax() const;

    bool contains(const Comparable & x) const;
    void insert(const Comparable & x);
    void remove(const Comparable &x);
    int treeSize() const;
    int computeHeight() const;
    int readRootHeight() const;
    bool isBalanced() const;
    bool isBST() const;

    double averageDepth() const;
    void removeByRank(int rank);

   
    // the next line follows textbook Figure 4.42, Line 19
    static const int ALLOWED_IMBALANCE = 1;
private:
    struct AVLNode  // refer to textbook, Figure 4.40
    {
        Comparable element;
        AVLNode *left;
        AVLNode *right;
        int height;

        AVLNode( const Comparable & theElement, AVLNode *lt, AVLNode *rt ): element(theElement), left(lt), right(rt) {}
        AVLNode( Comparable && theElement, AVLNode *lt, AVLNode *rt ): element(move(theElement)), left(lt), right(rt) {}
    };

    AVLNode *root;

    AVLNode * findMin( AVLNode * t ) const;
    AVLNode * findMax( AVLNode * t ) const;
    void makeEmpty( AVLNode * & t );

    void balance(AVLNode * & t);
    void rotateWithLeftChild( AVLNode * & t );
    void rotateWithRightChild( AVLNode * & t );
    void doubleWithLeftChild( AVLNode * & t);
    void doubleWithRightChild( AVLNode * & t);

    bool contains(const Comparable & x, AVLNode* t) const;
    void insert(const Comparable & x, AVLNode* &t);
    void remove(const Comparable &x, AVLNode *&t);
    bool isBalanced(AVLNode *t) const;
    double totalDepth(AVLNode *t, int depth) const;
    bool isBST(AVLNode* t, AVLNode* minNode, AVLNode* maxNode) const;
    int treeSize(AVLNode* t) const;
    int treeHeight(AVLNode *t) const;
    typename AVLTree<Comparable>::AVLNode *removeByRankHelper(AVLNode *t, int &rank);

};

// constructor
template <class Comparable>
AVLTree<Comparable>::AVLTree() : root(NULL) {}

// destructor
template <class Comparable>
AVLTree<Comparable>::~AVLTree()
{
    makeEmpty();
}

// public makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode * & t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// public findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMin() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMin(root)->element;
}

// private findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMax() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMax(root)->element;
}

// private findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMax(t->right);
    }
}

// start our implementation:
// public contains: follow the contains in BST, referring to textbook, Figure 4.17 and Figure 4.18
template<typename Comparable>
bool AVLTree<Comparable>::contains( const Comparable & x ) const 
{
    return contains(x, root); //calls the helper function
}

//private helper function 
template<typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable & x, AVLNode* t) const
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

// public insert: following BST, referring to textbook, Figure 4.17 and Figure 4.23
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x)
{
   insert(x, root); //calls helper
}

//private insert
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x, AVLNode* &t)
{
    if (t == nullptr) //empty tree
	{
        t = new AVLNode(x, nullptr, nullptr);
        t->height = 0;

	}
    else if (x < t->element) //insert in left subtree
	{
        insert(x, t->left);
	}
    else if (t->element < x) //insert in right subtree
	{
        insert(x, t->right);
	}

    balance(t);
}

// public remove: refer to textbook, Figure 4.17 and Figure 4.26
template<typename Comparable>
void AVLTree<Comparable>::remove( const Comparable & x ) 
{
   remove(x, root);
}

//private remove
template<typename Comparable>
void AVLTree<Comparable>::remove( const Comparable & x, AVLNode* &t ) 
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
		AVLNode *oldNode = t; //node to be deleted
		t = (t->left != nullptr) ? t->left : t->right; //bypass the node
		delete oldNode; //delete the node
	}

   if (t != nullptr) {
        t->height = std::max(treeHeight(t->left), treeHeight(t->right)) + 1;
    }
    balance(t);
}

// private balance: refer to textbook, Figure 4.42, Line 21 - 40
// assume t is the node that violates the AVL condition, and we then identify which case to use (out of 4 cases)
template<typename Comparable>
void AVLTree<Comparable>::balance(AVLNode * & t) 
{
    if (t == nullptr) //empty tree
    {
        return;
    }
    if (treeHeight(t->left) - treeHeight(t->right) > ALLOWED_IMBALANCE) //left subtree is higher
    {
        if (treeHeight(t->left->left) >= treeHeight(t->left->right)) 
        {
            rotateWithLeftChild(t);
        } 
        else 
        {
            doubleWithLeftChild(t);
        }
    } 
    else if (treeHeight(t->right) - treeHeight(t->left) > ALLOWED_IMBALANCE) //right subtree is higher
    {  
        if (treeHeight(t->right->right) >= treeHeight(t->right->left)) 
        {
            rotateWithRightChild(t);
        }
        else 
        {
            doubleWithRightChild(t);
        }
    }

    //update height after balancing
    t->height = std::max(treeHeight(t->left), treeHeight(t->right)) + 1;
}

// private rotateWithLeftChild: for case 1, referring to textbook, Figure 4.44 (code) and Figure 4.43 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode * & k2) 
{
    if (k2 == nullptr || k2->left == nullptr) //empty tree
    {
        return;
    }

    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    
    //update the heights
    k2->height = max(treeHeight(k2->left), treeHeight(k2->right)) + 1;
    k1->height = max(treeHeight(k1->left), k2->height) + 1;

    //update the reference
    k2 = k1;
}

// private rotateWithRightChild: for case 4 (the mirrored case of case 1)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode * & k2) 
{
    if (k2 == nullptr || k2->right == nullptr) //empty tree
    {
        return;
    }

    AVLNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    //update the heights
    k2->height = max(treeHeight(k2->left), treeHeight(k2->right)) + 1;
    k1->height = max(treeHeight(k1->right), k2->height) + 1;

    //update the reference
    k2 = k1;
}

// private doubleWithLeftChild: for case 2, see textbook, Figure 4.46 (code) and Figure 4.45 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode * & k3) 
{
    if (k3 == nullptr || k3->left == nullptr) //empty tree
    {
        return;
    }
    
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// private doubleWithRightChild: for case 3 (the mirrored case of case 2)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode * & k3) 
{
    if (k3 == nullptr || k3->right == nullptr) //empty tree
    {
        return;
    }

    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3); 
}

// public isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced() const 
{
   return isBalanced(root);
}

// private isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced(AVLNode* t) const 
{
    if (t == nullptr) 
    {
        return true;
    }

    int leftHeight = treeHeight(t->left);
    int rightHeight = treeHeight(t->right);

    return abs(leftHeight - rightHeight) <= 1 && isBalanced(t->left) && isBalanced(t->right);
}

// public isBST
template <class Comparable>
bool AVLTree<Comparable>::isBST() const 
{
    return isBST(root, nullptr, nullptr);
}

template <class Comparable>
bool AVLTree<Comparable>::isBST(AVLNode* t, AVLNode* minNode, AVLNode* maxNode) const 
{
    if (t == nullptr) 
    {
        return true;
    }
    if ((minNode != nullptr && t->element <= minNode->element) || (maxNode != nullptr && t->element >= maxNode->element)) //check if the current node violates the BST property
    {
        return false;
    }
    return isBST(t->left, minNode, t) && isBST(t->right, t, maxNode); //check the left and right subtrees
}

// public treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize() const 
{
    return treeSize(root);
}

// private treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize(AVLNode* t) const 
{
    if (t == nullptr) 
    {
        return 0;
    }
    return 1 + treeSize(t->left) + treeSize(t->right); //recursively count the number of nodes
}

// public computeHeight. See Figure 4.61 in Textbook
template <typename Comparable>
int AVLTree<Comparable>::computeHeight() const 
{
    return treeHeight(root);
}

// public readRootHeight
template <typename Comparable>
int AVLTree<Comparable>::readRootHeight() const 
{
    if (root == nullptr) 
    {
        return -1;
    }
    return root->height;
}

// public averageDepth
template <typename Comparable>
double AVLTree<Comparable>::averageDepth() const 
{
    if (root == nullptr) 
    {
        return 0.0;
    }
    return totalDepth(root, 0) / static_cast<double>(treeSize());
}

// private totalDepth
template <typename Comparable>
double AVLTree<Comparable>::totalDepth(AVLNode* t, int depth) const 
{
    if (t == nullptr) 
    {
        return 0;
    }
    return depth + totalDepth(t->left, depth + 1) + totalDepth(t->right, depth + 1);
}

// public removeByRank
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(int rank) 
{
    if (rank < 1 || rank > treeSize()) 
    {
        throw out_of_range("Rank is out of range"); //check if the rank is valid
    }
    root = removeByRankHelper(root, rank);
}

template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::removeByRankHelper(AVLNode* t, int &rank) 
{
    if (t == nullptr) 
    {
        return nullptr;
    }

    int leftSize = treeSize(t->left);

    //navigate to the correct rank
    if (rank <= leftSize) 
    {
        //rank is in the left subtree
        t->left = removeByRankHelper(t->left, rank);
    } 
    
    else if (rank == leftSize + 1) 
    {
        //rank corresponds to this node
        AVLNode* oldNode = t;
        if (t->left != nullptr && t->right != nullptr) 
        {
            //node with two children: replace with minimum in right subtree
            t->element = findMin(t->right)->element;
            t->right = removeByRankHelper(t->right, rank);  //continue removing the min
        } 
        
        else 
        {
            //node with one or no children: bypass
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    } 
    
    else 
    {
        //rank is in the right subtree
        rank -= (leftSize + 1);  //adjust rank for right subtree traversal
        t->right = removeByRankHelper(t->right, rank);
    }

    //rebalance and update the height of the tree
    if (t != nullptr) 
    {
        t->height = std::max(treeHeight(t->left), treeHeight(t->right)) + 1;
        balance(t);
    }

    return t;
}

// private treeHeight
template <typename Comparable>
int AVLTree<Comparable>::treeHeight(AVLNode *t) const 
{
    return t == nullptr ? -1 : t->height; //return the height of the tree
}
;