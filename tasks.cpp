#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void error(const string &s)
{
    throw runtime_error(s);
}

const string filename = "tasks.txt";

void print_option()
{
    cout << " Выбери одну из опций: 1, 2, 3, 0:\n";
    cout << " 1 - добавить задачу\n"
         << " 2 - удалить задачу\n"
         << " 3 - показать задачи\n"
         << " 0 - выход \n\n -> ";
}

void print_tasks()
{
    ifstream inputFile(filename);
    if (!inputFile) error("файл не открылся\n");
    
    string line;
    cout << "\n\033[33mтекущие задачи: \n";
    int i = 1;
    while (getline(inputFile, line))
    {
        cout << i << ". " << line << endl;
        ++i;
    }

    cout << "\033[0m\n";

    inputFile.close();
}

void add_task()
{
    ofstream outputFile(filename, std::ios::app);
    if (!outputFile) error("файл не открылся\n");

    cin.ignore();
    cout << "\nнапиши задачу: \n\n";
    string s;
    getline(cin, s);

    outputFile << s << endl;

    cout << '\n';

    outputFile.close();

    print_tasks();
}


void delete_task() 
{
    vector<string> tasks;

    ifstream inputFile(filename);
    if (!inputFile) error("файл не открылся\n");

    string line;
    while (getline(inputFile, line)) 
    {
        tasks.push_back(line);
    }
    inputFile.close();

    if (tasks.size() == 0) 
    {
        cout << "\n\033[31mзадач нет\033[0m\n\n";
        return;
    }
    print_tasks();

    cin.ignore();
    int number = 0;
    cout << "выбери номер для удаления -> ";
    cin >> number;
    tasks.erase(tasks.begin() + (number - 1));

    ofstream outputFile(filename);
    if (!outputFile) error("файл не открылся\n");

    for (string s : tasks) {
        outputFile << s << endl;
    }
    outputFile.close();
    print_tasks();
}

char correct_number()
{
    char h = '+';
    while (1)
    {
        if (h == '1' || h == '2' || h == '3' || h == '0')
            return h;
        print_option();
        cin >> h;
    }
}

void choose_option()
{

    char choose;
    while (1)
    {
        choose = correct_number();
        if (choose == '0')
            return;
        switch (choose)
        {
        case '1':
            add_task();
            break;
        case '2':
            delete_task();
            break;
        case '3':
            print_tasks();
            break;
        default:
            error("неизвестная команда");
            break;
        }
    }
}

int main()
{
    cout << "\033[35m\n";

    cout << "POOOP POOO   P    OP  POOO   POOO  OOOOO  P" << endl;
    cout << "O   O P   O  P   O P  P   O  P       P    P" << endl;
    cout << "O   O POOO   P  O  P  POOO   POOO    P    P" << endl;
    cout << "O   O P      P O   P  P   O  P       P    " << endl;
    cout << "O   O P      PO    P  POOO   POOO    P    O\n"
         << endl;

    cout << "\033[0m";

    try
    {
        choose_option();
    }
    catch (runtime_error &e)
    {
        cerr << "\n\033[31m" << e.what() << "\033[0m\n\n";
        return 1;
    }
    catch (...)
    {
        cerr << "\033[31mexception\n"
             << endl;
        return 2;
    }

    return 0;
}
