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

    // Constructors
    Node() : data(0), next(nullptr) {}
    Node(int value) : data(value), next(nullptr) {}
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
    Node *mergeSortedLists(Node *left, Node *right, function<bool(int, int)>);
    Node *mergeSort(Node *start, function<bool(int, int)> compareFunction);

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
    void clear();

    // Prints the values of all nodes in the list.

    void print();

    // Sorts the nodes based on their values.

    void sort(function<bool(int, int)> compareFunction);

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
        throw out_of_range("No element at the front top");
    }

    return head->data;
}

// Method to remove the node at the front of the list
void LinkedList::popFront()

{
    if (this->empty())
    {
        throw out_of_range("No element to pop from the top");
    }
    else
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
        throw out_of_range("No element at the front top");
    }

    return tail->data;
}

// Method to remove the node at the back of the list
void LinkedList::popBack()
{
    // Check if the list is empty
    if (this->empty())
    {
        throw out_of_range("No element to pop from the top");
    }

    // If there's only one node in the list, remove it
    if (size == 1)
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
        throw out_of_range("Index not found");
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
        throw out_of_range("Index not found");
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
void LinkedList::clear()
{

    head = tail = nullptr;
    size = 0;
    return;
}
// Method to print the values of all nodes in the list.
void LinkedList::print()
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

// Method to sort nodes with comapre function
void LinkedList::sort(function<bool(int, int)> compareFunction = [](int a, int b)
                      { return a < b; })
{
    head = this->mergeSort(head, compareFunction);
}

// Private helper method to perform Merge Sort on the linked list with a custom compareFunction  function

Node *LinkedList::mergeSort(Node *start, function<bool(int, int)> compareFunction)
{

    // Base case: If the list is empty or has only one node, it's already sorted
    if (start == nullptr || start->next == nullptr)
    {
        return start;
    }

    // Find the middle of the list
    Node *slow = start;
    Node *fast = start->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the list into two halves
    Node *middle = slow->next;
    slow->next = nullptr;

    // Recursively sort the two halves
    Node *left = mergeSort(start, compareFunction);
    Node *right = mergeSort(middle, compareFunction);

    // Merge the sorted halves
    return mergeSortedLists(left, right, compareFunction);
}

// Private helper  to merge two sorted linked lists

Node *LinkedList::mergeSortedLists(Node *left, Node *right, function<bool(int, int)> compareFunction)
{
    Node *mergeList = nullptr;

    if (left == nullptr)
    {
        return right;
    }

    if (right == nullptr)
    {
        return left;
    }
    // Comapre  values of nodes and merge based on the custom Comapre  function
    if (compareFunction(left->data, right->data))
    {
        mergeList = left;
        mergeList->next = mergeSortedLists(left->next, right, compareFunction);
    }
    else
    {
        mergeList = right;
        mergeList->next = mergeSortedLists(left, right->next, compareFunction);
    }

    return mergeList;
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
    this->clear();
}

int main()
{
    // Test Case 1: Basic Operations
    LinkedList list;

    // Check if the list is initially empty
    assert(list.empty());
    assert(list.getSize() == 0);

    // Test pushFront
    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    assert(list.getSize() == 3);
    assert(list.topFront() == 3);

    // Test popFront
    list.popFront();
    assert(list.getSize() == 2);
    assert(list.topFront() == 2);

    // Test pushBack
    list.pushBack(4);
    assert(list.getSize() == 3);
    assert(list.topBack() == 4);

    // Test popBack

    list.popBack();
    assert(list.getSize() == 2);
    assert(list.topBack() == 1);

    // Test find
    assert(list.find(2));
    assert(!list.find(5));

    // Test insert
    list.insert(10, 1);
    assert(list.getSize() == 3);
    assert(list.get(1) == 10);

    // Test remove
    list.remove(1);
    assert(list.getSize() == 2);
    assert(list.get(1) != 10);

    // Test clear
    list.clear();
    assert(list.empty());
    assert(list.getSize() == 0);

    // Test Case 2: Sorting
    LinkedList list2;

    // Add elements to the list
    list2.pushBack(5);
    list2.pushBack(2);
    list2.pushBack(8);
    list2.pushBack(1);

    // Sort the list

    list2.sort();

    // Check if the list is sorted in ascending order
    assert(list2.get(0) == 1);
    assert(list2.get(1) == 2);
    assert(list2.get(2) == 5);
    assert(list2.get(3) == 8);

    // All assertions passed
    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}
