using System.Text;

class DictionaryApp
{
    private Dictionary<string, Dictionary<string, List<string>>> dictionaries = new Dictionary<string, Dictionary<string, List<string>>>();

    public void Run()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.InputEncoding = Encoding.UTF8;
        Console.WriteLine("Welcome to the Dictionary");

        while (true)
        {
            Console.WriteLine("1. Create Dictionary");
            Console.WriteLine("2. List of Dictionary");
            Console.WriteLine("3. Exit");

            int choice;
            if (int.TryParse(Console.ReadLine(), out choice))
            {
                switch (choice)
                {
                    case 1:
                        CreateDictionary();
                        break;
                    case 2:
                        ManageDictionary();
                        break;
                    case 3:
                        Environment.Exit(0);
                        break;
                    default:
                        Console.WriteLine("Incorrect input");
                        break;
                }
            }
            else
                Console.WriteLine("Incorrect input");
        }
    }

    static void AddWordAndTranslation(Dictionary<string, List<string>> dictionary)
    {
        Console.WriteLine("Input word:");
        string word = Console.ReadLine();
        Console.WriteLine("Enter the separated by commas:");
        string translationInput = Console.ReadLine();
        List<string> translations = translationInput.Split(',').Select(t => t.Trim()).ToList();

        if (!dictionary.ContainsKey(word))
        {
            dictionary[word] = translations;
            Console.WriteLine("Word and translations added");
        }
        else{
            Console.WriteLine("The word exists");
        }
    }

    static void ReplaceWordOrTranslation(Dictionary<string, List<string>> dictionary)
    {
        Console.WriteLine("Input word to rename");
        string word = Console.ReadLine();

        if (dictionary.ContainsKey(word))
        {
            Console.WriteLine("Enter the separated by commas:");
            string translationInput = Console.ReadLine();
            List<string> translations = translationInput.Split(',').Select(t => t.Trim()).ToList();
            dictionary[word] = translations;
            Console.WriteLine("Word and translations added");
        }
        else
        {
            Console.WriteLine("Incorrect input");
        }
    }

    static void DeleteWordOrTranslation(Dictionary<string, List<string>> dictionary)
    {
        Console.WriteLine("Input word to delete");
        string word = Console.ReadLine();

        if (dictionary.ContainsKey(word))
        {
            dictionary.Remove(word);
            Console.WriteLine("Word and translations deleted");
        }
        else{
            Console.WriteLine("Incorrect input");
        }
    }

    static void SearchTranslation(Dictionary<string, List<string>> dictionary)
    {
        Console.WriteLine("Enter a word to search for translation");
        string word = Console.ReadLine();

        if (dictionary.ContainsKey(word))
        {
            List<string> translations = dictionary[word];
            Console.WriteLine($"Translation '{word}':");
            foreach (var translation in translations)
            {
                Console.WriteLine(translation);
            }
        }
        else
        {
            Console.WriteLine("Incorrect input");
        }
    }

    private void ExportDictionary(string dictionaryName, Dictionary<string, List<string>> dictionary)
    {
        Console.WriteLine("Enter the file name to export:");
        string fileName = Console.ReadLine();

        using (StreamWriter writer = new StreamWriter(fileName))
        {
            foreach (var entry in dictionary)
            {
                writer.WriteLine($"{entry.Key}: {string.Join(", ", entry.Value)}");
            }
        }

        Console.WriteLine($"Dictionary '{dictionaryName}' exported to file '{fileName}'.");
    }
    private void CreateDictionary()
    {
        Console.WriteLine("Enter the name of the new dictionary");
        string dictionaryName = Console.ReadLine();

        if (dictionaries.ContainsKey(dictionaryName))
        {
            Console.WriteLine("A dictionary with the same name already exists");
            return;
        }

        dictionaries[dictionaryName] = new Dictionary<string, List<string>>();
        Console.WriteLine($"Dictionary '{dictionaryName}' created.");
    }

    private void ManageDictionary()
    {
        Console.WriteLine("Select a dictionary to work with:");
        int index = 1;
        foreach (var dictionaryName in dictionaries.Keys)
        {
            Console.WriteLine($"{index}. {dictionaryName}");
            index++;
        }

        int choice;
        if (int.TryParse(Console.ReadLine(), out choice) && choice >= 1 && choice <= dictionaries.Count)
        {
            var selectedDictionary = dictionaries.ElementAt(choice - 1);

            while (true)
            {
                Console.WriteLine($"\nDictionary management '{selectedDictionary.Key}':");
                Console.WriteLine("1. Add word and translation");
                Console.WriteLine("2. Replace a word or translation");
                Console.WriteLine("3. Delete a word or translation");
                Console.WriteLine("4. Search translation of a word");
                Console.WriteLine("5. Export dictionary");
                Console.WriteLine("6. Return to previous menu");

                int subChoice;
                if (int.TryParse(Console.ReadLine(), out subChoice))
                {
                    switch (subChoice)
                    {
                        case 1:
                            AddWordAndTranslation(selectedDictionary.Value);
                            break;
                        case 2:
                            ReplaceWordOrTranslation(selectedDictionary.Value);
                            break;
                        case 3:
                            DeleteWordOrTranslation(selectedDictionary.Value);
                            break;
                        case 4:
                            SearchTranslation(selectedDictionary.Value);
                            break;
                        case 5:
                            ExportDictionary(selectedDictionary.Key, selectedDictionary.Value);
                            break;
                        case 6:
                            return;
                        default:
                            Console.WriteLine("Incorrect input");
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Incorrect input");
                }
            }
        }
        else
        {
            Console.WriteLine("Incorrect input");
        }
    }

    public static void Main(string[] args)
    {
        var app = new DictionaryApp();
        app.Run();
    }
}
