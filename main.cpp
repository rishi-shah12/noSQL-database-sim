#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>



//Creating the bank account class
class bankAccount {
  public:
    long accountNumber;
    std::string accountName;
    std::string accountOwner;
    double accountValue;
};

//Write the number of accounts to the reference file
void write_num_accounts(int accounts) {
    std::ofstream amountFile;
    amountFile.open ("amount.txt", std::ofstream::out | std::ofstream::trunc);
    amountFile << accounts;
    amountFile.close();
};

//Read the number of accounts from the reference file
int read_num_accounts() {
    std::string accounts;
    std::ifstream amountFile;

    amountFile.open("amount.txt");
    std::getline(amountFile, accounts);
    amountFile.close();

    return std::stoi(accounts);
};

//Write accounts to the database file
void write_accounts(int amount, bankAccount names) {
    std::ofstream accountsFile;

    accountsFile.open("accounts.txt", std::ios::app);

    accountsFile << names.accountNumber << "\t" << names.accountName << "\t" << names.accountOwner << "\t"
    << names.accountValue << std::endl;

    accountsFile.close();
}

//Read accounts from the database file
void read_accounts(int amount, bankAccount results[]) {
    bankAccount inputAccounts[amount];

    std::ifstream accountsFile;

    accountsFile.open("accounts.txt", std::ios::in);
    accountsFile.seekg(0);
    std::string str;
    std::vector<std::string> stringArray;


    while (std::getline(accountsFile, str)) {

        std::istringstream ss(str);
        std::string word;

        while (ss >> word) {stringArray.push_back(word);}
    }
    for (int x=0; x<amount; x++){
        results[x].accountNumber = std::stol(stringArray[(x*4)+0]);
        results[x].accountName = stringArray[(x*4)+1];
        results[x].accountOwner = stringArray[(x*4)+2];
        results[x].accountValue = std::stod(stringArray[(x*4)+3]);
    }
    accountsFile.close();
}

//Prepare the json for outputting
void outputString(int value, bankAccount results[]) {
    std::cout << "{" << std::endl;

    for (int w = 0; w<value; w++){
        std::cout << "\t" << "[" << std::endl;
        std::cout << "\t\t" << "\"accountNumber\": " << "\"" << results[w].accountNumber << "\"" << "," << std::endl;
        std::cout << "\t\t" << "\"accountName\": " << "\"" << results[w].accountName << "\"" << "," << std::endl;
        std::cout << "\t\t" << "\"accountOwner\": " << "\"" << results[w].accountOwner << "\"" << "," << std::endl;
        std::cout << "\t\t" << "\"accountValue\": " << results[w].accountValue << std::endl;
        if (w == value-1){
            std::cout << "\t" << "]" << std::endl;
        }
        else {
            std::cout << "\t" << "]," << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}

//Searching algorithm
void searching(int value, long search, bankAccount results[], bankAccount returned[]) {
    for (int z = 0; z<value; z++) {
        if (results[z].accountNumber == search) {
            returned[0] = results[z];
            break;
        }
    }
}

int main() {
    int menuChoice;

    std::cout << "Welcome to the bank account management NOSQL database program" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Please choose one of the following options:" << std::endl;
    std::cout << "\t" << "1. Display All Accounts" << std::endl;
    std::cout << "\t" << "2. Add an Account" << std::endl;
    std::cout << "\t" << "3. Search for an Account" << std::endl;
    std::cout << "\t" << "4. Exit" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Your Choice: ";
    std::cin >> menuChoice;


    if (menuChoice == 1) {
        int value = read_num_accounts();
        bankAccount accounts[value];
        read_accounts(value, accounts);
        outputString(value, accounts);
    }
    else if (menuChoice == 2) {
        std::string accountName;
        std::string accountOwner;

        int value = read_num_accounts();

        bankAccount add;

        std::cout << "Enter the account number" << std::endl;
        std::cin >> add.accountNumber;

        std::cout << "Enter the account Name" << std::endl;
        std::getline(std::cin >> std::ws, accountName);
        std::replace(accountName.begin(), accountName.end(), ' ', '_');
        add.accountName = accountName;

        std::cout << "Enter the account Owner" << std::endl;
        std::getline(std::cin >> std::ws, accountOwner);
        std::replace(accountOwner.begin(), accountOwner.end(), ' ', '_');
        add.accountOwner = accountOwner;

        std::cout << "Enter the account Value" << std::endl;
        std::cin >> add.accountValue;

        write_num_accounts(value+1);
        value = read_num_accounts();

        write_accounts(value, add);

        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "Account Added" << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
    }

    else if (menuChoice == 3) {
        int value = read_num_accounts();
        long search;
        bankAccount accounts[value];
        bankAccount result[1];
        read_accounts(value, accounts);

        std::cout << "Enter the account number to search" << std::endl;
        std::cin >> search;

        searching(value, search, accounts, result);

        outputString(1, result);
    }

    else if (menuChoice == 4) {
        exit(0);
    }

    return 0;
}
