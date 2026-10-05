#include <iostream>

using namespace std;


struct Part
{
    int id;
    char name[50];
    int defectPercent;
};


struct Node
{
    Part data;
    Node* next;
    Node* prev;
};


struct List
{
    Node* head = nullptr;
    Node* tail = nullptr;
};

List list;

void push_front()
{
    Part part;

    cout << "Введите ID детали: ";
    cin >> part.id;
    cin.ignore(1000, '\n');

    cout << "Введите название детали: ";
    cin.getline(part.name, 50);

    cout << "Введите процент брака: ";
    cin >> part.defectPercent;


    Node* newNode = new Node;

    newNode->data = part;
    newNode->prev = nullptr;
    newNode->next = list.head;


    if (list.head == nullptr)
    {
        list.head = newNode;
        list.tail = newNode;
    }
    else
    {
        list.head->prev = newNode;
        list.head = newNode;
    }
    cout << "Элемент добавлен в начало.\n";
}

void push_back()
{
    Part part;

    cout << "Введите ID детали: ";
    cin >> part.id;
    cin.ignore(1000, '\n');

    cout << "Введите название детали: ";
    cin.getline(part.name, 50);

    cout << "Введите процент брака: ";
    cin >> part.defectPercent;


    Node* newNode = new Node;
    newNode->data = part;
    newNode->next = nullptr;
    newNode->prev = list.tail;


    if (list.tail == nullptr)
    {
        list.head = newNode;
        list.tail = newNode;
    }
    else
    {
        list.tail->next = newNode;
        list.tail = newNode;
    }
    cout << "Элемент добавлен в конец.\n";
}

void pop_front()
{
    if (list.head == nullptr)
    {
        cout << "Список пуст.\n";
        return;
    }

    Node* del = list.head;
    if (list.head == list.tail)
    {
        list.head = nullptr;
        list.tail = nullptr;
    }
    else
    {
        list.head = list.head->next;
        list.head->prev = nullptr;
    }
    delete del;
    cout << "Первый элемент удален.\n";
}

void pop_back()
{
    if (list.tail == nullptr)
    {
        cout << "Список пуст.\n";
        return;
    }

    Node* del = list.tail;
    if (list.head == list.tail)
    {
        list.head = nullptr;
        list.tail = nullptr;
    }
    else
    {
        list.tail = list.tail->prev;
        list.tail->next = nullptr;
    }
    delete del;
    cout << "Последний элемент удален.\n";
}


void display_forward()
{
    if (list.head == nullptr)
    {
        cout << "Список пуст.\n";
    }
    Node* cur = list.head;
    cout << "\nСписок от начала к концу:\n";
    while (cur != nullptr)
    {
        cout << "ID: " << cur->data.id << endl;
        cout << "Название: " << cur->data.name << endl;
        cout << "Процент брака: " << cur->data.defectPercent << "%" << endl;
        cur = cur->next;
    }
}

void display_backward()
{
    if (list.tail == nullptr)
    {
        cout << "Список пуст.\n";
        return;
    }

    Node* cur = list.tail;
    cout << "\nСписок от конца к началу:\n";
    while (cur != nullptr)
    {
        cout << "ID: " << cur->data.id << endl;
        cout << "Название: " << cur->data.name << endl;
        cout << "Процент брака: " << cur->data.defectPercent << "%" << endl;
        cur = cur->prev;
    }
}

Node* foundNode = nullptr;
void find()
{
    int id;

    cout << "Введите ID детали для поиска: ";
    cin >> id;

    Node* cur = list.head;

    while (cur != nullptr)
    {
        if (cur->data.id == id)
        {
            foundNode = cur;

            cout << "\nЭлемент найден:\n";
            cout << "ID: " << cur->data.id << endl;
            cout << "Название: " << cur->data.name << endl;
            cout << "Процент брака: " << cur->data.defectPercent << "%" << endl;
            return;
        }

        cur = cur->next;
    }

    foundNode = nullptr;

    cout << "Элемент не найден.\n";
}

void deleteNode()
{
    if (foundNode == nullptr)
    {
        cout << "Сначала необходимо найти элемент.\n";
        return;
    }
    if (foundNode == list.head)
    {
        pop_front();
        foundNode = nullptr;
        cout << "Найденный элемент удален.\n";
        return;
    }
    if (foundNode == list.tail)
    {
        pop_back();
        foundNode = nullptr;
        cout << "Найденный элемент удален.\n";
        return;
    }
    foundNode->prev->next = foundNode->next;
    foundNode->next->prev = foundNode->prev;

    delete foundNode;
    foundNode = nullptr;
    cout << "Найденный элемент удален.\n";
}

void clear()
{
    while (list.head != nullptr)
    {
        Node* cl = list.head;
        list.head = list.head->next;
        delete cl;
    }
    list.tail = nullptr;
    foundNode = nullptr;
    cout << "Список полностью очищен.\n";
}

void findMaxDefect()
{
    if (list.head == nullptr)
    {
        cout << "Список пуст.\n";
        return;
    }
    Node* maxNode = list.head;
    Node* cur = list.head->next;

    while (cur != nullptr)
    {
        if (cur->data.defectPercent > maxNode->data.defectPercent)
        {
            maxNode = cur;
        }

        cur = cur->next;
    }

    cout << "\nДеталь с максимальным процентом брака:\n";
    cout << "ID: " << maxNode->data.id << endl;
    cout << "Название: " << maxNode->data.name << endl;
    cout << "Процент брака: " << maxNode->data.defectPercent << "%" << endl;
}

void deleteByDefect()
{
    if (list.head == nullptr)
    {
        cout << "Список пуст.\n";
    }
    int value;
    cout << "Введите допустимый процент брака: ";
    cin >> value;

    Node* cur = list.head;
    while (cur != nullptr)
    {
        Node* nextNode = cur->next;
        if (cur->data.defectPercent > value)
        {
            if (cur == list.head)
            {
                pop_front();
            }
            else if (cur == list.tail)
            {
                pop_back();
            }
            else
            {
                //B   A    C
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;

                delete cur;
            }
        }
        cur = nextNode;
    }
    cout << "Удаление завершено.\n";
}

void moveMinToFront()
{
    if (list.head == nullptr)
    {
        cout << "Список пуст.\n";
    }
    Node* minNode = list.head;
    Node* cur = list.head->next;
    while (cur != nullptr)
    {
        if (cur->data.defectPercent < minNode->data.defectPercent)
        {
            minNode = cur;
        }
        cur = cur->next;
    }
    if (minNode == list.head)
    {
        cout << "Деталь с минимальным процентом брака уже находится в начале.\n";
    }
    if (minNode == list.tail)
    {
        list.tail = minNode->prev;
        list.tail->next = nullptr;
    }
    else
    {
        minNode->prev->next = minNode->next;
        minNode->next->prev = minNode->prev;
    }

    minNode->prev = nullptr;
    minNode->next = list.head;

    list.head->prev = minNode;
    list.head = minNode;
    cout << "Деталь с минимальным процентом брака " << "перемещена в начало.\n";
}

int main()
{
    setlocale(NULL, "Russian");
    int choice;
    do
    {
        cout << "1. Добавить элемент в начало\n";
        cout << "2. Добавить элемент в конец\n";
        cout << "3. Удалить первый элемент\n";
        cout << "4. Удалить последний элемент\n";
        cout << "5. Вывести список\n";
        cout << "6. Вывести список в обратном порядке\n";
        cout << "7. Найти элемент по ID\n";
        cout << "8. Удалить найденный элемент\n";
        cout << "9. Очистить список\n";
        cout << "10. Найти деталь с максимальным процентом брака\n";
        cout << "11. Удалить детали с браком выше заданного\n";
        cout << "12. Переместить деталь с минимальным процентом брака в начало\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            push_front();
            break;
        case 2:
            push_back();
            break;
        case 3:
            pop_front();
            break;
        case 4:
            pop_back();
            break;
        case 5:
            display_forward();
            break;
        case 6:
            display_backward();
            break;
        case 7:
            find();
            break;
        case 8:
            deleteNode();
            break;
        case 9:
            clear();
            break;
        case 10:
            findMaxDefect();
            break;
        case 11:
            deleteByDefect();
            break;
        case 12:
            moveMinToFront();
            break;
        case 0:
            clear();
            cout << "Выход.\n";
            break;
        default:
            cout << "Неверный пункт меню\n";
        }
    } 
    while (choice != 0);


}