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
char* entry(char* text)
{
	FILE* file{};
	fopen_s(&file, "data.txt", "r");
	if (file == nullptr) {
		cout << "Error" << endl;
		return text;
	}
	fscanf_s(file, "%[^\n]", text, 200);
	fclose(file);
	return text;
}
struct createMP
{
	int tmp{};
	mp3* list = new mp3{};
	int count{};
	mp3 CreateMP3()
	{
		mp3* read = new mp3{};
		read->name = new char[50] {};
		read->text = new char[200] {};
		read->avtor = new char[30] {};
		cout << "Enter music name: " << endl;
		cin.getline(read->name, 20);
		cout << "Enter music data: " << endl;
		cin >> read->data;
		cin.ignore();
		cout
			<< "Enter task text: " << endl
			<< "1.Enter your text" << endl
			<< "2.Write from file" << endl;
		cin >> tmp;
		if (tmp == 1) 
		{
			cin.ignore();
			cout << "Enter task text: " << endl;
			cin.getline(read->text, 200);
		}
		else if (tmp == 2) 
		{
			cin.ignore();
			read->text = entry(read->text);
		}
		cout << "Enter music avtor: " << endl;
		cin.getline(read->avtor, 30);
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
	void saveLyricsToFile(int tmp, createMP* createMusic)
	{
		FILE* file{};
		char* lyrics = createMusic->list[tmp - 1].text;
		fopen_s(&file, "data.txt", "w");
		if (file == nullptr) {
			cout << "Error" << endl;
			return;
		}
		fprintf(file, "%s\n", lyrics);
		if (file != nullptr)
			fclose(file);
	}
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
			<< "5.Search by avtor" << endl
			<< "6.Saving lyrics to a file" << endl
			<< "Enter any other number to exit" << endl;
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
		case 6:
			system("cls");
			cout << "Enter the number of the song whose lyrics you want to record" << endl;
			cin >> tmp;
			saveLyricsToFile(tmp, createMusic);
			break;
		default:
			return true;
		}
	}
	return 0;
}
