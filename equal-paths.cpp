#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

int pathLength(Node* root);
bool equalPaths(Node * root)
{
    // Add your code below
    if (root==NULL){
        return true;
    }
    if (root->left == NULL){ // edge case 1 child
        if (pathLength(root->right)==1){
            return true;
        }
    }
    if (root->right == NULL){ // edge case 1 child
        if (pathLength(root->left)==1){
            return true;
        }
    }
    int leftLength = pathLength(root->left);
    int rightLength = pathLength(root->right);
    if (leftLength == -1 || rightLength == -1){
        return false; //there is a leaf path somewhere that does not reach the same length
    }
    return leftLength==rightLength;
}

int pathLength(Node* root){
    if (root==NULL){
        return 0;
    }
    if (root->left == NULL && root->right == NULL){ // leaf node
        return 1;
    }
    int leftLength = pathLength(root->left);
    int rightLength = pathLength(root->right);
    if (leftLength==-1 || rightLength==-1){
        //this is my error case, so if error is received,
        //propagate the error
        return -1; 
    }
    if (leftLength>rightLength || rightLength<leftLength){
        if (!leftLength==0 && !rightLength==0){
            // say you have lengths 2 and 1 at this node: 
            // clearly all lengths to leaves are unequal
            return -1; // unbalanced lengths are ok if one side is a leaf
        }
    }
    if (leftLength>rightLength){
        return 1+leftLength;
    }
    return 1+rightLength;
}
