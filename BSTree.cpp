/*
 * Tomomi Nakamura
 * Banking
 * file @ BSTree.cpp
 */

#include "BSTree.h"
#include "Account.h"

//default constructo
BSTree::BSTree() {
 root = NULL;
 size = 0;
}

//destructor
BSTree::~BSTree() {
    Empty();
}

//inserting new account into BST
bool BSTree::insert(Account * account) {
    if (isEmpty())
    {
        root = new Node(account, NULL, NULL);
        size++;
        return true;
    } else  {
        return insert(account, root);
    }
}
//private method for insert
bool BSTree::insert(Account *account, BSTree::Node* curr) {
    if (account->GetClientId() == curr->pAccount->GetClientId())
    {
        cout << "ERROR: Account " <<  account->GetClientId() << " is already open. Transaction refused." << endl;
        cout << endl;
        return false;
    }
    else if (account->GetClientId() < curr->pAccount->GetClientId())
    {
        if (curr->left == NULL)
        {
            curr->left = new Node(account, NULL, NULL);
            size++;
            return true;
        } else {
            return insert(account, curr->left);
        }
    }
    else if (account->GetClientId() > curr->pAccount->GetClientId())
    {
        if (curr->right == NULL)
        {
            curr->right = new Node(account, NULL, NULL);
            size++;
            return true;
        } else {
            return insert(account, curr->right);
        }
    }
}

// retrieve object, first parameter is the ID of the account
// second parameter holds pointer to found object, NULL if not found
bool BSTree::Retrive(const int &clientId, Account *&account) const {
    if (isEmpty())
    {
        return false;
    }
    else {
        return Retrive(clientId, account, root);
    }
}
//private method for retrive
bool BSTree::Retrive(const int &clientId, Account *&account, BSTree::Node *curr) const {

    if (curr == NULL)
    {
        cout << "ERROR: Account " << clientId <<  " not found. Transferal refused.";
        cout << endl;
        return false;
    }
    else if (clientId == curr->pAccount->GetClientId())
    {
        account = curr->pAccount;
        return true;
    }
    else if (clientId < curr->pAccount->GetClientId())
    {
        return Retrive(clientId, account, curr->left);
    }
    else {
        return Retrive(clientId, account, curr->right);
    }
}
//Displaying all account in BST
void BSTree::Display() const {
    cout << "Displaying BST" << endl;
    if (!isEmpty())
    {
        Display(root);
    }
    cout << endl;
}
//private method for display
void BSTree::Display(BSTree::Node *curr) const {
    if (curr == NULL)
    {
        return;
    }
    Display(curr->left);
    cout << curr->pAccount->GetClientId() << ", " << curr->pAccount->GetFirstName() << endl;
    Display(curr->right);
}


//Checking is BST is empty
bool BSTree::isEmpty() const {
    return root == NULL;
}

//Emptying BST
void BSTree::Empty() {
    if (!isEmpty())
    {
        Empty(root);
        //delete root;
        root = NULL;
        size = 0;
    }
}
//private method for empty()
void BSTree::Empty(BSTree::Node *curr) {
    if (curr == NULL)
    {
        return;
    }
    Empty(curr->left);
    Empty(curr->right);

    delete curr;
    //delete curr->right;
    //delete curr->left;
    //curr->pAccount = NULL;
    //curr->right = NULL;
    //curr->left = NULL;
    curr = NULL;
}

//Returning vector which contains all accounts in BST
vector<Account> BSTree::GetAllAccount()  {
    if (!isEmpty())
    {
        vector<Account> v;

        GetAllAccount(root, v);
        return v;
    }
}

//private method for getAllAccount()
void BSTree::GetAllAccount(BSTree::Node *curr, vector<Account>& v)  {
    if (curr == NULL)
    {
        return;
    }
    GetAllAccount(curr->left, v);
    v.push_back(*(curr->pAccount));
    GetAllAccount(curr->right, v);
}

//constructor for Node
BSTree::Node::Node(Account *account, BSTree::Node *right, BSTree::Node *left)
: pAccount{account}, right{right}, left{left} {  }

//destructor for Node
BSTree::Node::~Node() {
    delete pAccount;
    pAccount = NULL;
}
