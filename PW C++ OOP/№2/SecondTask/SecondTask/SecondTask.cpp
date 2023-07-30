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
void txtReader(string txt) {
	ifstream inputFile(txt);
	if (!inputFile.is_open()) {
		cout << "Error opening " << txt << endl;
		return;
	}
	string line{};
	while (getline(inputFile,line)){
		cout << line << endl;
	}
	inputFile.close();
}
bool clicked(int& x, int& y)
{
	cout << "Click to continue" << endl;
	getClick(x, y);
	if (x != 0 || y != 0)return true;
	return false;
}
class cardDebit 
{
private:
	string name{};
	uint64_t cardNum;
	string expiredDate{};
	float balance;
public:
	cardDebit(const string& name, uint64_t cardNum, const string& expiredDate, float balance) :
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
	void balanceReplenishment(int replenisment) {
		balance += replenisment;
	}
	void balanceWithdraw(int withdraw) {
		balance += withdraw;
	}
};
class cardCredit
{
private:
	string name{};
	uint64_t cardNum;
	string expiredDate{};
	float balance;
public:
	cardCredit(const string& name, uint64_t cardNum, const string& expiredDate, float balance) :
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
	void balanceReplenishment(float replenisment) {
		balance += replenisment;
	}
	void balanceWithdraw(float withdraw) {
		balance += withdraw;
	}
};
int main()
{

	cardDebit visaDebit("None", NULL, "None", NULL);
	cardDebit visaCredit("None", NULL, "None", NULL);
	cardDebit MCDebit("None", NULL, "None", NULL);
	cardDebit MCCredit("None", NULL, "None", NULL);
	remove("visaDebit.txt");
	remove("visaCredit.txt");
	remove("MasterCardDebit.txt");
	remove("MasterCardCredit.txt");
	//cout << "select: " << endl;
	//int turn{};
	//txtReader(turn);
	//cout << "Click on the console window or press Esc to exit." << endl;
	//getClick(x, y, inputTxt);
	//cout << inputTxt;
	//keyFinding(money);
	int x = 0;
	int y = 0;
	int money = 0;
	while (true)
	{
		system("cls");
		cout << "Choose: " << endl
			<< "1.Add new card" << endl
			<< "2.Make a transaction" << endl
			<< "3.Check all cards" << endl
			<< "Press ESC for exiting" << endl;
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		getClick(x, y);
		//cout << "Clicked at coordinates: (" << x << ", " << y << ")" << endl;
		switch (y)
		{
		case 1:
			system("cls");
			cout
				<< "Select your bank" << endl
				<< "1.Visa\t\tDebit\tCredit" << endl
				<< "2.MasterCard\tDebit\tCredit" << endl;
			getClick(x, y);
			if (y == 1 && 16 <= x && x <= 20)
			{
				ifstream inputFile("visaDebit.txt");
				if (inputFile.is_open())
					break;
				cardDebit visaDebit("Visa Debit", 4096584412364541, "08/28", 0);
				cout << "Debut visa card added to your wallet" << endl;
				visaDebit.writeToFile("visaDebit.txt");
			}
			else if (y == 1 && 24 <= x && x <= 29)
			{
				ifstream inputFile("visaCredit.txt");
				if (inputFile.is_open())
					break;
				cardCredit visaCredit("Visa Credit", 4096584448681284, "08/28",2000);
				cout << "Kredit visa card added to your wallet" << endl;
				visaCredit.writeToFile("visaCredit.txt");
			}
			else if (y == 2 && 16 <= x && x <= 20)
			{
				ifstream inputFile("MasterCardDebit.txt");
				if (inputFile.is_open())
					break;
				cout << "Debut MasterCard added to your wallet" << endl;
				cardDebit MCDebit("MasterCard Debit", 5096584412364875, "08/28", 0);
				MCDebit.writeToFile("MasterCardDebit.txt");
			}
			else if (y == 2 && 24 <= x && x <= 29)
			{
				ifstream inputFile("MasterCardCredit.txt");
				if (inputFile.is_open())
					break;
				cardCredit MDCredit("MasterCard Credit", 5096584412475524, "08/28", 2000);
				cout << "Kredit MasterCard added to your wallet" << endl;
				MDCredit.writeToFile("MasterCardCredit.txt");
			}
			if (clicked(x, y)) break;
			break;
		case 2:
			system("cls");
			cout <<"Select your card" << endl
				<< "Visa debit" << endl
				<< "Visa credit" << endl
				<< "MasterCard debit" << endl
				<< "MasterCard credit" << endl;
			getClick(x, y);
			if (y == 1) {
				keyFinding(money);
				cout << "How much do you want to upload?" << endl;
				cin >> money;
				visaDebit.balanceReplenishment(money);
				visaDebit.writeToFile("visaDebit.txt");
			}
			else if (y == 2)
			{
				cout << "How much do you want to upload?" << endl;
				cin >> money;
				keyFinding(money);
				visaCredit.balanceReplenishment(money);
				visaCredit.writeToFile("visaCredit.txt");
			}
			else if (y == 3) {
				cout << "How much do you want to upload?" << endl;
				cin >> money;
				keyFinding(money);
				MCDebit.balanceReplenishment(money);
				MCDebit.writeToFile("MasterCardDebit.txt");

			}
			else if (y == 4) {
				cout << "How much do you want to upload?" << endl;
				cin >> money;
				keyFinding(money);
				MCCredit.balanceReplenishment(money);
				MCCredit.writeToFile("MasterCardCredit.txt");
			}
			if (clicked(x, y)) break;
			break;
		case 3:
			while (true)
			{
				system("cls");
				txtReader("visaDebit.txt");
				txtReader("visaCredit.txt");
				txtReader("MasterCardDebit.txt");
				txtReader("MasterCardCredit.txt");
				if (clicked(x, y)) break;
			}
			break;
		default:
			cout << "Use Options" << endl;
			break;

		}
	}
	// Из ТХТ файла переписать категории и таблицу с месяцами
	// Продумать систему недель и месяца 
	// Переписать весь код в два СРР и один .H файл

	return 0;
}