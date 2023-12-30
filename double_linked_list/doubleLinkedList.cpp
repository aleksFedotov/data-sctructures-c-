#include <iostream>
#include <cassert>
#include <functional>

using namespace std;

// Node class represents individual elements in the linked list
class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    // Constructors
    Node() : data(0), next(nullptr), prev(nullptr) {}
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoubleLinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

    // Private helper method to traverse to a specific index in the list
    Node *traverse(int);
    Node *mergeSortedLists(Node *left, Node *right, function<bool(int, int)>);
    Node *mergeSort(Node *start, function<bool(int, int)> compareFunction);

public:
    // Constructor
    DoubleLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    };

    // Methods to manipulate the front of the list
    void pushFront(int);
    int topFront();
    void popFront();

    // Methods to manipulate the back of the list
    void pushBack(int);
    int topBack();
    void popBack();

    // Check if the list is empty
    bool empty();

    // Find a specific value in the list
    bool find(int);

    // Insert a value at a specific index
    void insert(int, int);

    // Remove a value at a specific index
    void remove(int);

    // Get size of a list

    int getSize();
    // Returns the value at the specified index.
    int get(int);

    // Reverses the order of nodes in the list.
    void reverse();

    // Removes all nodes from the list, leaving it empty.
    void clear();

    // Prints the values of all nodes in the list.

    void print();

    // Sorts the nodes based on their values.

    void sort(function<bool(int, int)> compareFunction);

    // Destructor to deallocate memory when the list is destroyed
    ~DoubleLinkedList();
};

bool DoubleLinkedList::empty()
{
    return size == 0;
}

void DoubleLinkedList::pushFront(int value)
{
    Node *newNode = new Node(value);

    if (this->empty())
    {
        head = newNode;
        tail = newNode;
        size = 1;
        return;
    }

    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size++;

    return;
}

int DoubleLinkedList::topFront()
{
    if (this->empty())
    {
        throw out_of_range("No element at the front top");
    }

    return head->data;
}

void DoubleLinkedList::popFront()
{
    if (this->empty())
    {
        throw out_of_range("No element to pop from the top");
    }
    else
    {
        Node *prevHead = head;
        head = head->next;
        head->prev = nullptr;
        delete prevHead;
        size--;
    }

    return;
}

void DoubleLinkedList::pushBack(int value)

{
    Node *newNode = new Node(value);
    if (this->empty())
    {
        head = newNode;
        tail = newNode;
        size = 1;
        return;
    }
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    size++;
    return;
}

int DoubleLinkedList::topBack()
{
    if (this->empty())
    {
        throw out_of_range("No element at the back top");
    }

    return tail->data;
}

void DoubleLinkedList::popBack()
{

    if (this->empty())
    {
        throw out_of_range("No element to pop from the back");
    }

    if (size == 1)
    {
        delete head;
        head = tail = nullptr;
        size = 0;
        return;
    }

    Node *currentNode = head;

    while (currentNode->next->next != nullptr)
    {
        currentNode = currentNode->next;
    }

    tail = currentNode;
    delete tail->next;
    tail->next = nullptr;

    size--;
    return;
}