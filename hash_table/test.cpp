#include <iostream>
#include <cassert>
#include "hashTable.h"


using namespace std;


// Function to run tests for the HashTable class
void runTests() {
    // Test case 1: Insertion and retrieval
    HashTable<int> hashTable;
    hashTable.set("key1", 10);
    hashTable.set("key2", 20);
    hashTable.set("key3", 30);
    assert(hashTable.get("key1") == 10);
    assert(hashTable.get("key2") == 20);
    assert(hashTable.get("key3") == 30);

    // Test case 2: Removal
    hashTable.remove("key2");
    
    assert(hashTable.get("key2") == 0); // Removed, should return default value (0)

    // Test case 3: Check if key exists
    assert(hashTable.has("key1") == true);
    assert(hashTable.has("key2") == false); // Removed, should return false

    // Test case 4: Resize
    for (int i = 0; i < 150; ++i) {
        hashTable.set("key" + to_string(i), i * 10);
    }
    assert(hashTable.get("key100") == 1000);

    
}

int main() {
    runTests(); // Run the tests
    cout << "All tests passed successfully!" << endl;
    return 0;
}