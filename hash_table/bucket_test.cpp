
#include <cassert>
#include "bucket.h"

using namespace std;

void testBucket() {
    // Test case 1: Insertion and retrieval
    Bucket<string, int> bucket;
    bucket.push("key1", 10);
    bucket.push("key2", 20);
    bucket.push("key3", 30);
    assert(bucket.get("key1")->value == 10);
    assert(bucket.get("key2")->value == 20);
    assert(bucket.get("key3")->value == 30);

    // Test case 2: Updating existing value
    bucket.push("key1", 50);
    assert(bucket.get("key1")->value == 50);

    // Test case 3: Removal
    assert(bucket.remove("key2") == true);
    assert(bucket.get("key2") == nullptr); // Removed, should return nullptr
    assert(bucket.remove("key4") == false); // Not existing key, should return false

    // Test case 4: Empty check
    assert(bucket.empty() == false); // Not empty
    bucket.remove("key1");
    bucket.remove("key3");
    assert(bucket.empty() == true); // Empty after removals
}

int main() {
    testBucket(); // Run the tests
    cout << "All tests passed successfully!" << endl;
    return 0;
}