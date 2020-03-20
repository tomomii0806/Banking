/*
 * Tomomi Nakamura
 * Banking
 * file @ main.cpp
 */

#include <iostream>
#include <cassert>
#include "Bank.h"
#include "Account.h"
#include "BSTree.h"

//testing methods accont class
void TestAccount(){
    int clientId = 0001;
    string lastName = "Nakamura";
    string firstName = "Tomomi";
    Account* act = new Account(clientId, lastName, firstName);
    assert(act->GetClientId() == 0001);
    assert(act->GetLastName() == "Nakamura");
    assert(act->GetFirstName() == "Tomomi");
    assert(act->GetFundType(8) == "Value Fund");
    act->AddFund(0, 100);
    assert(act->GetFund(0) == 100);
    assert(act->GetFund(8) == 0);
    act->RemoveFund(0, 60);
    assert(act->GetFund(0) == 40);
    delete act;
    act = NULL;
}

//testing methods from BST
void TestBST(){
    BSTree bst;
    assert(bst.isEmpty());
    Account* act;
    Account* act1 = new Account(0002, "Selena", "Gomez");
    Account* act2 = new Account(0003, "Obama", "Balack");
    Account* act3 = new Account(0010, "Bob", "Dillan");
    Account* act4 = new Account(0001, "John", "Snow");
    assert(bst.insert(act1));
    assert(bst.insert(act2));
    //Duplicate account
    assert(!bst.insert(act1));
    assert(bst.Retrive(0002, act));
    assert(act->GetClientId() == 0002);
    //account not found
    assert(!bst.Retrive(0004, act));
    bst.Display();
    //empty BST
    bst.Empty();
    assert(!bst.Retrive(0002, act));
    assert(!bst.Retrive(0003, act));

    //delete act1;
    //delete act2;
    //act1 = NULL;
    //act2 = NULL;
}

//testing methods from bank class
void TestBank(){
    Bank b;
    assert(b.OpenAccount("O Cash Johnny 1000"));
    assert(b.OpenAccount("O Katy White 1001"));
    assert(b.OpenAccount("O Stacy Edlin 0999"));
    assert(b.OpenAccount("O Ted John 1101"));
    assert(b.OpenAccount("O John Snow 0501"));
    //duplicate account
    assert(!b.OpenAccount("O Bob Johnny 1000"));

    assert(b.Deposit("D 10000 5000"));
    //account not found
    assert(!b.Deposit("D 10020 5000"));

    assert(b.Withdraw("W 10000 1000"));
    //Not enough fund
    assert(!b.Withdraw("W 10002 1000"));
    //No account found
    assert(!b.Withdraw("W 10102 1000"));


    assert(b.Transfer("T 10000 100 10013"));
    //Not enough fund
    assert(!b.Transfer("T 09990 100 10014"));
    //No account found
    assert(!b.Transfer("T 12000 100 14013"));

    //fund transferred from prime money market
    assert(b.Withdraw("W 10001 1000"));
    assert(b.Deposit("D 10002 100"));
    //fund transferred from long-term to short-term bond
    assert(b.Transfer("T 10003 100 11012"));
    //no enough fund in Bond
    assert(!b.Transfer("T 11013 150 10002"));

}

void TestAll(){
    cout << "*********************  Testing  *********************" << endl;
    TestAccount();
    TestBST();
    TestBank();
    cout << "***************  Passed All Test... *****************" << endl;
    cout << endl;
}

int main() {
    TestAll();
    //doing transaction from text file
    Bank("BankTransIn.txt");
    return 0;
}