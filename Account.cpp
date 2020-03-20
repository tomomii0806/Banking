/*
 * Tomomi Nakamura
 * Banking
 * file @ Account.cpp
 */

#include "Account.h"
#include "Bank.h"
#include <iostream>
using namespace std;

//default constructor
Account::~Account() {
}

//constructor
Account::Account(int clientId, string lastName, string firstName)
: clientId{clientId}, lastName{lastName}, firstName{firstName}
{

}

//getter for client ID
int Account::GetClientId() const {
    return clientId;
}
//getter for last name
string Account::GetLastName() const {
    return lastName;
}
//getter for first name
string Account::GetFirstName() const {
    return firstName;
}
//getter for fund
int Account::GetFund(int type) const {
    return fund[type];
}
//adding fund to the fund type
void Account::AddFund(int type, int asset) {
    fund[type] += asset;
}
//removing fund from the fund type
void Account::RemoveFund(int type, int asset) {
    fund[type] -= asset;
}
//adding history to a vector which stores all transaction histories
void Account::AddHistory(string info, int type) {
    history[type].push_back(info);
}
//displaying transaction history of the fund type
void Account::DisplayHistory(int type) {
    for (int i = 0; i < history[type].size(); i++)
    {
        cout << history[type].at(i) << endl;
    }
    cout << endl;
}
//Displaying all transaction history of the account
void Account::DisplayAllHistory() {
    for (int j = 0; j < 10; j++)
    {
        cout << fundNames[j] << ": $" << fund[j] << endl;
        for (int i = 0; i < history[j].size(); i++)
        {
            cout << history[j].at(i) << endl;
        }
    }
    cout << endl;
}
//getter for fund type
string Account::GetFundType(int type) const{
    return fundNames[type];
}

//overloading operator << to print out all funds of the account
ostream &operator<<(ostream &out, const Account &act) {
    out << act.GetFirstName() + " " + act.GetLastName() + " Account ID: "
        + to_string(act.GetClientId()) << endl;
    for (int i = 0; i < 10; i++)
    {
        out << act.GetFundType(i) + ": $" + to_string(act.GetFund(i)) << endl;
    }
    out << endl;

    return out;
}