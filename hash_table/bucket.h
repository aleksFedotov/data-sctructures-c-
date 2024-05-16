#ifndef BUCKET_H
#define BUCKET_H

#include <iostream>
#include <stdexcept> 

template <typename T, typename U>
class Node
{
public:
    T key;             // Key of the node
    U value;           // Value associated with the key
    Node *next;        // Pointer to the next node
    Node *prev;        // Pointer to the previous node

    // Constructors
    Node() : key{}, value{}, next{nullptr}, prev{nullptr} {};
    Node(const T &keyA, const U &valueA) : key{keyA}, value{valueA}, next{nullptr}, prev{nullptr} {};
};

template <typename T, typename U>
class Bucket
{
private:
    int size;          // Size of the linked list



public:
    Node<T, U> *head;  // Pointer to the head of the linked list
    Node<T, U> *tail;  // Pointer to the tail of the linked list
    // Constructor
    Bucket() : head{nullptr}, tail{nullptr}, size{0} {};

    // Method to push a key-value pair into the linked list
    void push(const T &keyA, const U &valueA);

    // Method to get a node with a specific key
    Node<T, U> *get(const T &keyA);

    // Method to remove a node with a specific key
    bool remove(const T &key);
    // Method to check if the linked list is empty
    bool empty();
    ~Bucket();
};

// Method definitions

template <typename T, typename U>
void Bucket<T, U>::push(const T &keyA, const U &valueA)
{   

   
    // Check if the node with the given key already exists
    Node<T, U> *existedNode = get(keyA);

    if (existedNode != nullptr)
    {
        // If the node exists, update its value
        existedNode->value = valueA;
    }
    else
    {
        // If the node doesn't exist, create a new node
        Node<T, U> *newNode = new Node(keyA, valueA);

        // Check if the list is empty
        if (head == nullptr)
        {
            // If the list is empty, the new node becomes both head and tail
            head = newNode;
            tail = newNode;
        }
        else
        {
            // If the list is not empty, append the new node to the end
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        // Increment the size of the linked list
        size++;
    }
}

template <typename T, typename U>
bool Bucket<T, U>::empty()
{
    return size == 0;
}

template <typename T, typename U>
Node<T, U> *Bucket<T, U>::get(const T &keyA)
{
    // Traverse the linked list to find a node with the specified key
    Node<T, U> *currNode = head;
    while (currNode)
    {
        if (currNode->key == keyA)
        {
            // If found, return the node
            return currNode;
        }
        // Move to the next node
        currNode = currNode->next;
    }

    // If not found, return nullptr
    return nullptr;
}

template <typename T, typename U>
bool Bucket<T, U>::remove(const T &keyA)
{
    // Get the node to delete
    Node<T, U> *nodeToDelete = get(keyA);

    // Check if the node exists or the list is empty
    if (nodeToDelete == nullptr || empty())
    {
        // Node not found or list is empty, so no action needed
        return false;
    }

    // Check if the node to delete is the head
    if (nodeToDelete == head)
    {
        head = head->next;
        // Check if the new head is not nullptr
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
    }
    // Check if the node to delete is the tail
    else if (nodeToDelete == tail)
    {
        tail = tail->prev;
        // Check if the new tail is not nullptr
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
    }
    else
    {
        // Node to delete is neither head nor tail
        Node<T, U> *prevNode = nodeToDelete->prev;
        Node<T, U> *nextNode = nodeToDelete->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Delete the node and decrement the size of the linked list
    delete nodeToDelete;
    size--;

    return true;
}


template <typename T, typename U>
Bucket<T,U>::~Bucket() {
    while (head != nullptr) {
            Node<T, U>* temp = head;
            head = head->next;
            delete temp;
        }

}
#endif // BUCKET_H

