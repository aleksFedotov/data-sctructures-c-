#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

// Queue class template declaration
template <typename T>
class Queue
{
private:
    std::vector<T> container; // Vector to store elements of the queue
    int length;               // Length of the queue

public:
    // Constructor to initialize the queue
    Queue() : container{}, length{0} {};

    // Function to add an element to the back of the queue
    void enqueue(const T &item);

    // Function to remove and return the element from the front of the queue
    T dequeue();

    // Function to return the element at the front of the queue without removing it
    T peek();

    // Function to check if the queue is empty
    bool isEmpty();

    // Function to return the number of elements in the queue
    int size();

    // Function to clear all elements from the queue
    void clear();

    // Destructor
    ~Queue();
};

// Implementation of the enqueue function
template <typename T>
void Queue<T>::enqueue(const T &item)
{
    container.push_back(item); // Add item to the back of the queue
    length++;                  // Increment the length of the queue
}

// Implementation of the dequeue function
template <typename T>
T Queue<T>::dequeue()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty");
    }
    T item = container.front();         // Get the front element of the queue
    container.erase(container.begin()); // Remove the front element
    length--;                           // Decrement the length of the queue
    return item;                        // Return the removed element
}

// Implementation of the peek function
template <typename T>
T Queue<T>::peek()
{
    if (isEmpty())
    {
        throw std::out_of_range("Queue is empty");
    }
    return container.front(); // Return the element at the front of the queue
}

// Implementation of the isEmpty function
template <typename T>
bool Queue<T>::isEmpty()
{
    return length == 0; // Check if the queue is empty
}

// Implementation of the size function
template <typename T>
int Queue<T>::size()
{
    return length; // Return the length of the queue
}

// Implementation of the clear function
template <typename T>
void Queue<T>::clear()
{
    container.clear(); // Remove all elements from the queue
}

// Destructor
template <typename T>
Queue<T>::~Queue()
{
    // Destructor implementation (if necessary)
}

#endif // QUEUE_H

// Main function for testing the Queue class
int main()
{
    // Test Queue with integers
    Queue<int> intQueue;

    // Enqueue integers onto the Queue
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);

    // Assertion tests
    assert(intQueue.size() == 3); // Check size after enqueue elements

    // Test dequeue and peek operations
    assert(intQueue.peek() == 10);    // Check peek element
    assert(intQueue.dequeue() == 10); // Check dequeue result
    assert(intQueue.size() == 2);     // Check size after dequeue

    // Clear the Queue
    intQueue.clear();
    assert(intQueue.size() == 0); // Check size after clearing

    // Test Queue with strings
    Queue<std::string> stringQueue;

    // Push strings onto the Queue
    stringQueue.enqueue("Hello");
    stringQueue.enqueue("World");

    // Assertion tests
    assert(stringQueue.size() == 2); // Check size after enqueue elements

    // Test dequeue and peek operations
    assert(stringQueue.peek() == "Hello");    // Check top element
    assert(stringQueue.dequeue() == "Hello"); // Check pop result
    assert(stringQueue.size() == 1);          // Check size after popping

    // Clear the Queue
    stringQueue.clear();
    assert(stringQueue.size() == 0); // Check size after clearing

    // All tests passed
    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}
