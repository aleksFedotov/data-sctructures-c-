#ifndef HASH_TABLE_LINKED_LIST
#define HASH_TABLE_LINKED_LIST

#include <iostream>

template <typename T, typename U>
class Node
{
public:
    T key;
    U value;
    Node *next;
    Node *prev;

    Node() : key{}, value{}, next{nullptr} {};
    Node(const T &keyA, const U &valueA) : key{keyA}, value{valueA}, next{nullptr} {};
};

template <typename T, typename U>
class HashTableLinkedList
{
private:
    Node<T, U> *head;
    Node<T, U> *tail;
    int size;
    bool empty();

public:
    HashTableLinkedList() : head{nullptr}, tail{nullptr}, size{0} {};

    void push(const T &keyA, const U &valueA);
    Node<T, U> *get(const T &keyA);
    void remove(const T &key)
};

template <typename T, typename U>

void HashTableLinkedList<T, U>::push(const T &keyA, const U &valueA)
{
    Node<T, U> *existedNode = get(&keyA);

    if (existedNode != nullptr)
    {
        existedNode->value = valueA;
    }
    else
    {
        Node<T, U> *newNode = new Node(keyA, valueA);

        if (!empty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {

            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;

        return;
    }
}

template <typename T, typename U>
bool HashTableLinkedList<T, U>::empty()
{
    return size == = 0;
}

template <typename T, typename U>
Node<T, U> *HashTableLinkedList<T, U>::get(const T &keyA)
{
    Node<T, U> *currNode = head;
    while (currNode)
    {
        if (currNode->key == keyA)
        {
            return currNode;
        }
    }

    return nullptr;
}

template <typename T, typename U>

void HashTableLinkedList<T, U>::remove(const T &keyA)
{
    Node<T, U> *nodeToDelete = get(keyA);
    if (nodeToDelete == nullptr || empty())
    {
        return;
    }
    if (nodeToDelete == head)
    {
        nodeToDelete = head;
        head = head->next;
        head->prev = nullptr;
    }
    else if (nodeToDelete == tail)
    {
        nodeToDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
    }
    else
    {
        Node<T, U> *prevNode = nodeToDelete->prev;
        Node<T, U> *nextNode = nodeToDelete->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    delete nodeToDelete;
    size--;
    return;
}

#endif HASH_TABLE_LINKED_LIST
