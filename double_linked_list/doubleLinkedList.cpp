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
    int length;

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
        length = 0;
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

    int size();
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
    return length == 0;
}

void DoubleLinkedList::pushFront(int value)
{

    Node *newNode = new Node(value);

    if (this->empty())
    {
        head = tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    length++;
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
        length--;
    }

    return;
}

void DoubleLinkedList::pushBack(int value)

{
    Node *newNode = new Node(value);

    if (this->empty())
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    length++;
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

    if (length == 1)
    {
        delete head;
        head = tail = nullptr;
        length = 0;
        return;
    }

    Node *nodeToDelete = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete nodeToDelete;
    length--;
    return;
}

bool DoubleLinkedList::find(int value)
{
    Node *currentNode = head;
    while (currentNode != nullptr)
    {
        if (currentNode->data == value)
        {
            return true;
        }

        currentNode = currentNode->next;
    }

    return false;
}

void DoubleLinkedList::insert(int value, int index)
{
    if (index == 0)
    {
        this->pushFront(value);
        length++;
        return;
    }

    if (index > length)
    {
        this->pushBack(value);
        length++;
        return;
    }

    if (index < 0)
    {
        throw out_of_range("Index not found");
    }

    Node *leader = this->traverse(index - 1);
    Node *follower = leader->next;
    Node *newNode = new Node(value);
    leader->next = newNode;
    newNode->prev = leader;
    newNode->next = follower;
    follower->prev = newNode;

    return;
}

void DoubleLinkedList::remove(int index)
{
    if (index == 0)
    {
        this->popFront();
        return;
    }

    if (index == length - 1)
    {
        this->popBack();
        return;
    }

    if (index >= length || index < 0)
    {
        throw out_of_range("Index not found");
    }

    Node *prevNode = this->traverse(index - 1);
    Node *nodeToDelete = prevNode->next;
    Node *follower = nodeToDelete->next;
    prevNode->next = follower;
    follower->prev = prevNode;

    delete nodeToDelete;
    length--;
    return;
}

int DoubleLinkedList::size()
{
    return length;
}

int DoubleLinkedList::get(int index)
{
    return this->traverse(index)->data;
}

void DoubleLinkedList::clear()
{
    while (!this->empty())
    {
        this->popFront();
    }

    return;
}

DoubleLinkedList::~DoubleLinkedList()
{
    this->clear();
}

void DoubleLinkedList::print()
{
    cout << "List: ";
    Node *currentNode = head;
    while (currentNode != nullptr)
    {
        std::cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }

    cout << endl;
    return;
}

Node *DoubleLinkedList::traverse(int index)
{
    int count = 0;
    Node *currentNode = head;

    while (count != index)
    {
        currentNode = currentNode->next;
        count++;
    }

    return currentNode;
}