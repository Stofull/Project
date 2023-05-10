#include <iostream>
#include <ctime>
using namespace std;
const int length = 3;
int square[length][length];
void replacement(int& a, int& b) {
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

int main()
{
    int index{};
    init();
    mix();
    while (true) {
        pin();
        if (win()) {
            cout << "You won!" << endl;
            cout << "Summ try = " << index;
            break;
        }
        int x, y;
        cout << "Enter x and y to move: ";
        cin >> x >> y;
        if (x < 0 || x >= length || y < 0 || y >= length) {
            cout << "Invalid please try again." << endl;
            continue;
        }
        index++;
        int forX[] = { 0, 0, 1, -1 };
        int forY[] = { 1, -1, 0, 0 };
        bool found = false;
        for (int i = 0; i < 4; i++) {
            int newX = x + forX[i];
            int newY = y + forY[i];
            if (newX >= 0 && newX < length && newY >= 0 && newY < length && square[newX][newY] == 0) {
                replacement(square[x][y], square[newX][newY]);
                found = true;
                break;
            }
        }
        if (found = false) {
            cout << "False x y ,please try again." << endl;
        }
    }
    return 0;
}
