#include <iostream>
#include <cassert>
#include <string>
#include "array.cpp"  // Include your Array implementation

// Test counter
int tests_run = 0;
int tests_passed = 0;

// Helper macro to run a test and print result
#define RUN_TEST(test_name, test_code) \
    do { \
        std::cout << "Running test: " << test_name << "... "; \
        bool assertion_failed = false; \
        tests_run++; \
        try { \
            test_code; \
            tests_passed++; \
            std::cout << "PASSED" << std::endl; \
        } catch (const std::exception& e) { \
            std::cout << "FAILED - Exception: " << e.what() << std::endl; \
        } \
    } while (0)

// Helper function to create an array with sample data
template <typename T>
DynamicArray<T> createSampleArray(const std::initializer_list<T>& values) {
    DynamicArray<T> arr;
    for (const auto& val : values) {
        arr.append(val);
    }
    return arr;
}

// Test cases for Array class
void testConstructors() {
    // Default constructor
    RUN_TEST("Default Constructor", {
        DynamicArray<int> arr;
        assert(arr.capacity() == 10);
        assert(arr.get_length() == 0);
        assert(arr.is_empty());
    });
    
    // Custom size constructor
    RUN_TEST("Custom Size Constructor", {
        DynamicArray<int> arr(20);
        assert(arr.capacity() == 20);
        assert(arr.get_length() == 0);
        assert(arr.is_empty());
    });
}

void testAppendAndAccess() {
    RUN_TEST("Append and Access", {
        DynamicArray<int> arr;
        arr.append(10);
        arr.append(20);
        arr.append(30);
        
        assert(arr.get_length() == 3);
        assert(arr[0] == 10);
        assert(arr[1] == 20);
        assert(arr[2] == 30);
    });
    
    RUN_TEST("Auto Resize", {
        DynamicArray<int> arr(2);  // Start with small capacity
        for (int i = 0; i < 10; i++) {
            arr.append(i);
        }
        assert(arr.get_length() == 10);
        assert(arr.capacity() >= 10);
    });
}

void testInsert() {
    RUN_TEST("Insert at Middle", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.insert(1, 15);
        assert(arr.get_length() == 4);
        assert(arr[0] == 10);
        assert(arr[1] == 15);
        assert(arr[2] == 20);
        assert(arr[3] == 30);
    });
    
    RUN_TEST("Insert at Beginning", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.insert(0, 5);
        assert(arr.get_length() == 4);
        assert(arr[0] == 5);
        assert(arr[1] == 10);
    });
    
    RUN_TEST("Insert at End", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.insert(3, 40);
        assert(arr.get_length() == 4);
        assert(arr[3] == 40);
    });
}

void testRemoval() {
    RUN_TEST("Pop Last Element", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.pop();
        assert(arr.get_length() == 2);
        assert(arr[0] == 10);
        assert(arr[1] == 20);
    });
    
    RUN_TEST("Delete Middle Element", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30, 40});
        arr.delete_item(1);
        assert(arr.get_length() == 3);
        assert(arr[0] == 10);
        assert(arr[1] == 30);
        assert(arr[2] == 40);
    });
    
    RUN_TEST("Delete First Element", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.delete_item(0);
        assert(arr.get_length() == 2);
        assert(arr[0] == 20);
        assert(arr[1] == 30);
    });
    
    RUN_TEST("Delete Last Element", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.delete_item(2);
        assert(arr.get_length() == 2);
        assert(arr[0] == 10);
        assert(arr[1] == 20);
    });
    
    RUN_TEST("Clear Array", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.clear();
        assert(arr.get_length() == 0);
        assert(arr.is_empty());
    });
}

void testSearch() {
    RUN_TEST("Linear Search - Found", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30, 40});
        size_t result = arr.search(30);
        assert(result == 2);
    });
    
    RUN_TEST("Linear Search - Not Found", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        size_t result = arr.search(50);
        assert(result == static_cast<size_t>(-1));
    });
    
    RUN_TEST("Binary Search - Found", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30, 40, 50});
        size_t result = arr.binary_search(30);
        assert(result == 2);
    });
    
    RUN_TEST("Binary Search - Not Found", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30, 40, 50});
        size_t result = arr.binary_search(35);
        assert(result == static_cast<size_t>(-1));
    });
    
    RUN_TEST("Binary Search - Custom Comparator", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30, 40, 50});
        auto comp = [](int a, int b) { return a < b; };
        size_t result = arr.binary_search(30, comp);
        assert(result == 2);
    });
}

void testGetSet() {
    RUN_TEST("Get - Direct Access", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        assert(arr.get(1) == 20);
    });
    
    RUN_TEST("Get - Loop Access", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        assert(arr.get_with_loop(1) == 20);
    });
    
    RUN_TEST("Set - Direct Access", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.set(1, 25);
        assert(arr[1] == 25);
    });
    
    RUN_TEST("Set - Loop Access", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.set_with_loop(1, 25);
        assert(arr[1] == 25);
    });
}

void testMinMax() {
    RUN_TEST("Max Value", {
        DynamicArray<int> arr = createSampleArray<int>({30, 10, 50, 40, 20});
        assert(arr.max() == 50);
    });
    
    RUN_TEST("Min Value", {
        DynamicArray<int> arr = createSampleArray<int>({30, 10, 50, 40, 20});
        assert(arr.min() == 10);
    });
}

void testArrayManipulation() {
    RUN_TEST("Reverse Array", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30, 40});
        arr.reverse();
        assert(arr[0] == 40);
        assert(arr[1] == 30);
        assert(arr[2] == 20);
        assert(arr[3] == 10);
    });
    
    RUN_TEST("Shift Right", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.shift_right();
        assert(arr[0] == 0);  // Default constructed int
        assert(arr[1] == 10);
        assert(arr[2] == 20);
    });
    
    RUN_TEST("Shift Left", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.shift_left();
        assert(arr[0] == 20);
        assert(arr[1] == 30);
        assert(arr[2] == 0);  // Default constructed int
    });
    
    RUN_TEST("Rotate Right", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.rotate_right();
        assert(arr[0] == 30);
        assert(arr[1] == 10);
        assert(arr[2] == 20);
    });
    
    RUN_TEST("Rotate Left", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        arr.rotate_left();
        assert(arr[0] == 20);
        assert(arr[1] == 30);
        assert(arr[2] == 10);
    });
}

void testCopyMove() {
    RUN_TEST("Copy Constructor", {
        DynamicArray<int> arr1 = createSampleArray<int>({10, 20, 30});
        DynamicArray<int> arr2(arr1);
        
        // Modify original to test deep copy
        arr1.set(0, 99);
        
        assert(arr2.get_length() == 3);
        assert(arr2[0] == 10);  // Should remain unchanged
        assert(arr2[1] == 20);
        assert(arr2[2] == 30);
    });
    
    RUN_TEST("Copy Assignment", {
        DynamicArray<int> arr1 = createSampleArray<int>({10, 20, 30});
        DynamicArray<int> arr2;
        arr2 = arr1;
        
        // Modify original to test deep copy
        arr1.set(0, 99);
        
        assert(arr2.get_length() == 3);
        assert(arr2[0] == 10);  // Should remain unchanged
        assert(arr2[1] == 20);
        assert(arr2[2] == 30);
    });
    
    RUN_TEST("Move Constructor", {
        DynamicArray<int> arr1 = createSampleArray<int>({10, 20, 30});
        DynamicArray<int> arr2(std::move(arr1));
        
        assert(arr2.get_length() == 3);
        assert(arr2[0] == 10);
        assert(arr2[1] == 20);
        assert(arr2[2] == 30);
        assert(arr1.get_length() == 0);  // Original should be empty
    });
    
    RUN_TEST("Move Assignment", {
        DynamicArray<int> arr1 = createSampleArray<int>({10, 20, 30});
        DynamicArray<int> arr2;
        arr2 = std::move(arr1);
        
        assert(arr2.get_length() == 3);
        assert(arr2[0] == 10);
        assert(arr2[1] == 20);
        assert(arr2[2] == 30);
        assert(arr1.get_length() == 0);  // Original should be empty
    });
}

void testIterator() {
    RUN_TEST("Iterator - Range-Based For Loop", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        int sum = 0;
        for (const auto& item : arr) {
            sum += item;
        }
        assert(sum == 60);
    });
}

// Exception tests need special handling with assert
void testExceptions() {
    // Index out of range
    RUN_TEST("Exception - Index Out of Range", {
        DynamicArray<int> arr = createSampleArray<int>({10, 20, 30});
        bool exception_thrown = false;
        try {
            int val = arr[5];  // This should throw
        } catch (const std::out_of_range&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    });
    
    // Pop empty array
    RUN_TEST("Exception - Pop Empty Array", {
        DynamicArray<int> arr;
        bool exception_thrown = false;
        try {
            arr.pop();  // This should throw
        } catch (const std::out_of_range&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    });
    
    // Min on empty array
    RUN_TEST("Exception - Min Empty Array", {
        DynamicArray<int> arr;
        bool exception_thrown = false;
        try {
            arr.min();  // This should throw
        } catch (const std::logic_error&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    });
    
    // Max on empty array
    RUN_TEST("Exception - Max Empty Array", {
        DynamicArray<int> arr;
        bool exception_thrown = false;
        try {
            arr.max();  // This should throw
        } catch (const std::logic_error&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    });
}

int main() {
    // Enable abort() when assert fails, but display our message first
    // Comment out this line if you want the program to continue after assert failure
    // but note that this may lead to undefined behavior after a failed test
    std::cout << "Running Array class unit tests using cassert...\n" << std::endl;
    
    // Run all test categories
    testConstructors();
    testAppendAndAccess();
    testInsert();
    testRemoval();
    testSearch();
    testGetSet();
    testMinMax();
    testArrayManipulation();
    testCopyMove();
    testIterator();
    testExceptions();
    
    // Print summary
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "Tests run: " << tests_run << std::endl;
    std::cout << "Tests passed: " << tests_passed << std::endl;
    
    if (tests_passed == tests_run) {
        std::cout << "All tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << "Some tests failed!" << std::endl;
        return 1;
    }
}