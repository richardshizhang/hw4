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
    if (root->left == NULL){
        if (pathLength(root->right)==1){
            return true;
        }
    }
    if (root->right == NULL){
        if (pathLength(root->left)==1){
            return true;
        }
    }
    return pathLength(root->left)==pathLength(root->right);
}

int pathLength(Node* root){
    if (root==NULL){
        return 0;
    }
    if (root->left == 0 && root->right == 0){ // leaf node
        return 1;
    }
    int leftLength = pathLength(root->left);
    int rightLength = pathLength(root->right);
    if (leftLength>rightLength){
        return 1+leftLength;
    }
    return 1+rightLength;
}
