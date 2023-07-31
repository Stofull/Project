#ifndef HEADER
#define HEADER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;
class Expense {
private:
    string date;
    string category;
    int amount;
public:
    Expense(const  string& date, const  string& category, int amount);
    string getDate() const;
    string getCategory() const;
    int getAmount() const;
};

class Card {
protected:
    string name;
    uint64_t cardNum;
    string expiredDate;
    int balance;
    vector<Expense> expenses;
public:
    Card(const  string& name, uint64_t cardNum, const  string& expiredDate, int balance);
    virtual ~Card();
    string getName() const;
    int getBalance() const;
    vector<Expense> getExpenses() const;
    void balanceReplenishment(int replenishment);
    virtual void addExpense(const  string& category, int amount, const  string& date);
    virtual void showOptions() const;
    virtual  string getType() const = 0;
    void writeToFile(const  string& filename) const;
};

class DebitCard : public Card {
public:
    using Card::Card;
    void addExpense(const  string& category, int amount, const  string& date) override;
    string getType() const override;
};

class CreditCard : public Card {
public:
    using Card::Card;
    void addExpense(const  string& category, int amount, const  string& date) override;
    string getType() const override;
};

class ExpenseTracker {
public:
    vector<Card*> cards;
    vector< string> categories;
    ExpenseTracker();
    ~ExpenseTracker();
    void addCard(Card* card);
    void showCards() const;
    void showCategories() const;
    void showReport(const  string& date) const;
    void showTopExpenses(int count) const;
};

#endif 
