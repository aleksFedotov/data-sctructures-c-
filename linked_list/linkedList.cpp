#include <iostream>

using namespace std;

// Node class represents individual elements in the linked list
class Node
{
public:
    int data;
    Node *next;

    // Constructors
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

// LinkedList class represents a singly linked list
class LinkedList
{
private:
    Node *head;
    Node *tail;
    int size;

    // Private helper method to traverse to a specific index in the list
    Node *traverse(int);

public:
    // Constructor
    LinkedList()
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
    void erase();

    // Destructor to deallocate memory when the list is destroyed
    ~LinkedList();
};

// Method to add a new node at the front of the list
void LinkedList::pushFront(int value)
{
    Node *newNode = new Node(value);

    // If the list is empty, the new node becomes both head and tail
    if (this->empty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Otherwise, insert the new node at the front
        newNode->next = head;
        head = newNode;
    }

    size++;
    return;
}

// Method to get the value at the front of the list
int LinkedList::topFront()
{
    if (this->empty())
    {
        cout << "No element at the front top" << endl;
        return 0;
    }

    return head->data;
}

// Method to remove the node at the front of the list
void LinkedList::popFront()
{
    if (!this->empty())
    {
        Node *prevHead = head;
        head = head->next;
        delete prevHead;
        size--;
    }
    return;
}

// Method to add a new node at the back of the list
void LinkedList::pushBack(int value)
{
    Node *newNode = new Node(value);

    // If the list is empty, the new node becomes both head and tail
    if (this->empty())
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        // Otherwise, insert the new node at the back
        tail->next = newNode;
        tail = newNode;
    }

    size++;

    return;
}

// Method to get the value at the back of the list
int LinkedList::topBack()
{
    if (this->empty())
    {
        cout << "No element at the back top" << endl;
        return 0;
    }

    return tail->data;
}

// Method to remove the node at the back of the list
void LinkedList::popBack()
{
    // Check if the list is empty
    if (this->empty())
    {
        cout << "No element to pop from the back" << endl;
        return;
    }

    // If there's only one node in the list, remove it
    if (head->next == nullptr)
    {
        delete head;
        head = tail = nullptr;
        size = 0;
        return;
    }

    Node *currentNode = head;
    // Traverse to the second-to-last node
    while (currentNode->next->next != nullptr)
    {
        currentNode = currentNode->next;
    }

    // Update the tail and delete the last node
    tail = currentNode;
    delete tail->next;

    tail->next = nullptr;
    size--;
    return;
}

// Method to check if the list is empty
bool LinkedList::empty()
{
    return size == 0;
}

// Method to find a specific value in the list
bool LinkedList::find(int value)
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

// Method to insert a value at a specific index in the list
void LinkedList::insert(int value, int index)
{
    // If the index is at the front, call pushFront
    if (index == 0)
    {
        this->pushFront(value);
        return;
    }

    // If the index is at or beyond the end, call pushBack
    if (index > size)
    {
        this->pushBack(value);
        return;
    }

    // Traverse to the node before the specified index
    Node *leader = this->traverse(index - 1);
    Node *follower = leader->next;
    Node *newNode = new Node(value);

    // Insert the new node between leader and follower
    leader->next = newNode;
    newNode->next = follower;
    size++;
    return;
}

// Method to remove a node at a specific index in the list
void LinkedList::remove(int index)
{
    // If the index is at the front, call popFront
    if (index == 0)
    {
        this->popFront();
        return;
    }

    // If the index is at the end, call popBack
    if (index == size - 1)
    {
        this->popBack();
        return;
    }

    // If the index is beyond the end, print an error message
    if (index >= size || index < 0)
    {
        cout << "Index not found" << endl;
        return;
    }

    // Traverse to the node before the specified index
    Node *follower = traverse(index - 1);
    Node *nodeToDelete = follower->next;
    follower->next = nodeToDelete->next;

    // Delete the node at the specified index
    delete nodeToDelete;
    size--;
    return;
}
// Returns the current size of the linked list.
int LinkedList::getSize()
{
    return size;
}
// Method to retrieve the value at the specified index in the linked list.
int LinkedList::get(int index)

{
    // If the index is beyond the end, print an error message
    if (index >= size || index < 0)
    {
        cout << "Index not found" << endl;
        return -1;
    }
    return this->traverse(index)->data;
}

// Method  to reverse the order of nodes in the linked list.

void LinkedList::reverse()
{
    // Check if the list is empty or has only one node
    if (head == nullptr || size == 1)
    {
        return;
    }

    // Initialize pointers for traversal and reversal
    Node *first = head;
    Node *second = head->next;
    tail = first;

    // Iteratively reverse the direction of pointers between consecutive nodes
    while (second != nullptr)
    {
        // Temporary pointer to store the next node in the original order
        Node *temp = second->next;

        // Reverse the direction of the pointer between nodes
        second->next = first;

        // Move the pointers to the next nodes in the original order
        first = second;
        second = temp;
    }

    // Update the head and set the next pointer of the original head to nullptr
    head->next = nullptr;
    head = first;
}

// Method to removes all nodes from the list, leaving it empty.
void LinkedList::erase()
{
    // Delete all nodes in the list
    while (!this->empty())
        this->popFront();
    return;
}
// Private helper method to traverse to a specific index in the list
Node *LinkedList::traverse(int index)
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

// Destructor to deallocate memory when the list is destroyed
LinkedList::~LinkedList()
{
    this->erase();
}
