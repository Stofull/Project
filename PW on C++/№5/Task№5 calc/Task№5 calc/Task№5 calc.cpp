#include <iostream>
using namespace std;
bool number(char symbol) {
	return (symbol >= '0' && symbol <= '9');
}
int calculate(char op, int a, int b) {
	switch (op) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return 0;
	}
}
void index(char* arr, bool& test)
{
	for (size_t i = 0; i < arr[i] != '\0'; i++)
	{
		if ((arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/') &&
			(arr[i + 1] == '+' || arr[i + 1] == '-' || arr[i + 1] == '*' || arr[i + 1] == '/'))
		{
			cout << "\tWrong expression" << endl;
			test = true;
			break;
		}
		else if (arr[i] >= 58 || arr[i] <= 39)
		{
			cout << "\tWrong expression" << endl;
			test = true;
			break;
		}
		else if ((arr[0] >= 57 || arr[0] <= 48) && arr[0] != 40)
		{
			cout << "\tWrong expression" << endl;
			test = true;
			break;
		}
		else test = false;
	}
}
int main()
{
	char input[100];
	bool test = true;
	while (test == true)
	{
		cout << "Enter your expression: ";
		cin.getline(input, 100);
		index(input, test);
	}
	int numArr[100]{};
	char opArr[100]{};
	int zero = 0;
	int tmp = 0;
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (number(input[i]))
		{
			int num = input[i] - '0';
			while (number(input[i + 1]))
			{
				num = num * 10 + (input[i + 1] - '0');
				i++;
			}
			numArr[zero++] = num;
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
		{
			while (tmp > 0 && (opArr[tmp - 1] == '*' || opArr[tmp - 1] == '/'))
			{
				int b = numArr[--zero];
				int a = numArr[--zero];
				char op = opArr[--tmp];
				numArr[zero++] = calculate(op, a, b);
			}
			opArr[tmp++] = input[i];
		}
		else if (input[i] == '(')
		{
			opArr[tmp++] = '(';
		}
		else if (input[i] == ')')
		{
			while (tmp > 0 && opArr[tmp - 1] != '(')
			{
				int b = numArr[--zero];
				int a = numArr[--zero];
				char op = opArr[--tmp];
				numArr[zero++] = calculate(op, a, b);
			}
			tmp--;
		}
	}
	while (tmp > 0)
	{
		int b = numArr[--zero];
		int a = numArr[--zero];
		char op = opArr[--tmp];
		numArr[zero++] = calculate(op, a, b);
	}
	cout << "Result: " << numArr[0] << endl;
	return 0;
}
