#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateRight(AVLNode<Key,Value>* center);
    void rotateLeft(AVLNode<Key,Value>* center);
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, int8_t diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    Key k = new_item.first;
    Value v = new_item.second;
    if (this->root_==NULL){
        this->root_ = new AVLNode<Key,Value>(k,v, NULL);
        return;
    }
    bool locFound = false; //before the location for the node found
    AVLNode<Key,Value>* c = static_cast<AVLNode<Key,Value>*>(this->root_);//current node
    AVLNode<Key,Value>* n = NULL;
    while(!locFound){
        if (k == c->getKey()){//key exists
            c->setValue(v);
            return;
        }
        if (k < c->getKey()){//go left
            if(c->getLeft()==NULL){
                n = new AVLNode<Key,Value>(k,v,c);
                c->setLeft(n);
                break;
            }
            c = c->getLeft();
        }
        if (k > c->getKey()){//go right
            if(c->getRight()==NULL){
                n = new AVLNode<Key,Value>(k,v,c);
                c->setRight(n);
                break;
            }
            c = c->getRight();
        }
    }
    n->setBalance(0);
    AVLNode<Key,Value>* p = n->getParent();
    if (p->getBalance() == -1 || p->getBalance() == 1){
        p->setBalance(0);
        return;
    }
    if (p->getBalance()==0){
        if (p->getKey()>k){// we are a left child, right-left notation
            p->setBalance(-1);
        }
        else{ // we are a right child
            p->setBalance(1);
        }
        insertFix(p,n);
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
}
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* center){
    AVLNode<Key,Value>* lc = center->getLeft();
    AVLNode<Key,Value>* temp = lc->getRight();
    AVLNode<Key,Value>* g = center->getParent();
    
    lc->setParent(g);
    center->setParent(lc);

    center->setLeft(temp);
    if (temp != NULL){
        temp->setParent(center);
    }

    lc->setRight(center);

    if (g!=NULL){
        if (g->getLeft()==center)g->setLeft(lc);
        else g->setRight(lc);
    }
    else{
        this->root_ = lc;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* center){
    AVLNode<Key,Value>* rc = center->getRight();
    AVLNode<Key,Value>* temp = rc->getLeft();
    AVLNode<Key,Value>* g = center->getParent();

    rc->setParent(g);
    center->setParent(rc);

    center->setRight(temp);
    if (temp != NULL){
        temp->setParent(center);
    }

    rc->setLeft(center);

    if (g!=NULL){
        if (g->getLeft()==center)g->setLeft(rc);
        else g->setRight(rc);
    }
    else{
        this->root_ = rc;
    }
    
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    if (p==NULL || p->getParent()==NULL){
        return;
    }
    AVLNode<Key,Value>* g = p->getParent();//grandparent
    if (p->getKey() < g->getKey()){ //parent is left child
        g->updateBalance(-1);
        if (g->getBalance()==0){//case 1
            return;
        }
        if (g->getBalance()==-1){//case 2
            insertFix(g,p);
        }
        if (g->getBalance()==-2){//case 3
            if (p->getBalance()==-1){
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            if (p->getBalance()==1){
                rotateLeft(p);
                rotateRight(g);
                //cases 3a to 3c
                if(n->getBalance()==0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                if(n->getBalance()==1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                if(n->getBalance()==-1){
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                }
            }
            return;
        }
    }
    else{ // parent is right child
        g->updateBalance(1);
        if (g->getBalance()==0){//case 1
            return;
        }
        if (g->getBalance()==1){//case 2
            insertFix(g,p);
        }
        if (g->getBalance()==2){//case 3
            if (p->getBalance()==1){
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            }
            if (p->getBalance()==-1){
                rotateRight(p);
                rotateLeft(g);
                //cases 3a to 3c
                if(n->getBalance()==0){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                if(n->getBalance()==-1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
                if(n->getBalance()==1){
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                }
            }
            return;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, int8_t diff){

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
