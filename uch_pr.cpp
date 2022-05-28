#include <iostream> //подключение библеотек
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

void word_separation(string st, vector <string>& words)   //функция разделяющая слова
{
    string temp_word = "";  //создание временной переменной для текущего слова
    for (int i = 0; i <= st.length(); i++)   //цикл проверяющий каждый символ текста
    {
        if ((st[i] >= 'А' && st[i] <= 'я') || (st[i] >= '0' && st[i] <= '9'))   //если символ это буква или цифра, то...
        {
            temp_word = temp_word + st[i];   //добавление буквы к текущему слову
        }
        else if ((st[i] == ' ') && ((st[i + 1] >= 'А' && st[i + 1] <= 'я') || (st[i + 1] >= '0' && st[i + 1] <= '9')))   //если символ это пробел а также следующий элемент это буква или цифра
        {
            words.push_back(temp_word);   //добавление текущего слова в массив 
            temp_word = "";   //сброс переменной для текущего слова
        }
    }
}

vector<string> sort(vector<string> data)   //функция сортирующая массив
{
    double factor = 1.2473309;
    int step = data.size() - 1;
    char temp_letter1, temp_letter2;
    while (step >= 1)
    {
        for (int i = 0; i + step < data.size(); i++)
        {
            temp_letter1 = data[i][0];
            temp_letter2 = data[i + step][0];
            if (data[i][0] >= 'А' && data[i][0] <= 'Я') {
                temp_letter1 = data[i][0] - 'А' + 'а';
            }
            if (data[i + step][0] >= 'А' && data[i + step][0] <= 'Я') {
                temp_letter2 = data[i + step][0] - 'А' + 'а';
            }
            if (temp_letter1 > temp_letter2) {
                swap(data[i], data[i + step]);
            }
        }
        step /= factor;
    }
    return data;
}

void analysis(vector<string> sorted_data, string text, float time)   //функция для анализа текста
{
    ofstream out("analysis.txt");
    if (out.is_open())
    {
        out << "Введённый текст: " << endl;
        out << text << endl << endl;
        out << "20 вариант: кириллица, по алфавиту, по возрастанию, учитывать числа, сортировка расчёской" << endl;
        out << "Количество слов: " << sorted_data.size() + 1 << endl;
        out << "Время выполнения сортировки: " << time << " сек" << endl << endl;
        out << "Статистика (количество слов на каждую букву алфавита, количество чисел на каждую цифру): " << endl;
        int letters[33] = { 0 };   //вывод побуквенной статистики
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < sorted_data.size(); j++) {
                if (sorted_data[j][0] == (char)(i + (int)('А')) || sorted_data[j][0] == (char)(i + (int)('а'))) {
                    letters[i] += 1;
                }
            }
            out << "Слов на букву '" << (char)(i + (int)('А')) << "': " << letters[i] << endl;
        }
        int numbers[10] = { 0 };
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < sorted_data.size(); j++) {
                if (sorted_data[j][0] == (char)(i + (int)('0'))) {
                    numbers[i] += 1;
                }
            }
            out << "Чисел на цифру '" << i << "': " << numbers[i] << endl;
        }
    }
    out.close();
}

void result(vector<string> sorted_data)   //внесение отсортированного текста в отдельный файл
{
    ofstream out("result.txt");
    if (out.is_open())
    {
        for (int i = 0; i < sorted_data.size(); i++)
        {
            out << sorted_data[i] << endl;
        }
    }
    out.close();
}

void main()
{
    setlocale(LC_ALL, "Russian");
    string line, text;
    vector<string> data, sorted_data;
    ifstream fin("text.txt");   //открытие исходного файла
    if (fin.is_open())
    {
        while (getline(fin, line))
        {
            text = text + line + " ";   //чтение текста из файла
        }
    }
    fin.close();
    word_separation(text, data);  //выхов функции разделяющей слова
    unsigned int start_time = clock();
    sorted_data = sort(data);
    unsigned int end_time = clock();
    result(sorted_data);   //вывод функции записывающей результаты в файл
    analysis(sorted_data, text, ((float)(end_time - start_time) / (float)CLOCKS_PER_SEC));   //вывод функции записывающей анализ в файл
    cout << "Программа успешно завершила свою работу. Отсортированный массив находится в файле result.txt, анализ текста находится в файле analysis.txt.";
}