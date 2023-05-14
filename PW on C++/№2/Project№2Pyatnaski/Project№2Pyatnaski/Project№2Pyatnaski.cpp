#include <iostream> 
#include <ctime> 
#include <windows.h>  
using namespace std;

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

void replacement(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void init(int** square, int length)
{
    int count = 1;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            square[i][j] = count;
            count++;
        }
    }
    square[length - 1][length - 1] = 0;
}

void mix(int** square, int length)
{
    time_t srand(time(0));
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
void pin(int** square, int length)
{
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
bool win(int** square, int length)
{
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
bool move(int x, int y, int** square, int length)
{
    int zero_x{}, zero_y{};
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
    time_t startTime = time(0);
    int length{};
    while (length != 3 && length != 4)
    {
        cout
            << "\tEnter board size" << endl
            << "1.3x3" << endl
            << "2.4x4" << endl;
        cin >> length;
        length += 2;
        system("cls");
        if (length != 3 && length != 4) cout << "Enter correct number" << endl;
    }
    int manual{};
    while(manual != 1 && manual !=2)
    {
        system("cls");
        cout << "\tGame modes" << endl
            << "1.Manual assembly" << endl
            << "2.Computer collects (random)" << endl;
        cin >> manual;
    }
    int** square = new int* [length];
    for (size_t i = 0; i < length; i++)
    {
        square[i] = new int[length] {};
    }
    int index{};
    init(square, length);
    mix(square, length);
    while (true)
    {
        pin(square, length);
        if (win(square, length))
        {
            time_t endTime = time(0);
            cout << "\tYou won!" << endl;
            cout << "\t" << endTime - startTime << "Seconds have been spent" << endl;
            cout << "\tNumber of steps = " << index << endl;
            break;
        }
        if (manual == 2)
        {
            int x, y = 0;
            cout << "Press any button to continue"<<endl << "To exit press 'Esc'" << endl;
            keyFinding(x);
            mix(square, length);
            if (x == 27)
            {
                time_t endTime = time(0);
                cout << "\tThe game has been closed" << endl;
                cout << "\tSeconds have been spent: " << endTime - startTime << endl;
                cout << "\tNumber of steps: " << index << endl;
                return false;
            }
            else index++;
        }
        else if(manual == 1)
        {
            int x, y = 0;
            cout << "Use arrow keys to move and press Enter: " << endl << "To exit press 'Esc'" << endl;
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
                case 39:
                    x = 0;
                    y = 1;
                    break;
                case 40:
                    x = 1;
                    y = 0;
                    break;
                case 27:
                    time_t endTime = time(0);
                    cout << "\tThe game has been closed" << endl;
                    cout << "\tSeconds have been spent: " << endTime - startTime << endl;
                    cout << "\tNumber of steps: " << index << endl;
                    return false;
                }
            }
            if (move(x, y, square, length))
            {
                index++;
            }
            else
            {
                cout << "\tUse the arrows on your keyboard or wrong move!" << endl << "\tTry again!" << endl;
            }
        }
    }
    return 0;
}