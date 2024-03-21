#ifndef QUEUE_DOUBLE_LINK_LIST
#define QUEUE_DOUBLE_LINK_LIST

#include <double_linked_list/doubleLinkedList.h> // Include the double linked list implementation
#include <iostream>
#include <cassert>
#include <stdexcept>

class QueueDoubleLinkedList
{
private:
    DoubleLinkedList container; // Underlying double linked list to store elements
    int length;                 // Variable to keep track of the number of elements in the queue

public:
    // Constructor
    QueueDoubleLinkedList() : container{}, length{0} {};

    // Method to add an item to the queue
    void enqueue(const int &item);

    // Method to remove and return the front item from the queue
    int dequeue();

    // Method to observe the front item of the queue without removing it
    int peek();

    // Method to check if the queue is empty
    bool isEmpty();

    // Method to clear the queue
    void clear();

    // Method to get the number of items in the queue
    int size();

    // Destructor
    ~QueueDoubleLinkedList();
};

// Implementation of the enqueue method
void QueueDoubleLinkedList::enqueue(const int &item)
{
    container.pushBack(item); // Add item to the back of the double linked list
    length++;                 // Increment the length of the queue
};

// Implementation of the dequeue method
int QueueDoubleLinkedList::dequeue()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty"); // Throw an exception if the queue is empty
    }
    int item = container.topBack(); // Retrieve the front item of the queue
    container.popBack();            // Remove the front item from the queue
    length--;                       // Decrement the length of the queue
    return item;                    // Return the removed item
};

// Implementation of the peek method
int QueueDoubleLinkedList::peek()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty"); // Throw an exception if the queue is empty
    }
    return container.topBack(); // Return the front item of the queue
};

// Implementation of the isEmpty method
bool QueueDoubleLinkedList::isEmpty()
{
    return length == 0; // Check if the length of the queue is zero
};

// Implementation of the clear method
void QueueDoubleLinkedList::clear()
{
    container.clear(); // Clear the underlying double linked list
};

// Implementation of the size method
int QueueDoubleLinkedList::size()
{
    return length; // Return the length of the queue
}

#endif // QUEUE_DOUBLE_LINK_LIST

// Test the QueueDoubleLinkedList class
int main()
{
    QueueDoubleLinkedList queue; // Create a queue object

    // Test enqueue, size, peek, and dequeue methods
    assert(queue.size() == 0);
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    assert(queue.size() == 3);
    assert(queue.peek() == 10);
    assert(queue.dequeue() == 10);
    assert(queue.dequeue() == 20);
    assert(queue.size() == 1);

    // Test isEmpty and clear methods
    assert(queue.isEmpty() == false);
    queue.clear();
    assert(queue.size() == 0);

    return 0;
};
