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
        cout << name << endl;
        cout << priorty << endl;
        cout << description << endl;
        cout << data << endl;
    }
};
struct CreateToDo
{
    ToDoList* list = new ToDoList{};


    ToDoList CreateTaskToDo()
    {
        list->name = new char[30] {};
        list->description = new char[30] {};
        list->data = new char[20] {};
        cout << "Enter task name: ";
        cin.getline(list->name, 20);
        cout
            << "Enter task Priorty" << endl
            << "1.High" << endl
            << "2.Medium" << endl
            << "3.Easy" << endl;
        cin >> list->priorty;
        cout << "Enter task description: ";
        cin.getline(list->description, 20);
        cin.ignore();
        cout << "Enter task data: ";
        cin.getline(list->data, 20);
        cin.ignore();

        return *list;
    }

};

int main()
{
    uint16_t Max{ 10 };
    CreateToDo* createList = new CreateToDo{};
    createList->CreateTaskToDo();
    return 0;
}
