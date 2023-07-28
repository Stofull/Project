#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
void getClick(int& x, int& y)
{
	HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRec;
	DWORD events;
	COORD coord;
	bool clicked = false;
	DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hConsoleIn, fdwMode);
	while (!clicked) {
		ReadConsoleInput(hConsoleIn, &inputRec, 1, &events);

		if (inputRec.EventType == MOUSE_EVENT) {
			if (inputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				coord = inputRec.Event.MouseEvent.dwMousePosition;
				x = coord.X;
				y = coord.Y;
				clicked = true;
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			cout << "Exiting" << endl;
			break;
		}
	}
}
int keyFinding(int& x)
{
	HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRec;
	DWORD events;
	do
	{
		ReadConsoleInput(hConsoleIn, &inputRec, 1, &events);
	} while (inputRec.Event.KeyEvent.bKeyDown == false);
	x = inputRec.Event.KeyEvent.wVirtualKeyCode;
	return 0;
}

void txtReader(int x) {
	ifstream inputFile("example.txt");
	if (!inputFile.is_open()) {
		cout << "Error opening " << "example.txt" << endl;
		return;
	}
	string line{};
	while (getline(inputFile,line)){
		cout << line << endl;
	}
	inputFile.close();
}


class cardDebit 
{
private:
	string name{};
	int cardNum;
	int expiredDate;
	int balance;
public:
	cardDebit(const string& name,int cardNum, int expiredDate, int balance) :
		cardNum(cardNum), expiredDate(expiredDate), balance(balance),name(name) {};

	friend ostream& operator<<(ostream& out, const cardDebit& visaDebit)
	{
		out << "Bank name: " << visaDebit.name << endl;
		out << "Balance: " << visaDebit.balance << endl;
		return out;
	}
	void writeToFile(const string& filename)
	{
		ofstream outputFile(filename);
		if (outputFile.is_open())
		{
			outputFile << "Bank name: " << name << endl;
			outputFile << "Card Number: " << cardNum << endl;
			outputFile << "Expiration Date: " << expiredDate << endl;
			outputFile << "Balance: " << balance << endl;
			outputFile.close();
			cout << "Information has been written to the file." << endl;
		}
	}
};
class cardCredit
{
private:
	string name{};
	int cardNum;
	int expiredDate;
	int balance;
public:
	cardCredit(const string& name, int cardNum, int expiredDate, int balance) :
		cardNum(cardNum), expiredDate(expiredDate), balance(balance), name(name) {};

	friend ostream& operator<<(ostream& out, const cardCredit& cardCredit)
	{
		out << "Bank name: " << cardCredit.name << endl;
		out << "Balance: " << cardCredit.balance << endl;
		return out;
	}
	void writeToFile(const string& filename)
	{
		ofstream outputFile(filename);
		if (outputFile.is_open())
		{
			outputFile << "Bank name: " << name << endl;
			outputFile << "Card Number: " << cardNum << endl;
			outputFile << "Expiration Date: " << expiredDate << endl;
			outputFile << "Balance: " << balance << endl;
			outputFile.close();
			cout << "Information has been written to the file." << endl;
		}
	}
};
class MCDebit
{
private:
	int cardNum;
	int expiredDate;
	int balance;
public:
	MCDebit(int cardNum, int expiredDate, int balance) :
		cardNum(cardNum), expiredDate(expiredDate), balance(balance) {};


};
class MCKredit
{
private:
	int cardNum;
	int expiredDate;
	int balance = 2000;
public:
	MCKredit(int cardNum, int expiredDate, int balance) :
		cardNum(cardNum), expiredDate(expiredDate), balance(balance) {};

};
int main()
{
	remove("visaDebit.txt");
	remove("visaCredit.txt");
	remove("MasterCardDebit.txt");
	remove("MasterCardCredit.txt");
	//int turn{};
	//cout << "select: " << endl;
	//txtReader(turn);
	//cout << "Click on the console window or press Esc to exit." << endl;
	//getClick(x, y, inputTxt);
	//cout << inputTxt;

	int x = 0;
	int y = 0;
	int money = 0;

	while(true)
	{
		cout
			<< "Select your bank" << endl
			<< "1.Visa\t\tDebit\tCredit" << endl
			<< "2.MasterCard\tDebit\tCredit" << endl
			<< "Press ESC for exiting" << endl;
		getClick(x, y);
		cout << "Clicked at coordinates: (" << x << ", " << y << ")" << endl;

		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		if (y == 1 && 16 <= x && x <= 20)
		{
			keyFinding(money);
			system("cls");
			cout << "Enter balance: ";
			cin >> money;
			cardDebit visaDeb("Visa", 123123, 2211, money);
			cout << visaDeb;
			visaDeb.writeToFile("visaDebit.txt");
		}
		else if (y == 1 && 24 <= x && x <= 29)
		{
			system("cls");
			money += 2000;
			cardCredit visaCredit("Visa", 123123, 2211,money);
			cout << visaCredit;
			visaCredit.writeToFile("visaCredit.txt");

		}
		else if (y == 2 && 16 <= x && x <= 20)
		{
			keyFinding(money);
			system("cls");
			cout << "Enter balance: ";
			cin >> money;
			cardDebit MCDed("MasterCard", 123123, 2211, money);
			cout << MCDed;
			MCDed.writeToFile("MasterCardDebit.txt");
		}
		else if (y == 2 && 24 <= x && x <= 29)
		{
			system("cls");
			money += 2000;
			cardCredit MDCredit("MasterCard", 123123, 2211, money);
			cout << MDCredit;
			MDCredit.writeToFile("MasterCardCredit.txt");
		}
		money = 0;
	}

	// Дописать рандомную запись номеров карт так же и конец даты и перевести её в строку из-за слэша
	// Из ТХТ файла переписать категории и таблицу с месяцами
	// Продумать систему недель и месяца 
	// Переписать весь код в два СРР и один .H файл

	return 0;
}