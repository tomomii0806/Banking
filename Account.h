/*
 * Tomomi Nakamura
 * Banking
 * file @ Account.h
 */
//This is a header file for Account class
#include <iostream>
#include <vector>
using namespace std;

#ifndef HW6_BANKING_ACCOUNT_H
#define HW6_BANKING_ACCOUNT_H

class Account {
public:
    //constructor
    Account(int clientId, string lastName, string firstName);
    //destructor
    ~Account();
    //overloading operator << to print out all funds of the account
    friend ostream &operator<<(ostream &out, const Account &act);

    //getter for client ID
    int GetClientId() const;
    //getter for last name
    string GetLastName() const;
    //getter for first name
    string GetFirstName() const;
    //getter for fund type
    string GetFundType(int type) const;
    //getter for fund
    int GetFund(int type) const;
    //adding fund to the fund type
    void AddFund(int type, int asset);
    //removing fund from the fund type
    void RemoveFund(int type, int asset);
    //adding history to a vector which stores all transaction histories
    void AddHistory(string info, int type);
    //displaying transaction history of the fund type
    void DisplayHistory(int type);
    //Displaying all transaction history of the account
    void DisplayAllHistory();

private:
    int clientId;
    string lastName;
    string firstName;

    //map fund types
    string fundNames[10] = {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
                            "500 Index Bond", "Capital Value Fund", "Growth Equality Fund", "Growth Index Fund",
                            "Value Fund", "Value Stock Index"};
    //store all 10 funds
    int fund[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //storing histories of Deposit and Withdraw for each fund types
    vector<string> history[10];
};


#endif //HW6_BANKING_ACCOUNT_H
