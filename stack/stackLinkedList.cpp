#include <iostream>
#include <linked_list/linkedList.h>
#include <cassert>

using namespace std;

class Stack
{
private:
    LinkedList stack; // Vector to store elements of the stack
    int size;         // Current size of the stack

public:
    Stack() : stack{}, size{0} {}; // Constructor to initialize an empty stack

    // Method to push an item onto the top of the stack
    void push(const int &item)
    {
        stack.pushFront(item); // Add the item to the end of the vector
        size++;                // Increment the size of the stack
    };

    // Method to remove and return the item at the top of the stack
    int pop()
    {
        // Check if the stack is empty
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }

        // Get the item at the top of the stack
        int item = stack.topFront();
        // Remove the item from the stack
        stack.popFront();
        // Decrease the size of the stack
        size--;
        // Return the removed item
        return item;
    };

    // Method to return the item at the top of the stack without removing it
    int top()
    {
        // Check if the stack is empty
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }

        // Return the item at the top of the stack
        return stack.topFront();
    };

    // Method to check if the stack is empty
    bool isEmpty()
    {
        return size == 0;
    };

    // Method to return the current size of the stack
    int stackSize()
    {
        return size;
    };

    // Method to clear the stack, removing all elements
    void clear()
    {
        stack.clear(); // Remove all elements from the vector
        size = 0;      // Reset the size of the stack to zero
    };
};

int main()
{
    // Create an instance of the Stack class
    Stack stack;

    // Test 1: Push elements onto the stack and verify top and size
    stack.push(10);
    assert(stack.top() == 10);      // Verify top element
    assert(stack.stackSize() == 1); // Verify stack size

    stack.push(20);
    stack.push(30);
    assert(stack.top() == 30);      // Verify top element
    assert(stack.stackSize() == 3); // Verify stack size

    // Test 2: Pop elements from the stack and verify top and size
    assert(stack.pop() == 30);      // Verify popped element
    assert(stack.top() == 20);      // Verify top element after pop
    assert(stack.stackSize() == 2); // Verify stack size after pop

    stack.pop();
    stack.pop();
    assert(stack.isEmpty());        // Verify stack is empty
    assert(stack.stackSize() == 0); // Verify stack size after popping all elements

    // Test 3: Test exception handling for popping from an empty stack
    try
    {
        stack.pop();
        // If the pop operation did not throw an exception, the test failed
        assert(false && "Pop operation on empty stack did not throw exception");
    }
    catch (const std::out_of_range &e)
    {
        // Pop operation on empty stack should throw out_of_range exception
        // If exception caught, the test passed
        assert(true);
    }

    // Test 4: Test exception handling for top operation on an empty stack
    try
    {
        stack.top();
        // If the top operation did not throw an exception, the test failed
        assert(false && "Top operation on empty stack did not throw exception");
    }
    catch (const std::out_of_range &e)
    {
        // Top operation on empty stack should throw out_of_range exception
        // If exception caught, the test passed
        assert(true);
    }

    // Test 5: Test clearing the stack
    stack.push(100);
    stack.push(200);
    stack.clear();
    assert(stack.isEmpty());        // Verify stack is empty after clearing
    assert(stack.stackSize() == 0); // Verify stack size is zero after clearing

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}