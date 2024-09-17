#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

class str //Класс - строка
{
private:

    char* STRING; //Содержимое строки
    int STRING_LENGTH; //Длина строки

public:

    str() //Конструктор по умолчанию
    {
        STRING = nullptr;
        STRING_LENGTH = 0;
    }

    str(const char* text) //Конструктор инициализации
    {
        STRING_LENGTH = strlen(text); //Вычисление длины строки с помощью функции strlen()

        this->STRING = new char[STRING_LENGTH + 1]; //Выделение памяти под строку и еще один символ - терминирующий ноль

        for (int i = 0; i < STRING_LENGTH; i++) //Копирование элементов
        {
            this->STRING[i] = text[i];
        }

        this->STRING[STRING_LENGTH] = '\0'; //Завершение строки терминирующим нулем
    }

    str(const str& other) //Конструктор копирования
    {
        STRING_LENGTH = strlen(other.STRING); //Вычисление длины строки с помощью функции strlen()

        STRING = new char[STRING_LENGTH + 1]; //Выделение памяти под строку и еще один символ - терминирующий ноль

        for (int i = 0; i < STRING_LENGTH; i++) //Копируем символы строки в строку созданного класса
        {
            this->STRING[i] = other.STRING[i];
        } 

        STRING[STRING_LENGTH] = '\0'; //Завершение строки терминирующим нулем
    }

    ~str() //Деструктор
    {
        delete[] STRING;
    }

    str& operator =(const str& other) //Перегрузка операции присваивания
    {
        if (STRING != nullptr) //Удаление предыдущего содержимого строки, если она непустая
        {
            delete[] STRING;
        }

        STRING_LENGTH = strlen(other.STRING); //Вычисление длины строки с помощью функции strlen()

        STRING = new char[STRING_LENGTH + 1]; //Выделение памяти под строку и еще один символ - терминирующий ноль

        for (int i = 0; i < STRING_LENGTH; i++) //Копируем символы строки в строку созданного класса
        {
            this->STRING[i] = other.STRING[i];
        }

        STRING[STRING_LENGTH] = '\0'; //Завершение строки терминирующим нулем

        return *this;
    }

    str operator +(const str& other) //Перегрузка операции сложения (конкатенация)
    {
        str NEW_STRING; //Новая строка - результат сложения

        int THIS_STRING_LENGTH = strlen(STRING); //Длина первой строки
        int OTHER_STRING_LENGTH = strlen(other.STRING); //Длина второй строки

        NEW_STRING.STRING_LENGTH = THIS_STRING_LENGTH + OTHER_STRING_LENGTH; //Длина новой строки - сумма двух предыдущих

        NEW_STRING.STRING = new char[THIS_STRING_LENGTH + OTHER_STRING_LENGTH + 1]; //Выделение памяти под новую строку и еще один символ - терминирующий ноль

        int i;
        for (i = 0; i < THIS_STRING_LENGTH; i++)
        {
            NEW_STRING.STRING[i] = this->STRING[i]; //Добавляем элементы первой строки в новую строку
        }

        for (int j = 0; j < OTHER_STRING_LENGTH; j++, i++)
        {
            NEW_STRING.STRING[i] = other.STRING[j]; //Добавляем элементы второй строки в новую строку
        }

        NEW_STRING.STRING[THIS_STRING_LENGTH + OTHER_STRING_LENGTH] = '\0'; //Завершение новой строки терминирующим нулем

        return NEW_STRING;
    }

    bool operator ==(const str& other) //Перегрузка операции сравнения на равенство
    {
        bool res = false;

        if (STRING_LENGTH != other.STRING_LENGTH) //Сравнение длины строк
        {
            res = false;
        }
        else
        {
            for (int i = 0; i < STRING_LENGTH; i++)
            {
                if (this->STRING[i] == other.STRING[i]) //Сравнение элементов строк
                {
                    res = true;
                    continue;
                }
                else
                {
                    res = false;
                    break;
                }
            }
        }
        return res;
    }

    bool operator >(const str& other) //Перегрузка операции сравнения "больше"
    {
        bool res = false;

        if (STRING_LENGTH > other.STRING_LENGTH) //Сравнение длины строк
        {
            res = true;
        }

        for (int i = 0; i < STRING_LENGTH; i++)
        {
            if ((int)this->STRING[i] > (int)other.STRING[i]) //Сравнение ASCII кодов элементов строк
            {
                res = true;
                break;
            }
            else
            {
                res = false;
            }
        }
        
        return res;
    }

    bool operator <(const str& other) //Перегрузка операции сравнения "меньше"
    {
        bool res = false;

        if (STRING_LENGTH < other.STRING_LENGTH) //Сравнение длины строк
        {
            res = true;
        }

        for (int i = 0; i < STRING_LENGTH; i++)
        {
            if ((int)this->STRING[i] < (int)other.STRING[i]) //Сравнение ASCII кодов элементов строк
            {
                res = true;
                break;
            }
            else
            {
                res = false;
            }
        }

        return res;
    }

    bool operator >=(const str& other) //Перегрузка операции сравнения "больше или равно"
    {
        return !(*this < other); //Вернуть обратный результат операции сравнения "меньше"
    }

    bool operator <=(const str& other) //Перегрузка операции сравнения "меньше или равно"
    {
        return !(*this > other); //Вернуть обратный результат операции сравнения "больше"
    }

    friend ifstream& operator >>(ifstream& in, str& text) //Перегрузка оператора чтения из потока
    {
        char buffer[256];
        in >> buffer;

        text = str(buffer);

        return in;
    }

    friend ofstream& operator <<(ofstream& out, const str& text) //Перегрузка оператора вывода в поток
    {
        for (int i = 0; i < text.STRING_LENGTH; i++)
        {
            out << text.STRING[i]; //Последовательный вывод элементов строки в поток
        }

        return out;
    }

    int getLength() //Метод, возвращающий длину строки
    {
        return this->STRING_LENGTH;
    }

    void add(int INDEX, char C) //Метод, принимающий в качестве аргументов индекс в строке и символ и добавляющий в строку на соответствующую позицию указанный символ
    {
        if (INDEX >= 0 && INDEX <= STRING_LENGTH) //Проверка значения индекса на то, что он лежит в пределах длины строки
        {
            char* NEW_STRING = new char[STRING_LENGTH + 2]; //Выделение памяти под новую строку и еще двух символов - новый символ и терминирующий ноль

            for (int i = 0; i < INDEX; i++) //Добавляем элементы до указанного индекса в новую строку
            {
                NEW_STRING[i] = STRING[i];
            }

            NEW_STRING[INDEX] = C; //Добавляем символ на указанный индекс

            for (int i = INDEX + 1; i < STRING_LENGTH + 1; i++) //Добавляем оставшиеся элементы после добавленного символа в новую строку
            {
                NEW_STRING[i] = STRING[i - 1];
            }

            NEW_STRING[STRING_LENGTH + 1] = '\0'; //Завершение новой строки терминирующим нулем

            delete[] STRING; //Очищение памяти, занятой предыдущей строкой

            STRING = NEW_STRING; //Присваивание указателя на новую строку
            ++STRING_LENGTH; //Увеличить длину строки на 1
        }
    }

    void remove(int INDEX) //Метод, принимающий в качестве аргумента индекс в строке и удаляющий элемент из строки на соответствующей позиции
    {
        if (INDEX >= 0 && INDEX < STRING_LENGTH) //Проверка значения индекса на то, что он лежит в пределах длины строки
        {
            char* NEW_STRING = new char[STRING_LENGTH]; //Выделение памяти под новую строку и еще один символ - терминирующий ноль (без + 1, так как строка стала меньше из-за удалённого элемента)

            for (int i = 0; i < INDEX; i++) //Добавляем элементы до указанного индекса в новую строку
            {
                NEW_STRING[i] = STRING[i];
            }

            for (int i = INDEX + 1; i < STRING_LENGTH; i++) //Добавляем оставшиеся элементы после указанного индекса в новую строку
            {
                NEW_STRING[i - 1] = STRING[i];
            }

            NEW_STRING[STRING_LENGTH - 1] = '\0'; //Завершение новой строки терминирующим нулем

            delete[] STRING; //Очищение памяти, занятой предыдущей строкой

            STRING = NEW_STRING; //Присваивание указателя на новую строку
            --STRING_LENGTH; //Уменьшить длину на 1
        }
    }

    str intersection(const str& STR_1, const str& STR_2) //Метод, принимающий в качестве аргументов две строки и возвращающий в качестве результата новую строку - пересечение строк
    {
        char* result = new char[min(STR_1.STRING_LENGTH, STR_2.STRING_LENGTH) + 1]; //Выделение памяти под результат и еще один символ - терминирующий ноль

        int pos = 0;

        for (int i = 0; i < STR_1.STRING_LENGTH; i++)
        {
            for (int j = 0; j < STR_2.STRING_LENGTH; j++)
            {
                if (STR_1.STRING[i] == STR_2.STRING[j])
                {
                    result[pos++] = STR_1.STRING[i];
                    break;
                }
            }
        }

        result[pos] = '\0'; //Завершение строки терминирующим нулем

        str res(result); //Создание новой строки на основе результата

        delete[] result; //Освобождение памяти

        return res;
    }
};

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    if (!input_file) //Проверка существования файла
    {
        output_file << "File doesn't exist!\n";
        input_file.close();
        output_file.close();
    }
    else
    {
        int KEY; //Ключ
        input_file >> KEY;

        str str_1, str_2, str_3;

        int index;
        char symbol;

        switch (KEY)
        {
        case (0): //Тест метода добавления символа в строку
            input_file >> str_1;
            input_file >> index;
            input_file >> symbol;
            str_1.add(index, symbol);
            output_file << str_1;
            break;
        case (1): //Тест удаления символа из строки
            input_file >> str_1;
            input_file >> index;
            str_1.remove(index);
            output_file << str_1;
            break;
        case (2): //Получение количества символов в строке
            input_file >> str_1;
            output_file << str_1.getLength();
            break;
        case (3): //Сложение строк
            input_file >> str_1 >> str_2;
            output_file << str_1 + str_2;
            break;
        case (4): //Пересечение строк
            input_file >> str_1 >> str_2;
            output_file << str_3.intersection(str_1, str_2);
            break;
        case (5): //Операция сравнения на равенство
            input_file >> str_1 >> str_2;
            output_file << (str_1 == str_2);
            break;
        }

        input_file.close();
        output_file.close();
    }

    return 0;
}
