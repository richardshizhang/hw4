#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;



int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    AVLTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    bt.print();

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair(20,20));
    at.insert(std::make_pair(10,10));
    at.insert(std::make_pair(30,30));
    at.insert(std::make_pair(8,8));
    at.insert(std::make_pair(15,15));
    at.insert(std::make_pair(25,25));
    at.insert(std::make_pair(35,35));
    at.insert(std::make_pair(5,5));
    at.insert(std::make_pair(12,12));
    at.insert(std::make_pair(17,17));
    at.insert(std::make_pair(28,28));
    at.insert(std::make_pair(14,14));
    // at.insert(std::make_pair('a',1));
    // at.insert(std::make_pair('b',2));
    // at.insert(std::make_pair('c',4));
    // at.insert(std::make_pair('f',4));
    // at.insert(std::make_pair('g',5));
    // at.insert(std::make_pair('h',6));
    // at.insert(std::make_pair(15,7));
    at.print();
    // cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    at.remove(10);
    at.print();
    return 0;
}