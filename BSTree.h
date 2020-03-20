/*
 * Tomomi Nakamura
 * Banking
 * file @ BSTree.h
 */
//This is a header file for Binary Search Tree class
#include "Account.h"

#ifndef HW6_BANKING_BSTREE_H
#define HW6_BANKING_BSTREE_H

class BSTree
{
public:
    //constructor
    BSTree();
    //destructor
    ~BSTree();

    //inserting new account into BST
    bool insert(Account *);

    // retrieve object, first parameter is the ID of the account
    // second parameter holds pointer to found object, NULL if not found
    bool Retrive(const int&, Account *&) const;

    //Displaying all account in BST
    void Display() const;
    //Emptying BST
    void Empty();
    //Checking is BST is empty
    bool isEmpty() const;
    //Returning vector which contains all accounts in BST
    vector<Account> GetAllAccount();

private:
    //structure for Nofr
    struct Node{
        Account *pAccount;
        Node *right;
        Node *left;
        Node(Account* account, Node* right, Node* left);
        ~Node();
    };
    //root node of BST
    Node *root;
    int size;   //number of nodes

    //private methods for each method above
    bool insert(Account *, Node* curr);
    bool Retrive(const int&, Account *&, Node* curr) const;
    void Display(Node* curr) const;
    void Empty(Node* curr);
    void GetAllAccount(Node* curr, vector<Account>&) ;

};
#endif //HW6_BANKING_BSTREE_H
