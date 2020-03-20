/*
 * Tomomi Nakamura
 * Banking
 * file @ Bank.h
 */
//This is a header file for Bank class
#include "BSTree.h"
#include "Account.h"
#include <iostream>
#include <queue>
#include <map>
using namespace std;

#ifndef HW6_BANKING_BANK_H
#define HW6_BANKING_BANK_H

class Bank
{
public:
    //default constructor
    Bank();
    //constructor
    explicit Bank(string fileName);
    //destructor
    ~Bank();

    //reading input file passed by constructor
    // and store each lines in queue
    void ReadFile(string fileName);
    //doing each transaction based on lines stored in queue
    void DoTransactions();

    //Opening account
    bool OpenAccount(string info);
    //depositing fund
    bool Deposit(string info);
    //withdrawing fund
    bool Withdraw(string info);
    //transferring fund between Money Market and Primary Money Market
    // or Long term bond and short term Bonds
    bool CoverFromOtherFund(Account *& account, int type, int asset); //type is a fund type which does not have enough fund
    //transferring fund to other account
    bool Transfer(string info);
    //displaying history of specified account
    void Display(string info);
    //displaying history of all account after all transaction is done
    void DisplayFinalBalance();
private:
    //queue to store transactions read from text file
    queue<string> q;
    //Binary Search Tree to store accounts and funds
    BSTree bst;
    //new account to insert BST
    Account* newAccount;

};
#endif //HW6_BANKING_BANK_H
