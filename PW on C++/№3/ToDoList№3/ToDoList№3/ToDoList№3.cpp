#include <iostream> 
using namespace std;
struct ToDoList
{
	char* name{};
	int priorty{};
	char* description{};
	char* data{};
	void print()
	{
		cout << "Name: " << name << endl;
		cout << "Priorty: " << priorty << endl;
		cout << "Description:" << description << endl;
		cout << "Data: " << data << endl;
	}
};
struct CreateToDo
{
	ToDoList* list = new ToDoList{};
	int count{};
	ToDoList CreateTaskToDo()
	{
		ToDoList* readList = new ToDoList{};
		readList->name = new char[30] {};
		readList->description = new char[30] {};
		readList->data = new char[20] {};
		cout << "Enter task name: ";
		cin.getline(readList->name, 20);
		cout
			<< "Enter task Priorty" << endl
			<< "1.High" << endl
			<< "2.Medium" << endl
			<< "3.Easy" << endl;
		cin >> readList->priorty;
		cout << "Enter task description: ";
		cin.ignore();
		cin.getline(readList->description, 30);
		cout << "Enter task data: ";
		cin.getline(readList->data, 20);
		return *readList;
	}
	void addTask()
	{
		list[count] = CreateTaskToDo();
		count++;
	}
	void showtask()
	{
		cout << "All tasks: " << endl;
		for (size_t i = 0; i < count; i++)
		{
			cout << "Number " << i + 1 << "- th task" << endl;
			list[i].print();
			cout << endl;
		}
	}
	void deletetask(int tmp)
	{
		delete[] list[tmp - 1].name;
		delete[] list[tmp - 1].data;
		delete[] list[tmp - 1].description;
		for (size_t i = 0; i < count; i++)
		{
			list[i] = list[i + 1];

		}
		count--;
	}
	void edittask(int tmp)
	{
		list[tmp - 1] = CreateTaskToDo();
	}
	void searchByName(char* tmp)
	{
		int turn{};
		int length = sizeof(tmp);
		while (true)
		{
			cin >> turn;


			switch (turn)
			{
			case 1:
				for (size_t i = 0; i < count; i++)
				{
					int j = 0;
					while (list[i].name[j] == tmp[j] && tmp[j] != '\0') j++;
					if (list[i].name[j] == '\0' && tmp[j] == '\0')
					{
						cout << i + 1 << "-th task\n";
						list[i].print();
					}


					break;
				}
			default:
				cout << "Incorrect input try again" << endl;
				break;
			}


		}
	}
};

int main()
{
	CreateToDo* createList = new CreateToDo{};
	int tmp{};
	int choise{};
	char* name = new char[20] {};
	while (true)
	{
		cout
			<< "1.Add task" << endl
			<< "2.Show task" << endl
			<< "3.Delete task" << endl
			<< "4.Edit task" << endl
			<< "5.Search by name" << endl;
		cin >> choise;
		cin.ignore();
		switch (choise)
		{
		case 1:
			system("cls");
			createList->addTask();
			break;
		case 2:
			system("cls");
			createList->showtask();
			break;
		case 3:
			system("cls");
			cout << "Enter the number of the case you want to delete" << endl;
			cin >> tmp;
			createList->deletetask(tmp);
			break;
		case 4:
			system("cls");
			cout << "Enter the number of the case you want to edit" << endl;
			cin >> tmp;
			cin.ignore();
			createList->edittask(tmp);
			break;
		case 5:
			system("cls");
			cout << "Enter search: ";
			cin >> name;
			createList->searchByName(name);
		default:
			return true;
		}
	}



	return 0;
}
