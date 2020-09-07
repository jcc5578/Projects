/****************************************
** File:    AugmentedBinarySearchTree.cpp
** Project: CSCE 221 Project 2
** Author:  ???
** Date:    ???
** Section: ???
** E-mail:  ???
**
**  C++ file:
**	Breif Description of the file
**
**	
**
*******************************************/
#include "AugmentedBinarySearchTree.h"
#ifndef AUGMENTED_BINARY_SEARCH_TREE_CPP
#define AUGMENTED_BINARY_SEARCH_TREE_CPP
template<class Comparable>
AugmentedBinarySearchTree<Comparable>::AugmentedBinarySearchTree() : root(NULL)
{
}
template<class Comparable>
AugmentedBinarySearchTree<Comparable>::AugmentedBinarySearchTree(const AugmentedBinarySearchTree<Comparable>& rhs) : root(NULL)
{
    *this = rhs;
}

template<class Comparable>
AugmentedBinarySearchTree<Comparable>::~AugmentedBinarySearchTree()
{
    makeEmpty();
    delete ret;
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::remove(const Comparable& x)
{
    int check = remove(x, root);
    return check;
}
template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsPerfect()
{
    int height = 0;
    queue<BinaryNode<Comparable>*> q;
    return IsPerfect(q, height);
}

template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsComplete()
{
    int height = 0;
    queue<BinaryNode<Comparable>*> q;
    return IsPerfect(q, height);
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::PrintLevels(int numlevels)
{
    queue<BinaryNode<Comparable>*> q;
    PrintLevels(q, numlevels);
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::RemoveResidue()
{
    int deletions = 0;
    RemoveResidue(root, &deletions);
    return deletions;
}
//Nth element Boot strap
template<class Comparable>
const Comparable& AugmentedBinarySearchTree<Comparable>::NthElement(int n)
{
    int nodeVisited = 1;
    if (n > root->m_size || n < 1)
    {
        try {
            throw ItemNotFound();
        }
        catch (std::exception const & ex) {
            std::cerr << ex.what() << "There does not exist an nth element in the BST" << '\n' << endl;
        }
        return ret->element;
    }
    return NthElement(root, &nodeVisited, n)->element;
// TODO: insert return statement here
}
//Rank Bootstrap
template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::Rank(const Comparable& x)
{
    int nodeVisited = 1;
    Rank(x, root, &nodeVisited);
    return nodeVisited;
}

template<class Comparable>
const Comparable& AugmentedBinarySearchTree<Comparable>::Median()
{
    if (root == nullptr)
    {
        try {
            throw ArgumentIsNull();
        }
        catch (std::exception const & ex) {
            std::cerr << ex.what() << "No median value for a tree of zero size" << '\n' << endl; 
        }
        return ret->element;
        
    }
    int size = root->m_size;
    if (size % 2 == 0) //if even number of nodes
    {
        size = size/2;
        return NthElement(size);
    }
    else  //if odd number of nodes
    {
        size = size/2 + 1;
        return NthElement(size);
    }

}

template<class Comparable>
BinaryNode<Comparable>* AugmentedBinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t) const
{
    if (t== nullptr)
    {
        return nullptr;
    }
    if (t->left == nullptr)
    {
        return t;
    }
    return findMin(t->left);
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::insert(const Comparable& x)
{
    insert(x, root);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////SEPERATES BOOTSTRAP ABOVE
template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::insert(const Comparable& x, BinaryNode<Comparable>*& t) const
{
    static bool dupl = false;
    if (t == nullptr)
    {
        t = new BinaryNode<Comparable>(x, NULL, NULL);
        t->m_size = 1;
    }
    else if(x < t->element)
    {
        insert (x, t->left);
        if (dupl == false)
        {
            t->m_size++;
        }
    }
    else if (t-> element < x)
    {
        insert(x, t->right);
        
        if (dupl == false)
        {
            t->m_size++;
        }
    }
    else if (t->element == x)
    {
        dupl = true;
        return 0;
    }
    dupl = false;
    return 0;
}

template<class Comparable>
int AugmentedBinarySearchTree<Comparable>::remove(const Comparable& x, BinaryNode<Comparable>*& t) const
{
    int check;
	if (t != nullptr) {
		if (x < t->element) //if compared item is smaller than current node
        { 
			check = remove(x, t->left);
			if (check != 0) 
            {
				t->m_size -= 1;
				return 1;
			}
			else 
            {
				return 0;
			}
		}
		else if (t->element < x) //if compared item is larger than current node
        { 
			check = remove(x, t->right);
			if (check != 0) 
            {
				t->m_size -= 1;
				return 1;
			}
			else 
            {
				return 0;
			}
		}
		else if (t->element == x) 
        {
			if (t->left != nullptr && t->right != nullptr) //if the item to be removed has 2 children
			{
				t->element = findMin(t->right)->element;
				remove(t->element, t->right);
			}
			else //if only one child exists in located item
			{
				BinaryNode <Comparable>* node = t;
				t = (t->left != nullptr) ? t->left : t->right;
				delete node;
			}
			return 1;
		}
		else 
        { 
			return 0;
		}
	}
	else return 0;

}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::PrintLevels(queue<BinaryNode<Comparable>*> q, int levels) //if asking for 1 level, show lvl 0, if asking for 2 levels, show lvl 0 and 1
{
    int pcounter = -1;
    int counter, limit, i = 0; //counter is used to determine when to skip lines for next lvl, limit for when 6 nodes is reached, and i to print the respective levels
    if (root == nullptr)
    {
        return;
    }
    BinaryNode<Comparable> *cursor = nullptr;
    queue<BinaryNode<Comparable>*> pq; //parent queue
    q.push(root);
    while(!q.empty() && levels > 0)
    {
        cout << "Level " << i << ": " << endl;
        limit = 0;
        counter = q.size();
        while(counter > 0)
        {
            limit++;
            cursor = q.front();
            pq.push(q.front());

            if (cursor == root) //account only for root
            {
                cout << "(" << cursor->element << ", " << cursor->m_size << ", NULL)";
            }
            else if (cursor->m_size != -1 && cursor->element != -1) // if element and m_size is not NULL
            {
                if (pq.front()->element != -1)
                    cout << "(" << cursor->element << ", " << cursor->m_size << ", " << pq.front()->element <<  ")"; 
                else
                {
                    cout << "(" << cursor->element << ", " << cursor->m_size << ", NULL)";
                }
                
            }
            else // if element and m_size is NULL
            {
                if (pq.front()->element != -1)
                    cout << "(" << "NULL, NULL, " << pq.front()->element << ")"; 
                else
                {
                    cout << "(NULL, NULL, NULL)";
                }
            }
            q.pop();
            pcounter++;
            if (pcounter >= 2)
            {
                pcounter = 0;
                pq.pop();
            }
            if (levels > 1)
                {
                    if(cursor->left != nullptr)
                    {
                        q.push(cursor->left);
                    }
                    else 
                    {
                        cursor->left = new BinaryNode<Comparable>();
                        q.push(cursor->left);
                    }
                    if(cursor->right != nullptr)
                    {
                        q.push(cursor->right);
                    }
                    else
                    {
                        cursor->right = new BinaryNode<Comparable>();
                        q.push(cursor->right);
                    }
                    
                    
                }
            counter--;
            if (limit == 6)
            {
                cout << endl;
                limit = 0;
            }
            
        }
        cout << endl << endl;
        levels--;
        i++;
    }
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::RemoveResidue(BinaryNode<Comparable>*& t, int* deletions) const
{
    if (root == nullptr)
    {
        deletions = 0;
        return;
    }
    if (t != nullptr)
    {
        RemoveResidue(t->left, deletions);
        RemoveResidue(t->right, deletions);
        if (t->element == -1)
        {
            (*deletions)++;
            delete t;
            t = nullptr;
        }
    }
    
}

template<class Comparable>
BinaryNode<Comparable>* AugmentedBinarySearchTree<Comparable>::NthElement(BinaryNode<Comparable>* t, int* nodesVisited, int n) const
{
    if (t == nullptr)
    {
        return nullptr;
    }
    if (t->left != nullptr) //if left child exists
    {
        BinaryNode<Comparable>* temp = NthElement(t->left, nodesVisited, n);
        if(temp)
            return temp;
    }
    if (*nodesVisited == n) //if nth node located, return
        return t;
    (*nodesVisited)++;
    if (t->right != nullptr) //check if left child exists
    {
        BinaryNode<Comparable>* temp = NthElement(t->right, nodesVisited, n);
        if(temp)
            return temp;
    }
    return nullptr;
}

template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::Rank(const Comparable& x, BinaryNode<Comparable>* t, int* nodesVisited) const
{
    if (root == nullptr)
    {
        *nodesVisited = -1;
        return;
    }
    if (t != NULL) 
    {
        if (x < t->element)
        {
            Rank(x, t->left, nodesVisited);
        }
        else if (x > t->element)
        {
            if (t->left != nullptr)
            {
                *nodesVisited += t->left->m_size;
            }
            *nodesVisited += 1;
            Rank(x, t->right, nodesVisited);
        }
        else if (x == t->element)
        {
            if (t->left != nullptr)
            {
                *nodesVisited += t->left->m_size;
            }
        }
        else
        {
            return;
        }
        
    }
    else
    {
        try {
                throw (NodeNotFound());
            }
            catch (std::exception const & ex) {
                std::cerr << ex.what() << "BST does not contain element " << x << '\n' << endl;
            }
            *nodesVisited = -1;
            return;
    }
    
    
}

template<class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsPerfect(queue<BinaryNode<Comparable>*> q, int height)
{
    height = 0;
    if (root == nullptr)
    {
        return true; //empty tree is perfect
    }
    BinaryNode<Comparable> *cursor = nullptr;
    q.push(root);
    while(!q.empty())
    {
        cursor = q.front();
        q.pop();
        if(cursor->left != nullptr && cursor->right != nullptr) //if the node has both left and right child
        {
            if(height == 1) //check if leaf node height has already been located
                return false;
        
            else
            {
                q.push(cursor->left); //push in left and right if leaf not found yet
                q.push(cursor->right);
            }
        }
        else if (cursor->left == nullptr && cursor->right == nullptr) //if leaf node is found, mark height
        {
            height = 1;
        }
        else if (cursor->left == nullptr || cursor->right == nullptr) //if the node has only one child
        {
            return false;
        }
    }
return true;
}
template <class Comparable>
bool AugmentedBinarySearchTree<Comparable>::IsComplete(queue <BinaryNode<Comparable>*> q, int height)
{
    height = 0;
    if (root == nullptr)
    {
        return true; //empty tree is complete
    }
    BinaryNode<Comparable> * cursor = nullptr;
    q.push(root);
    while(!q.empty())
    {
        cursor = q.front();
        q.pop();
        if (height == 1 && (cursor->left || cursor->right)) //check if left or right node exists past level
        {
            return false;
        }
        if (cursor->left == nullptr && cursor->right != nullptr) //checks if right node exists without left node
        {
            return false;
        }
        if (cursor->left)
        {
            q.push(cursor->left);
        }
        else
        {
            height = 1;
        }
        
        if(cursor->right)
        {
            q.push(cursor->right);
        }
        else
        {
            height = 1;
        }
    }
    return 1;
}
template<class Comparable>
void AugmentedBinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable>*& t) const
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

#endif