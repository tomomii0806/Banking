/*
 * Tomomi Nakamura
 * Banking
 * file @ Bank.cpp
 */

#include "Bank.h"
#include "Account.h"
#include "BSTree.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
//default constructor
Bank::Bank(string fileName) {
    ReadFile(fileName);
    DoTransactions();
    DisplayFinalBalance();
}
//destructor
Bank::~Bank() {
    delete newAccount;
    newAccount = NULL;
}
//reading input file passed by constructor
// and store each lines in queue
void Bank::ReadFile(string fileName) {
    ifstream readFile(fileName);
    string line;
    if (readFile.is_open())
    {
        while (getline(readFile, line))
        {
            //cout << line << endl;
            q.push(line);
        }

    } else {
        cout << "Error Opening a File" << endl;
    }
}

//doing each transaction based on lines stored in queue
void Bank::DoTransactions() {
    string str;
    while (!q.empty())
    {
        str = q.front();
        q.pop();

        switch (str.at(0))
        {
            case 'O':
                OpenAccount(str);
                break;
            case 'D':
                Deposit(str);
                break;
            case 'W':
                Withdraw(str);
                break;
            case 'T':
                Transfer(str);
                break;
            case 'H':
                Display(str);
                break;
        }
    }


}

//opening account
//get client id, lastname, and firstname
//then add them into BST
bool Bank::OpenAccount(string info) {
    string str;
    stringstream S(info);

    //create a new account
    int clientId;
    string lastName;
    string firstName;

    int i = 0;
    while (getline(S, str, ' '))
    {
        if (i == 1)
        {
            lastName = str;
        }
        else if (i == 2)
        {
            firstName = str;
        }
        else if (i == 3)
        {
            clientId = stoi(str);
        }
        i++;
    }
    //cout << clientId << endl;
    newAccount = new Account(clientId, lastName, firstName);


    return bst.insert(newAccount);

}

//depositing fund
//get clientId, asset, and fund type
//then find account from BST using clientID
//add the asset to the account
bool Bank::Deposit(string info) {
    string str;
    stringstream S(info);

    int clientId;
    int asset;
    int type;
    int i = 0;
    while (getline(S, str, ' '))
    {
        if (i == 1)
        {
            type = str.at(4) - '0';
            clientId = stoi(str);
            clientId /= 10;
        }
        else if (i == 2)
        {
            asset = stoi(str);
        }
        i++;
    }
    //cout << clientId << ", " << type << ", " << asset << endl;

    Account* account;
    bool findId = bst.Retrive(clientId, account);
    if (findId)
    {
        account->AddFund(type, asset);
        account->AddHistory(info, type); //adding this transaction to history vector
        //cout << account->getClientId() << ", " << account->getFund(type) << endl;
        return true;
    }
    else
    {
        return false;
    }

}

//withdrawing fund
//get clientId, asset, and fund type
//then find account from BST using clientID
//remove the asset from the account
bool Bank::Withdraw(string info) {
    string str;
    stringstream S(info);

    int clientId;
    int asset;
    int type;
    int i = 0;
    while (getline(S, str, ' '))
    {
        if (i == 1)
        {
            type = str.at(4) - '0';
            clientId = stoi(str);
            clientId /= 10;
        }
        else if (i == 2)
        {
            asset = stoi(str);
        }
        i++;
    }

    Account* account;
    bool findId = bst.Retrive(clientId, account);
    if (findId)
    {
        if (account->GetFund(type) >= asset)
        {
            account->RemoveFund(type, asset);
            account->AddHistory(info, type); //adding this transaction to history vector
            return true;
        }
        else if ((type == 0 || type == 1 || type == 2 || type == 3) && CoverFromOtherFund(account, type, asset))
        {
            account->RemoveFund(type, asset);
            account->AddHistory(info, type); //adding this transaction to history vector
            return true;
        }
        else {
            cout << "ERROR: Not enough funds to withdraw $" << asset << " from " << account->GetFirstName()
            << " " << account->GetLastName() << " " << account->GetFundType(type) << endl;
            cout << endl;
            string failInfo = "D " + to_string(account->GetClientId()) + to_string(type) + " " + to_string(asset)+ " (failed)";
            account->AddHistory(failInfo, type); //adding this transaction to history vector
            return false;
        }

    }
    else
    {
        string failInfo = "D " + to_string(account->GetClientId()) + to_string(type) + " " + to_string(asset)+ " (failed)";
        account->AddHistory(failInfo, type); //adding this transaction to history vector
        return false;
    }
}

//transferring fund between Money Market and Primary Money Market
// or Long term bond and short term Bonds
bool Bank::CoverFromOtherFund(Account *&account, int type, int asset) {
    string transHistory;
    int totalFund;
    int fundToCollect = asset - account->GetFund(type);
    if (type == 0 || type == 2)
    {
        if (fundToCollect <= account->GetFund(type + 1))
        {
            account->RemoveFund(type + 1, fundToCollect);
            account->AddFund(type, fundToCollect);
            transHistory = "T " + to_string(account->GetClientId()) + to_string(type + 1) + " "
                           + to_string(fundToCollect) + " " + to_string(account->GetClientId()) + to_string(type);
            account->AddHistory(transHistory, type + 1);
            account->AddHistory(transHistory, type);
            return true;
        }
        else {
            return false;
        }
    }
    else if (type == 1 || type == 3)
    {
        if (fundToCollect <= account->GetFund(type - 1))
        {
            account->RemoveFund(type - 1, fundToCollect);
            account->AddFund(type, fundToCollect);
            transHistory = "T " + to_string(account->GetClientId()) + to_string(type - 1) + " "
                           + to_string(fundToCollect) + " " + to_string(account->GetClientId()) + to_string(type);
            account->AddHistory(transHistory, type - 1);
            account->AddHistory(transHistory, type);
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

//transferring funds
//get clientId of two accounts and find them from BST
//then transfer fund
bool Bank::Transfer(string info) {
    string str;
    stringstream S(info);

    int clientIdFrom;
    int clientIdTo;
    int asset;
    int typeFrom;
    int typeTo;
    int i = 0;
    while (getline(S, str, ' '))
    {
        if (i == 1)
        {
            typeFrom = str.at(4) - '0';
            clientIdFrom = stoi(str);
            clientIdFrom /= 10;
        }
        else if (i == 2)
        {
            asset = stoi(str);
        }
        else if (i == 3)
        {
            typeTo = str.at(4) - '0';
            clientIdTo = stoi(str);
            clientIdTo /= 10;
        }

        i++;
    }

    Account* accFrom;
    Account* accTo;
    bool findIdFrom = bst.Retrive(clientIdFrom, accFrom);
    bool findIdTo = bst.Retrive(clientIdTo, accTo);
    if (findIdFrom && findIdTo)
    {
        if (accFrom->GetFund(typeFrom) >= asset)
        {
            accFrom->RemoveFund(typeFrom, asset);
            accTo->AddFund(typeTo, asset);
            accFrom->AddHistory(info, typeFrom); //adding this transaction to history vector
            accTo->AddHistory(info, typeTo);
            return true;
        }
        else if (CoverFromOtherFund(accFrom, typeFrom, asset)) //if type is Money Market or Bond
        {
            accFrom->RemoveFund(typeFrom, asset);
            accTo->AddFund(typeTo, asset);
            accFrom->AddHistory(info, typeFrom); //adding this transaction to history vector
            accTo->AddHistory(info, typeTo);
            return true;
        }
        else {
            cout << "ERROR: Not enough funds to transfer $" << asset << " from " << accFrom->GetFirstName()
                 << " " << accFrom->GetLastName() << " " << accFrom->GetFundType(typeFrom) << endl;
            cout << endl;
            string failInfo = "T " + to_string(accFrom->GetClientId()) + to_string(typeFrom)
                    + " " + to_string(asset)+ to_string(accTo->GetClientId()) + to_string(typeTo) +" (failed)";

            accFrom->AddHistory(failInfo, typeFrom); //adding this transaction to history vector
            accTo->AddHistory(failInfo, typeTo);
            return false;
        }

    }
    else
    {
        return false;
    }
}

//displaying history of specified account
void Bank::Display(string info) {
    string str;
    stringstream S(info);

    int clientId;
    int type;
    int i = 0;
    while (getline(S, str, ' '))
    {
        if (i == 1)
        {
            if (str.at(4) == '0' || str.at(4) == '1' || str.at(4) == '2' || str.at(4) == '3'
            || str.at(4) == '4' || str.at(4) == '5' || str.at(4) == '6' || str.at(4) == '7' ||
            str.at(4) == '8' || str.at(4) == '9')
            {
                type = str.at(4) - '0';
                clientId = stoi(str);
                clientId /= 10;
            } else  {
                clientId = stoi(str);
                type = -1;
            }
        }
        i++;
    }

    Account* account;
    bool findId = bst.Retrive(clientId, account);
    if (findId)
    {
        if (type != -1)
        {
            cout << "Transaction History for " << account->GetFirstName() << " " << account->GetLastName()
            << " " << account->GetFundType(type) << ": $" << account->GetFund(type) << endl;
            account->DisplayHistory(type);
        }
        else
        {
            // print all
            cout << "Transaction History for " << account->GetFirstName() << " " << account->GetLastName()
                 << " by fund."  << endl;
            account->DisplayAllHistory();
        }
    }

}

//default constructor
Bank::Bank() {

}

//displaying history of all account after all transaction is done
void Bank::DisplayFinalBalance() {
    vector<Account> allAct = bst.GetAllAccount();

    cout << "Processing Done. Final Balances" << endl;
    for (int i = 0; i < allAct.size(); i++)
    {
        Account act = allAct.at(i);
        cout << act;
    }
}





