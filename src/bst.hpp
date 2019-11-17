#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
#include "node.hpp"


template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
    void inorder_helper(Node <T> *helper, std::vector<T> *vec);
    void preorder_helper(Node <T> *prehelper, std::vector<T> *vec);
    void postorder_helper(Node <T> *posthelper, std::vector<T> *vec);


private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    //std::cout <<"printing inorder func \n";

    std::vector<T> *vec = new std::vector<T>;
    inorder_helper(root, vec);
    //std::cout <<"\n";
    //std::cout <<"done with inorder func \n";
    return vec;
}

template<class T>
void BST<T>::inorder_helper(Node <T> *helper, std::vector<T> *vec)
{
    //helper = root;
    if(helper == NULL)
    {
        return;
    }
    inorder_helper(helper->get_left(), vec);
    vec->push_back(helper->get_data());
    //std::cout << helper->get_data()<<" ";
    inorder_helper(helper->get_right(), vec);
    return;
}


template<class T>
 std::vector<T> * BST<T>::preorder()
{
    //std::cout <<"printing preorder func \n";

    std::vector<T> *vec = new std::vector<T>;
    preorder_helper(root,vec);
    //std::cout << "\n";
    //std::cout <<"done with preorder func \n";
    return vec;
}

template<class T>
void BST<T>::preorder_helper(Node <T> *prehelper, std::vector<T> *vec)
{
    if(prehelper == NULL)
    {
        return;
    }
    preorder_helper(prehelper->get_left(), vec);
    //std::cout << prehelper->get_data()<<" ";
    preorder_helper(prehelper->get_right(), vec);
    vec->push_back(prehelper->get_data());
    return;
}


template<class T>
 std::vector<T> * BST<T>::postorder()
{
    //std::cout <<"printing postordeer func \n";

    std::vector<T> *vec = new std::vector<T>;
    postorder_helper(root,vec);
    //std::cout << "\n";
    //std::cout <<"done with postorder func \n";
    return vec;
}

template<class T>
void BST<T>::postorder_helper(Node <T> *posthelper, std::vector<T> *vec)
{
     if(posthelper == NULL)
     {
         return;
     }
     vec->push_back(posthelper->get_data());
     postorder_helper(posthelper->get_left(), vec);
     //std::cout << posthelper->get_data()<<" ";
     postorder_helper(posthelper->get_right(), vec);
     return;
}


template<class T>
void BST<T>::insert(T new_data)
{
    //new data
    Node<T> *node = new Node<T>(new_data);
    //current iterator
    Node<T> *cur = new Node<T>;
    //left node ptr
    Node<T> *lnode  =  new Node<T>;
    //right node ptr
    Node<T> *rnode =  new Node<T>;
    //std::cout << "New node is " << node->get_data() << "\n";

    //if root is null, assign a value
    if(root == NULL)
    {
        
        //node = node
        //Cur = cur
        root = node;
        //set root's left to NULL
        root->set_left(NULL);
        //set root's right to NULL
        root->set_right(NULL);
        //std::cout << "root is " << root->get_data() << "\n";
    }
    else {
        cur = root;
        while(cur != NULL)
        {
            if(node->get_data() < cur->get_data())
            {
                //std::cout << node->get_data() << " is less than " << cur->get_data()<< " inserting on the left\n";
                
                if (cur->get_left() == NULL)
                {
                    cur->set_left(node);
                    cur = NULL;
                }
                else
                {
                    cur = cur->get_left();
                }
            }
            else
                if(cur->get_right() == NULL)
                {
                    cur->set_right(node);
                    cur = NULL;
                }
                else
                {
                    cur->set_right(node);
                    node->set_left(NULL);
                    node->set_right(NULL);
                    cur = NULL;
                }
        }
    node_count++;
    }
}

template<class T>
Node<T> *BST<T>::search(T val)
{    std::cout << "**********searching for a value \n";

    Node<T> *key = new Node<T>(val);
    Node<T> *cur = root;
    std::cout << "searching for a " << key->get_data() << "\n";
    //std::cout << "searching for a " << cur->get_data() << "\n";
    while(cur != NULL)
    {
         if (key->get_data() == cur->get_data())
         {
            return cur;
         }
        else if(key->get_data() < cur->get_data())
        {
            cur = cur->get_left();
        }
        else if(key->get_data() > cur->get_data())
        {
        cur = cur->get_right();
        }
        else
        {
            cur = NULL;
        }
    }
}


template<class T>
void BST<T>::remove(T val)
{
    Node<T> *par = new Node<T>(val);
    Node<T> *cur = root;
    while(cur != NULL)
    {
        if(cur->get_data() == par->get_data())
        {
                 if(!cur->get_left()->get_data() && !cur->get_right()->get_data())
                 {
                     if(par->get_left()->get_data() == cur->get_data())
                     {
                         root = NULL;
                     }
                    else if(par->get_left()->get_data() == cur->get_data())
                    {
                        root->set_left(NULL);
                    }
                    else
                    {
                        root->set_right(NULL);
                    }
                 }
                else if(cur->get_left()->get_data() && !cur->get_right()->get_data())
                {
                    if(!par)
                    {
                        root = cur->get_left();
                    }
                    else if(par->get_left() == cur)
                    {
                        par->set_left(cur->get_left());
                    }
                    else
                    {
                        par->set_right(cur->get_left());
                    }
                }
                else if(!cur->get_left()->get_data() && cur->get_right()->get_data())
                {
                    if(!par)
                    {
                        root = cur->get_right();
                    }
                    else if (par->get_left()->get_data() == cur->get_data())
                    {
                        par->set_left(cur->get_right());
                    }
                    else
                    {
                        par->set_right(cur->get_right());
                    }
                }
                else
                {
                    Node<T> *suc = new Node<T>;
                    suc = cur->get_right();
                    while (suc->get_left() != NULL)
                    {
                        suc = suc->get_left();
                        Node<T> *sucData = new Node<T>;
                        sucData = suc;
                        remove(suc->get_data());
                        cur = sucData;
                        return;
                    }
                    return;

                }
                }
        else if(cur->get_data() < root->get_data())
            {
                par = cur;
                cur = cur->get_right();
            }
        else
            {
                par = cur;
                cur = cur->get_left();
            }
        }
    node_count--;
    return;
}
 
    
    /*std::cout << "node count is "  << node_count << "\n";

    std::cout << "Initiating removal \n";
    
    Node<T> *itr = new Node<T>(val);
    
    std::cout << "Searching for a  " << itr->get_data()<< " to delete\n";
    
    //execute while root has data
    while (itr != NULL)
    {
        //if root equals searched value, return searched value
        if(itr->get_data() == val)
        {
            std::cout << "Value found: " << itr->get_data() << "\n";
            std::cout << "node count is "  << node_count << "\n";
        }
        //if root did not equal searched value
        //itr = left node
        if(itr->get_left()->get_data() <= val)
        {
            itr = itr->get_left();
        }
        //if left node did note equal value
        //itr = right node
        if(itr->get_right()->get_data() >= val)
        {
            itr = itr->get_right();
        }
        //repeats while loop until itr = val
    }
    std::cout << "Reducing node count \n";
    node_count--;
    std::cout << "node count is "  << node_count << "\n";
     */

template<class T>
int BST<T>::get_size()
{
    return node_count;
}
