#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <stdexcept>
#include "bucket.h" // Include the definition of the Bucket class
#include <vector>
#include <string>

using namespace std;

// Template declaration for the HashTable class
template <typename U>
class HashTable {
private:
    size_t capacity = 100; // Default size of the hash table
    int size = 0; // Current number of elements in the hash table
    const float loadFactorThreshold = 0.75;
    vector<Bucket<string, U>*> data; // Vector to store pointers to Buckets


    // Private method to calculate the hash value of a key
    int hashFunction(const string &key, const size_t &hashSize);
    void resize();

public:
    // Constructor to initialize the HashTable
    HashTable() : data(capacity, nullptr) {};

    // Method to check if a key exists in the HashTable
    bool has(const string &key);

    // Method to get the value associated with a key
    U get(const string &key);

    // Method to set a key-value pair in the HashTable
    void set(const string &key, const U &value);

    // Method to remove a key-value pair from the HashTable
    bool remove(const string &key);

    ~HashTable();


};

// Definition of the hashFunction method
template <typename U>
int HashTable<U>::hashFunction(const string &key, const  size_t &hashSize) {
    int hash = 0;
    // Simple hashing algorithm
    for (char ch : key) {
        hash = (hash * 31) + ch;
    }
      
    return std::abs(static_cast<long long>(hash)) % hashSize; // Ensure hash value is within the bounds of the hash table size
}

// Definition of the has method
template <typename U>
bool HashTable<U>::has(const string &key) {
    int hash = hashFunction(key, capacity); // Calculate the hash value of the key
   
    Bucket<string, U>* list = data[hash]; // Get the Bucket at the calculated hash index

    // Check if the Bucket exists and if the key exists in the Bucket
    if (list != nullptr && list->get(key) != nullptr) {
        return true; // Key exists
    }
    return false; // Key does not exist
}

// Definition of the get method
template <typename U>
U HashTable<U>::get(const string &key) {
    int hash = hashFunction(key, capacity); // Calculate the hash value of the key
    
    Bucket<string, U>* list = data[hash]; // Get the Bucket at the calculated hash index
    
   
    if (list != nullptr) {
        
        Node<string, U>* node = list->get(key); // Get the Node containing the key-value pair
        if (node != nullptr) {
            return node->value; // Return the value associated with the key
        }
    }
    return U{}; // Return default value if key is not found
}

// Definition of the set method
template <typename U>
void HashTable<U>::set(const string &key, const U &value) {
    int hash = hashFunction(key, capacity); // Calculate the hash value of the key
   
    Bucket<string, U>* &list = data[hash]; // Get the Bucket at the calculated hash index
      
    if (list == nullptr) {
         // If Bucket does not exist, create a new Bucket and add key-value pair
        list = new Bucket<string, U>();
        size++;
       
    } 
    list->push(key, value); // Add key-value pair to the Bucket

    if(size >= static_cast<int>(capacity * loadFactorThreshold)) {
        resize(); // Resize the hash table if load factor exceeds the threshold
    }

   
}

// Definition of the remove method
template <typename U>
bool HashTable<U>::remove(const string &key) {
    int hash = hashFunction(key, capacity); // Calculate the hash value of the key
 

    Bucket<string, U>* list = data[hash]; // Get the Bucket at the calculated hash index
  
    
    if (list != nullptr) {
        bool isDeleted = list->remove(key); // Remove the key-value pair from the Bucket
        if (list->empty()) {
            data[hash] = nullptr;
            delete list; // Delete the Bucket if it becomes empty after removal
        }
        return isDeleted; // Return true if removal was successful, false otherwise
    }
    return false; // Return false if Bucket does not exist
}

// Definition of the resize method
template <typename U>
void HashTable<U>::resize() {
  
    // Calculate the new capacity as double the current capacity
    size_t newCapacity = capacity * 2;
    
    // Create a new vector to store pointers to Buckets with the new capacity
    vector<Bucket<string, U>*> newData(newCapacity, nullptr);
    
    // Iterate through the current data vector
    for (size_t i = 0; i < capacity; ++i) {
        // Get the Bucket at index i
        Bucket<string, U>* bucket = data[i];
        
        // Check if the Bucket is not null
        if (bucket != nullptr) {
            // Get the head of the Bucket's linked list
            Node<string, U>* currentNode = bucket->head;
            
            // Iterate through the linked list
            while (currentNode != nullptr) {
                // Calculate the new hash for the current key using the new capacity
                int hash = hashFunction(currentNode->key, newCapacity);
                
                // Ensure the hash is within the bounds of the new capacity
                if (hash < newCapacity) { // Boundary check
                    // Get the Bucket at the new hash index
                    Bucket<string, U>* newBucket = newData[hash];
                    
                    // If the Bucket is null, create a new Bucket
                    if (newBucket == nullptr) {
                        newBucket = new Bucket<string, U>();
                        newData[hash] = newBucket;
                    }
                    
                    // Push the key-value pair to the new Bucket
                    newBucket->push(currentNode->key, currentNode->value);
                }
                
                // Move to the next node in the linked list
                currentNode = currentNode->next;
            }
        }
    }
    
    // Update the capacity to the new capacity
    capacity = newCapacity;

    // Deallocate memory from the old data vector
    for (size_t i = 0; i < capacity / 2; ++i) {
        delete data[i];
    }

    // Update the data vector to point to the new data
    data = newData;
}

template < typename U>
HashTable<U>::~HashTable() {
     for (size_t i = 0; i < capacity / 2; ++i) {
        delete data[i];
    }


}

#endif // HASH_TABLE_H




