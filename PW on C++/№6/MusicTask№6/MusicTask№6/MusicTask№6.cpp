#include <iostream> 
using namespace std;
struct mp3
{
	char* name{};
	char* avtor{};
	char* text{};
	int data{};
	void print()
	{
		cout << "Name: " << name << endl;
		cout << "Avtor: " << avtor << endl;
		cout << "Text:" << text << endl;
		cout << "Data: " << data << endl;
	}
};
struct createMP
{
	mp3* list = new mp3{};
	int count{};
	mp3 CreateMP3()
	{
		mp3* read = new mp3{};
		read->name = new char[50] {};
		read->text = new char[200] {};
		read->avtor = new char[50] {};
		cout << "Enter music name: " << endl;
		cin.getline(read->name, 20);
		cout << "Enter music data: " << endl;
		cin >> read->data;
		cin.ignore();
		cout << "Enter task text: " << endl;
		cin.getline(read->text, 30);
		cout << "Enter music avtor: " << endl;
		cin.getline(read->avtor, 20);
		return *read;
	}
	void addMusic()
	{
		list[count] = CreateMP3();
		count++;
	}
	void showMusic()
	{
		cout << "All music: " << endl;
		for (size_t i = 0; i < count; i++)
		{
			cout << "Number " << i + 1 << "-th music" << endl;
			list[i].print();
			cout << endl;
		}
	}
	void deleteMusic(int tmp)
	{
		delete[] list[tmp - 1].name;
		delete[] list[tmp - 1].avtor;
		delete[] list[tmp - 1].text;
		for (size_t i = 0; i < count; i++)
		{
			list[i] = list[i + 1];

		}
		count--;
	}
	void editMusic(int tmp)
	{
		list[tmp - 1] = CreateMP3();
	}
	void searchByAvtor(char* tmp)
	{

		for (size_t i = 0; i < count; i++)
		{
			int j = 0;
			while (list[i].avtor[j] == tmp[j] && tmp[j] != '\0') j++;
			if (list[i].avtor[j] == '\0' && tmp[j] == '\0')
			{
				cout << i + 1 << "-th music\n";
				list[i].print();
			}
			else
			{
				cout << "Unkown avtor" << endl;
				break;
			}
		}
	}
};
int main()
{
	createMP* createMusic = new createMP{};
	int tmp{};
	int choise{};
	char* name = new char[20] {};
	while (true)
	{
		cout
			<< "1.Add music" << endl
			<< "2.Show music list" << endl
			<< "3.Delete music" << endl
			<< "4.Edit music" << endl
			<< "5.Search by avtor" << endl;
		cin >> choise;
		cin.ignore();
		switch (choise)
		{
		case 1:
			system("cls");
			createMusic->addMusic();
			break;
		case 2:
			system("cls");
			createMusic->showMusic();
			break;
		case 3:
			system("cls");
			cout << "Enter the number of the case you want to delete" << endl;
			cin >> tmp;
			createMusic->deleteMusic(tmp);
			break;
		case 4:
			system("cls");
			cout << "Enter the number of the case you want to edit" << endl;
			cin >> tmp;
			cin.ignore();
			createMusic->editMusic(tmp);
			break;
		case 5:
			system("cls");
			cout << "Enter search by avtor: ";
			cin >> name;
			createMusic->searchByAvtor(name);
			break;
		default:
			return true;
		}
	}
	return 0;
}
