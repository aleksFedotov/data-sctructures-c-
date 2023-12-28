#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node()
    {
        data = 0;
        next = nullptr;
    }

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    };

    void pushFront(int);
    int topFront();
    void popFront();

    void pushBack(int);
    int topBack();
    void popBack();
};

void LinkedList::pushFront(int value)
{
    Node *newNode = new Node(value);

    if (head == nullptr)
    {
        head = newNode;
        size = 1;
        return;
    }

    newNode->next = head;
    head = newNode;
    size++;
}

int LinkedList::topFront()
{
    if (head == NULL)
    {
        cout << "No element at the front top" << endl;
        return 0;
    }

    return head->data;
}

void LinkedList::popFront()
{

    if (head != nullptr)

    {
        Node *prevHead = head;
        head = head->next;
        delete prevHead;
    }
    return;
}

void LinkedList::pushBack(int value)
{
    Node *newNode = new Node(value);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
        return;
    }

    if (tail != nullptr)
    {
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        tail = newNode;
        head->next = tail;
    }

    return;
}

int LinkedList::topBack()
{
    if (tail == nullptr)
    {
        cout << "No element at the back top" << endl;
        return 0;
    }

    return tail->data;
}

void LinkedList::popBack()
{

    Node *curentNode = head;

    if (head->next == nullptr)
    {
        head = nullptr;
        delete curentNode;
        return;
    }

    while (curentNode->next->next != nullptr)
    {

        curentNode = curentNode->next;
    }

    tail = curentNode;
    delete tail->next;

    tail->next = nullptr;
    return;
}

int main()
{
}