#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// Transaction class to store transaction details
class Transaction {
public:
    string type;       // "Income" or "Expense"
    string category;   // Category of the transaction
    double amount;     // Amount of the transaction

    Transaction(string t, string c, double a) : type(t), category(c), amount(a) {}
};

// PersonalFinanceTracker class to manage transactions and reporting
class PersonalFinanceTracker {
private:
    vector<Transaction> transactions;

public:
    // Add a transaction
    void addTransaction(const string& type, const string& category, double amount) {
        transactions.push_back(Transaction(type, category, amount));
    }

    // Save transactions to file
    void saveTransactions() {
        ofstream file("transactions.txt");
        if (file.is_open()) {
            for (size_t i = 0; i < transactions.size(); ++i) {
                file << transactions[i].type << "," << transactions[i].category << "," << transactions[i].amount << "\n";
            }
            file.close();
            cout << "Transactions saved to file.\n";
        } else {
            cout << "Error saving transactions.\n";
        }
    }

    // Load transactions from file
    void loadTransactions() {
        ifstream file("transactions.txt");
        if (file.is_open()) {
            transactions.clear();  // Clear existing transactions
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(",");
                size_t pos2 = line.rfind(",");
                string type = line.substr(0, pos1);
                string category = line.substr(pos1 + 1, pos2 - pos1 - 1);
                std::string amountStr = line.substr(pos2 + 1);
				std::stringstream ss(amountStr);
				double amount;
				ss >> amount;
                transactions.push_back(Transaction(type, category, amount));
            }
            file.close();
            cout << "Transactions loaded from file.\n";
        } else {
            cout << "Error loading transactions.\n";
        }
    }

    // Display all transactions
    void displayTransactions() const {
        cout << fixed << setprecision(2);
        cout << "\n--- All Transactions ---\n";
        for (size_t i = 0; i < transactions.size(); ++i) {
            cout << "Type: " << transactions[i].type
                 << ", Category: " << transactions[i].category
                 << ", Amount: $" << transactions[i].amount << "\n";
        }
    }

    // Generate report of total income, expenses, and balance
    void generateReport() const {
        double totalIncome = 0.0, totalExpenses = 0.0;
        for (size_t i = 0; i < transactions.size(); ++i) {
            if (transactions[i].type == "Income") {
                totalIncome += transactions[i].amount;
            } else if (transactions[i].type == "Expense") {
                totalExpenses += transactions[i].amount;
            }
        }
        double balance = totalIncome - totalExpenses;
        
        cout << fixed << setprecision(2);
        cout << "\n--- Monthly Financial Report ---\n";
        cout << "Total Income: $" << totalIncome << "\n";
        cout << "Total Expenses: $" << totalExpenses << "\n";
        cout << "Balance: $" << balance << "\n";
    }
};

// Main function for the console application
int main() {
    PersonalFinanceTracker tracker;
    tracker.loadTransactions();  // Load existing transactions from file
    
    int choice;
    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Transaction\n";
        cout << "2. Display Transactions\n";
        cout << "3. Generate Monthly Report\n";
        cout << "4. Save Transactions\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string type, category;
            double amount;
            cout << "Enter type (Income/Expense): ";
            cin >> type;
            cout << "Enter category (e.g., Food, Rent): ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            tracker.addTransaction(type, category, amount);
        } else if (choice == 2) {
            tracker.displayTransactions();
        } else if (choice == 3) {
            tracker.generateReport();
        } else if (choice == 4) {
            tracker.saveTransactions();
        } else if (choice == 5) {
            cout << "Exiting application.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

