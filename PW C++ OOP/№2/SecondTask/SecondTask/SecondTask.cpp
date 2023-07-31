#include "Header.h"

int main() {
    ExpenseTracker tracker;
    Card* visaDebit = new DebitCard("Visa Debit", 4096584412364541, "08/28", 1000);
    Card* visaCredit = new CreditCard("Visa Credit", 4096584448681284, "08/28", 2000);
    Card* masterCardDebit = new DebitCard("MasterCard Debit", 5096584412364875, "08/28", 500);
    Card* masterCardCredit = new CreditCard("MasterCard Credit", 5096584412475524, "08/28", 3000);
    int money = 0;
    int categoryIndex = 0;
    int cardIndex = 0;
    int option = 0;
    int choice = 0;
    string date;
    while (true) {
        system("cls");
        cout << "Choose: " << endl
            << "1. Create card" << endl
            << "2. Make a transaction" << endl
            << "3. Show reports" << endl
            << "4. Show top expenses" << endl
            << "5. Enter to exit" << endl;

        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            cout << "Select card type: " << endl
                << "1. Visa Debit" << endl
                << "2. Visa Credit" << endl
                << "3. MasterCard Debit" << endl
                << "4. MasterCard Credit" << endl;
            cin >> option;
            switch (option) {
            case 1:
                tracker.addCard(visaDebit);
                break;
            case 2:
                tracker.addCard(visaCredit);
                break;
            case 3:
                tracker.addCard(masterCardDebit);
                break;
            case 4:
                tracker.addCard(masterCardCredit);
                break;
            default:
                cout << "Invalid option" << endl;
                break;
            }
            break;
        case 2:
            system("cls");
            cout << "Select your card: " << endl;
            tracker.showCards();
            cin >> cardIndex;
            cardIndex--;
            if (cardIndex >= 0 && cardIndex < tracker.cards.size()) {
                Card* selectedCard = tracker.cards[cardIndex];
                selectedCard->showOptions();
                cin >> option;
                switch (option) {
                case 1:
                    cout << "How much do you want to replenish?" << endl;
                    cin >> money;
                    selectedCard->balanceReplenishment(money);
                    break;
                case 2:
                    cout << "Select the category of expense: " << endl;
                    tracker.showCategories();
                    cin >> categoryIndex;
                    categoryIndex--;
                    if (categoryIndex >= 0 && categoryIndex < tracker.categories.size()) {
                        cout << "Enter the amount of payment: " << endl;
                        cin >> money;
                        cout << "Enter the date of the transaction (YYYY-MM-DD): " << endl;
                        cin.ignore();
                        getline(cin, date);
                        selectedCard->addExpense(tracker.categories[categoryIndex], money, date);
                    }
                    else {
                        cout << "Invalid category selection" << endl;
                    }
                    break;
                default:
                    cout << "Invalid option" << endl;
                    break;
                }
            }
            else {
                cout << "Invalid card selection" << endl;
            }
            break;
        case 3:
            system("cls");
            cout << "Enter the date for the report (YYYY-MM-DD): " << endl;
            cin.ignore();
            getline(cin, date);
            tracker.showReport(date);
            break;
        case 4:
            system("cls");
            cout << "Enter the number of top expenses to show: " << endl;
            cin >> option;
            tracker.showTopExpenses(option);
            break;
        case 5:
            return false;
        }
        system("pause");
    }
    return 0;
}
