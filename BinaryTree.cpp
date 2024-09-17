#include <fstream>

struct Tree
{
    int val; //Значение
    Tree* left; //Левая ветвь
    Tree* right; //Правая ветвь
};

void deleteTree(Tree * root) //Функция удаления дерева
{
    if (root->left)
        deleteTree(root->left); //Удаление левой ветви при наличии
    root->left = nullptr;

    if (root->right)
        deleteTree(root->right); //Удаление правой ветви при наличии
    root->right = nullptr;

    delete root; //Удаление корневого значения
}

Tree* insert(Tree* root, int val) //Функция добавления элемента в дерево
{
    if (!root) //При отсутствии корневого элемента он создается
    {
        root = new Tree;
        root->val = val;
        root->left = root->right = nullptr;
    }
    else if (val <= root->val) //Элементы меньшие либо равные корневому вставляются в левую ветвь
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->val) //Элементы большие корневого вставляются в правую ветвь
    {
        root->right = insert(root->right, val);
    }
    return root;
}

void reflect(Tree* root) //Функция обработки дерева (обращение значений элементов)
{
    if (!root) //Проверка на наличие корневого элемента
    {
        return;
    }

    //Проверка на отрицательность элемента дерева
    bool isNegative = false;
    if (root->val < 0)
    {
        isNegative = true;
        root->val = -root->val; //Меняем знак
    }

    int rev = 0;

    //Обращаем значение элемента дерева
    while (root->val > 0)
    {
        rev = rev * 10 + root->val % 10;
        root->val /= 10;
    }

    //Возвращаем первоначальный знак
    isNegative ? root->val = -rev : root->val = rev;

    //Рекурсивно продолжаем обрабатывать дерево
    reflect(root->left);
    reflect(root->right);
}

void printTree(std::ostream& out, Tree* root) //Функция вывода дерева
{
    if (root)
    {
        out << root->val << " ";
        printTree(out, root->left);
        printTree(out, root->right);
    }
}

int main()
{
    std::ifstream input_file("input.txt");
    std::ofstream output_file("output.txt");

    if (!input_file) //Проверка существования файла
    {
        output_file << "File doesn't exist!\n";
        input_file.close();
        output_file.close();
    }
    else
    {
        int size = 0;
        int temp;

        while (input_file >> temp) //Последовательное считывание элементов из файла и подсчёт их количества (размер дерева)
            ++size;

        input_file.clear(); //Сброс битов состояния входного потока
        input_file.seekg(0); //Перемещение указателя потока в начало файла

        int* arr = new int[size];

        //Считывание элементов дерева
        for (int i = 0; i < size; ++i)
            input_file >> arr[i];

        input_file.close();

        Tree* root = NULL;

        //Заполнение дерева
        for (int i = 0; i < size; ++i)
        {
            root = insert(root, arr[i]);
        }

        reflect(root); //Обработка дерева

        printTree(output_file, root); //Вывод дерева

        output_file.close();

        deleteTree(root); //Удаление дерева (освобождение памяти)

        delete[] arr; //Удаление массива элементов входного файла (освобождение памяти)
    }

    return 0;
}
