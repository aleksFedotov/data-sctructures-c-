#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
class Stack
{
private:
    std::vector<T> stack; // Vector to store elements of the stack
    int size;             // Current size of the stack

public:
    Stack() : stack{}, size{0} {}; // Constructor to initialize an empty stack

    // Method to push an item onto the top of the stack
    void push(const T &item)
    {
        stack.push_back(item); // Add the item to the end of the vector
        size++;                // Increment the size of the stack
    };

    // Method to remove and return the item at the top of the stack
    T pop()
    {
        // Check if the stack is empty
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }

        // Get the item at the top of the stack
        T item = stack.back();
        // Remove the item from the stack
        stack.pop_back();
        // Decrease the size of the stack
        size--;
        // Return the removed item
        return item;
    };

    // Method to return the item at the top of the stack without removing it
    T top()
    {
        // Check if the stack is empty
        if (isEmpty())
        {
            throw std::out_of_range("Stack is empty");
        }

        // Return the item at the top of the stack
        return stack.back();
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

    // Destructor to deallocate memory when the list is destroyed
    ~Stack();
};

int main()
{
    // Test Stack with integers
    Stack<int> intStack;

    // Push integers onto the stack
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Assertion tests
    int size = intStack.stackSize();
    assert(size == 3); // Check size after pushing elements

    // Test pop and top operations
    assert(intStack.top() == 30); // Check top element
    assert(intStack.pop() == 30); // Check pop result
    size = intStack.stackSize();
    assert(size == 2); // Check size after popping

    // Clear the stack
    intStack.clear();
    size = intStack.stackSize();
    assert(size == 0); // Check size after clearing

    // Test Stack with strings
    Stack<std::string> stringStack;

    // Push strings onto the stack
    stringStack.push("Hello");
    stringStack.push("World");

    // Assertion tests
    size = stringStack.stackSize();
    assert(size == 2); // Check size after pushing elements

    // Test pop and top operations
    assert(stringStack.top() == "World"); // Check top element
    assert(stringStack.pop() == "World"); // Check pop result
    size = stringStack.stackSize();
    assert(size == 1); // Check size after popping

    // Clear the stack
    stringStack.clear();
    size = stringStack.stackSize();
    assert(size == 0); // Check size after clearing

    // All tests passed
    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}