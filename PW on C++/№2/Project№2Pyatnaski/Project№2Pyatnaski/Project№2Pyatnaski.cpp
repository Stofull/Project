#include <iostream>
#include <ctime>
#include <windows.h> 
using namespace std;
const int length = 4;
int square[length][length];
int keyFinding(int& x)
{
	HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRec;
	DWORD events;
	    do {
        ReadConsoleInput(hConsoleIn, &inputRec, 1, &events);
    } while (inputRec.Event.KeyEvent.bKeyDown == false);
	x = inputRec.Event.KeyEvent.wVirtualKeyCode;
	return 0;
}
void replacement(int& a, int& b) 
{
	int tmp = a;
	a = b;
	b = tmp;
}
void init() {
	int count = 1;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			square[i][j] = count;
			count++;
		}
	}
	square[length - 1][length - 1] = 0;
}
void mix() {
	srand(time(0));
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			int x1 = rand() % length;
			int y1 = rand() % length;
			int x2 = rand() % length;
			int y2 = rand() % length;
			replacement(square[x1][y1], square[x2][y2]);
		}
	}
}
void pin() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (square[i][j] == 0) {
				cout << "  ";
			}
			else {
				cout << square[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
bool win() {
	int count = 1;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (i == length - 1 && j == length - 1) {
				if (square[i][j] != 0) {
					return false;
				}
			}
			else {
				if (square[i][j] != count) {
					return false;
				}
				count++;
			}
		}
	}
	return true;
}
bool move(int x, int y) {
	int zero_x, zero_y;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (square[i][j] == 0) {
				zero_x = i;
				zero_y = j;
			}
		}
	}
	int new_zero_x = zero_x + x;
	int new_zero_y = zero_y + y;
	if (new_zero_x < 0 || new_zero_x >= length || new_zero_y < 0 || new_zero_y >= length) {
		return false;
	}
	replacement(square[zero_x][zero_y], square[new_zero_x][new_zero_y]);
	return true;
}

int main()
{
	int startTime = time(0);
	int index{};
	init();
	mix();
	while (true) 
	{
		pin();
		if (win()) 
		{
			int endTime = time(0);
			cout << "\tYou won!" << endl;
			cout << "\t" << endTime - startTime << "Seconds have been spent" << endl;
			cout << "\tNumber of steps = " << index << endl;
			break;
		}
		int x, y = 0;
		cout << "Use arrow keys to move and press Enter: " << endl;
		keyFinding(x);
		if (x >= 37 || x <= 40)
		{
			switch (x)
			{
			case 37:
				x = 0;
				y = -1;
				break;
			case 38:
				x = -1;
				y = 0;
				break;
			case 39:				// СПРОСИТЬ ПРО time_t ВМЕСТО INT ТАК КАК ВЫДАЁТ ОШИБКУ!!
				x = 0;
				y = 1;
				break;
			case 40:
				x = 1;
				y = 0;
				break;
			case 27:
				int endTime = time(0);
				cout << "\tThe game has been closed" << endl;
				cout << "\tSeconds have been spent: " << endTime - startTime << endl;
				cout << "\tNumber of steps: " << index << endl;
				return false;
			}
		}
		if (move(x, y)) 
		{
			index++;
		}
		else 
		{
			cout << "\tUse the arrows on your keyboard or wrong move!" << endl << "\tTry again!" << endl;
		}
	}
	return 0;
}

