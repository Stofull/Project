#include "Header.h"
using namespace std;
Expense::Expense(const  string& date, const  string& category, int amount)
    : date(date), category(category), amount(amount) {}

string Expense::getDate() const {
    return date;
}

string Expense::getCategory() const {
    return category;
}

int Expense::getAmount() const {
    return amount;
}

Card::Card(const  string& name, uint64_t cardNum, const  string& expiredDate, int balance)
    : name(name), cardNum(cardNum), expiredDate(expiredDate), balance(balance) {}

Card::~Card() {}

string Card::getName() const {
    return name;
}

int Card::getBalance() const {
    return balance;
}

vector<Expense> Card::getExpenses() const {
    return expenses;
}

void Card::balanceReplenishment(int replenishment) {
    balance += replenishment;
}

void Card::addExpense(const  string& category, int amount, const  string& date) {
    if (balance >= amount) {
        balance -= amount;
        expenses.push_back(Expense(date, category, amount));
    }
    else {
        throw  runtime_error("Insufficient funds!");
    }
}

void Card::showOptions() const {
    cout << "Options for card: " << name << endl;
    cout << "1. Replenish balance" << endl;
    cout << "2. Make a payment" << endl;
}

void Card::writeToFile(const  string& filename) const {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << "Bank name: " << name << endl;
        outputFile << "Card Number: " << cardNum << endl;
        outputFile << "Expiration Date: " << expiredDate << endl;
        outputFile << "Balance: " << balance << endl;
        outputFile << "Transactions: " << endl;
        for (const auto& expense : expenses) {
            outputFile << "Date: " << expense.getDate() << ", Category: " << expense.getCategory() << ", Amount: " << expense.getAmount() << endl;
        }
        outputFile.close();
        cout << "Information has been written to the file." << endl;
    }
    else {
        cout << "Error opening " << filename << endl;
    }
}

void DebitCard::addExpense(const  string& category, int amount, const  string& date) {
    static const  regex dateRegex(R"(^\d{4}[.-]\d{2}[.-]\d{2}$)");

    if (!regex_match(date, dateRegex)) {
        throw  runtime_error("Invalid date format. Use YYYY-MM-DD.");
    }
    if (balance >= amount) {
        balance -= amount;
        expenses.push_back(Expense(date, category, amount));
    }
    else {
        throw  invalid_argument("Insufficient funds!");
    }
}

string DebitCard::getType() const {
    return "Debit";
}

void CreditCard::addExpense(const  string& category, int amount, const  string& date) {
    static const  regex dateRegex(R"(^\d{4}-\d{2}-\d{2}$)");

    if (!regex_match(date, dateRegex)) {
        throw  runtime_error("Invalid date format. Use YYYY-MM-DD.");
    }
    if (balance >= amount) {
        balance -= amount;
        expenses.push_back(Expense(date, category, amount));
    }
    else {
        throw  invalid_argument("Insufficient funds!");
    }
}

string CreditCard::getType() const {
    return "Credit";
}

ExpenseTracker::ExpenseTracker() {
    categories = { "Food", "Grocery", "Medicine", "Shopping", "Others" };
}

ExpenseTracker::~ExpenseTracker() {
    for (auto card : cards) {
        card->writeToFile(card->getType() + "_" + card->getName() + ".txt");
        delete card;
    }
}

void ExpenseTracker::addCard(Card* card) {
    cards.push_back(card);
}

void ExpenseTracker::showCards() const {
    int i = 1;
    for (const auto& card : cards) {
        cout << i++ << ". " << card->getName() << endl;
    }
}

void ExpenseTracker::showCategories() const {
    int i = 1;
    for (const auto& category : categories) {
        cout << i++ << "." << category << endl;
    }
}

void ExpenseTracker::showReport(const  string& date) const {
    cout << "Report for date: " << date << endl;
    cout << "----------------------------------------" << endl;

    for (const auto& card : cards) {
        cout << "Card: " << card->getName() << " Balance: " << card->getBalance() << endl;
        cout << "Expenses: " << endl;

        for (const auto& expense : card->getExpenses()) {
            if (expense.getDate() == date) {
                cout << "Category: " << expense.getCategory() << " Amount: " << expense.getAmount() << endl;
            }
        }
        cout << "----------------------------------------" << endl;
    }
}

void ExpenseTracker::showTopExpenses(int count) const {
    vector< pair< string, int>> topExpenses;

    for (const auto& card : cards) {
        for (const auto& expense : card->getExpenses()) {
            bool categoryFound = false;

            for (auto& topExpense : topExpenses) {
                if (topExpense.first == expense.getCategory()) {
                    topExpense.second += expense.getAmount();
                    categoryFound = true;
                    break;
                }
            }

            if (!categoryFound) {
                topExpenses.push_back({ expense.getCategory(), expense.getAmount() });
            }
        }
    }

    sort(topExpenses.begin(), topExpenses.end(), [](const auto& a, const auto& b)
        {return a.second > b.second; });

    cout << "Top Expenses: " << endl;
    int i = 1;
    for (const auto& expense : topExpenses) {
        cout << i++ << ". Category: " << expense.first << ", Total Amount: " << expense.second << endl;
        if (i > count) {
            break;
        }
    }
}
