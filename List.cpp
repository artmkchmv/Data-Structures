#include <fstream>

using namespace std;

class Node //Класс, реализующий узел списка
{

public:

    int value; //Поле данных
    Node* next; //Указатель на следующий узел

    Node(int val) //Конструктор инициализации
    {
        value = val;
        next = NULL;
    }
};

class list //Класс, реализующий список
{

public:

    Node* head; //"Голова" списка
    int size; //Размер списка

    list() //Конструктор по умолчанию
    {
        head = NULL;
        size = 0;
    }

    list(Node* hd, int sz) //Конструктор инициализации
    {
        head = hd;
        size = sz;
    }

    ~list() //Деструктор
    {
        while (head) //Пока есть "голова"
        {
            if (size == 0) //Выход из цикла, если размер списка 0
                break;

            Node* temp = head; //Запомнить адрес первого элемента
            head = head->next; //Перейти на следующий элемент
            delete temp; //Освободить первый элемент

            size--; //Уменьшить размер
        }
    }

    void push_back(int value) //Метод класса list, предназначенный для добавления элемента в конец списка
    {
        ++size; //Увеличить размер
        Node* newNode = new Node(value);
        if (!head) //Если у списка нет "головы"
        {
            head = newNode; //Добавляем новый узел
            newNode->next = head; //Новый узел указывает на "голову" - циклический список
        }
        else
        {
            Node* temp = head; //Временный узел, изначально указывающий на голову
            while (temp->next != head) //Пока не дойдем до узла, предшествующего "голове"
            {
                temp = temp->next; //Переход к следующему узлу списка
            }
            temp->next = newNode; //Добавляем новый узел в конец
            newNode->next = head; //Добавляем указатель на "голову"
        }
    }

    void printToFile(string fileName) //Метод класса list, предназначенный для вывода списка в файл
    {
        ofstream outFile(fileName);

        if (!head) //При отсутствии "головы" - выход из функции
        {
            return;
        }

        Node* temp = head; //Временный узел, изначально указывающий на голову

        outFile << size << " "; //Вывод размера списка

        do
        {
            outFile << temp->value << " "; //Последовательный вывод значений, хранящихся в узлах списка
            temp = temp->next; //Переход к следующему узлу списка
        } while (temp != head); //Пока временный узел опять не станет "головой"

        outFile << '\n';
        outFile.close();
    }
};

void swap1(Node* a, Node* b) //Функция, выполняющая перестановку значений
{
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

void swap2(Node*& a, Node*& b) //Функция, выполняющая перестановку узлов
{
    Node* next2 = b->next;
    Node* prev1;

    prev1 = b;
    while (prev1->next != a) //Поиск узла предшествующего a
        prev1 = prev1->next;

    //Обмениваются соседние узлы
    b->next = NULL;
    a->next = NULL;
    prev1->next = NULL;

    b->next = a;
    a->next = next2;
    prev1->next = b;

}

void bubbleSort(list& l) //Функция, осуществляющая пузырьковую сортировку списка
{
    if (!l.head || !l.head->next) //Если список пуст или в нём 1 элемент - выход из функции
    {
        return;
    }

    bool swapped;
    Node* temp;

    do
    {
        swapped = false;
        temp = l.head; //Временный узел, изначально указывающий на голову

        while (temp->next != l.head) //Пока следующий за временным узлом узел не станет "головой"
        {
            if (temp->value > temp->next->value) //Если значение, хранящееся в предыдущем узле, больше значения, хранящегося в последующем
            {
                //Перестановка узлов
                if (temp == l.head)
                {
                    swap2(temp, temp->next);
                    l.head = temp->next;
                }


                swapped = true; //Если выполняется перестановка - true

            }

            temp = temp->next; //Переход к следующему узлу списка
        }

    } while (swapped); //Пока есть перестановки
}

int main()
{
    ifstream input_file("input.txt");
        
    if (!input_file) //Проверка существования файла
    {
        ofstream output_file("output.txt");

        output_file << "File doesn't exist!\n";

        output_file.close();
    }
    else
    {
        //Проверка метода сортировки
        int type_of_sort;
        input_file >> type_of_sort; 

        list l;

        //Заполнение списка элементами из файла
        int temp;
        while (input_file >> temp)
        {
            l.push_back(temp);
        }

        if (type_of_sort) //1 - Пузырьковая сортировка
        {
            bubbleSort(l);
            l.printToFile("output.txt");
        }
    }

    input_file.close();

    return 0;
}
