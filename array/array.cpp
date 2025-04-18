#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <memory>

/**
 * @brief Dynamic array implementation with resizing capabilities
 * 
 * This class provides a dynamic array that automatically resizes
 * when elements are added or removed. It includes common array operations
 * and demonstrates both direct access and loop-based access methods.
 */
template <typename T>
class Array {
private:
    // Using unique_ptr for automatic memory management
    std::unique_ptr<T[]> array;
    size_t size;      // Total allocated capacity
    size_t length = 0; // Current number of elements

    /**
     * @brief Resizes the array to a new capacity
     * @param newSize The new capacity to allocate
     */
    void resize(size_t newSize);
    
    /**
     * @brief Attempts to shrink the array if it's significantly empty
     * Called after removing elements to reduce memory usage
     */
    void tryShrink();

public:
    /**
     * @brief Iterator class for range-based for loop support
     * Allows using the array with modern C++ constructs
     */
    class iterator {
    private:
        T* ptr;
    public:
        explicit iterator(T* ptr) : ptr(ptr) {}
        iterator& operator++() { ++ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr; return tmp; }
        T& operator*() const { return *ptr; }
        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    // Iterator support for range-based for loops
    iterator begin() { return iterator(array.get()); }
    iterator end() { return iterator(array.get() + length); }

    /**
     * @brief Constructs an array with optional initial capacity
     * @param size Initial capacity of the array (default: 10)
     */
    explicit Array(size_t size = 10) : array(new T[size]), size(size), length(0) {}
    
    // Rule of five implementation for proper resource management
    
    /**
     * @brief Destructor - handled automatically by unique_ptr
     */
    ~Array() = default;
    
    /**
     * @brief Copy constructor - creates a deep copy
     * @param other Array to copy from
     */
    Array(const Array& other) : array(new T[other.size]), size(other.size), length(other.length) {
        // Deep copy all elements
        for (size_t i = 0; i < length; i++) {
            array[i] = other.array[i];
        }
    }
    
    /**
     * @brief Copy assignment operator - creates a deep copy with self-assignment check
     * @param other Array to copy from
     * @return Reference to this array
     */
    Array& operator=(const Array& other) {
        if (this != &other) {
            // Create new array and copy elements before replacing current array
            std::unique_ptr<T[]> newArray(new T[other.size]);
            for (size_t i = 0; i < other.length; i++) {
                newArray[i] = other.array[i];
            }
            array = std::move(newArray);
            size = other.size;
            length = other.length;
        }
        return *this;
    }
    
    /**
     * @brief Move constructor - transfers ownership efficiently
     * @param other Array to move from
     */
    Array(Array&& other) noexcept
        : array(std::move(other.array)), size(other.size), length(other.length) {
        // Reset the source object
        other.size = 0;
        other.length = 0;
    }
    
    /**
     * @brief Move assignment operator - transfers ownership efficiently
     * @param other Array to move from
     * @return Reference to this array
     */
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            array = std::move(other.array);
            size = other.size;
            length = other.length;
            // Reset the source object
            other.size = 0;
            other.length = 0;
        }
        return *this;
    }

    /**
     * @brief Access element at specified index (with bounds checking)
     * @param index Index of the element to access
     * @return Reference to the element
     * @throws std::out_of_range if index is out of bounds
     */
    T& operator[](size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    /**
     * @brief Access element at specified index (const version)
     * @param index Index of the element to access
     * @return Const reference to the element
     * @throws std::out_of_range if index is out of bounds
     */
    const T& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    // Core functionality
    
    /**
     * @brief Displays the contents of the array
     * Prints all elements in a readable format
     */
    void display() const;
    
    /**
     * @brief Adds an element to the end of the array
     * @param value Value to add
     * Resizes the array if necessary
     */
    void append(const T& value);
    
    /**
     * @brief Inserts an element at the specified index
     * @param index Position to insert at
     * @param value Value to insert
     * @throws std::out_of_range if index is out of bounds
     * Shifts subsequent elements right and resizes if necessary
     */
    void insert(size_t index, const T& value);
    
    /**
     * @brief Removes the last element from the array
     * @throws std::out_of_range if array is empty
     * Decreases length and may shrink the array
     */
    void pop();
    
    /**
     * @brief Deletes an element at the specified index
     * @param index Index of element to delete
     * @throws std::out_of_range if index is out of bounds
     * Shifts subsequent elements left and may shrink the array
     */
    void delete_item(size_t index);
    
    /**
     * @brief Searches for a value using linear search
     * @param value Value to find
     * @return Index of the value or -1 if not found
     * Time complexity: O(n)
     */
    size_t search(const T& value) const;
    
    /**
     * @brief Searches for a value using binary search
     * @param value Value to find
     * @return Index of the value or -1 if not found
     * @note Array must be sorted before calling this method
     * Time complexity: O(log n)
     */
    size_t binary_search(const T& value) const;
    
    /**
     * @brief Searches for a value using binary search with custom comparator
     * @param value Value to find
     * @param comp Custom comparison function
     * @return Index of the value or -1 if not found
     * @note Array must be sorted according to comp before calling
     * Time complexity: O(log n)
     */
    template <typename Compare>
    size_t binary_search(const T& value, Compare comp) const;
    
    /**
     * @brief Gets element at the specified index (direct access)
     * @param index Index of the element
     * @return Reference to the element
     * @throws std::out_of_range if index is out of bounds
     * Time complexity: O(1)
     */
    T& get(size_t index);
    
    /**
     * @brief Gets element at the specified index (const version)
     * @param index Index of the element
     * @return Const reference to the element
     * @throws std::out_of_range if index is out of bounds
     * Time complexity: O(1)
     */
    const T& get(size_t index) const;
    
    /**
     * @brief Gets element using loop-based access (for educational purposes)
     * @param index Index of the element
     * @return Copy of the element
     * @throws std::out_of_range if index is out of bounds
     * Time complexity: O(n) - demonstrates inefficiency compared to direct access
     */
    T get_with_loop(size_t index) const;
    
    /**
     * @brief Sets element at specified index (direct access)
     * @param index Index of the element
     * @param value New value to set
     * @throws std::out_of_range if index is out of bounds
     * Time complexity: O(1)
     */
    void set(size_t index, const T& value);
    
    /**
     * @brief Sets element using loop-based access (for educational purposes)
     * @param index Index of the element
     * @param value New value to set
     * @throws std::out_of_range if index is out of bounds
     * Time complexity: O(n) - demonstrates inefficiency compared to direct access
     */
    void set_with_loop(size_t index, const T& value);
    
    /**
     * @brief Finds the maximum value in the array
     * @return The maximum value
     * @throws std::logic_error if array is empty
     * Time complexity: O(n)
     */
    T max() const;
    
    /**
     * @brief Finds the minimum value in the array
     * @return The minimum value
     * @throws std::logic_error if array is empty
     * Time complexity: O(n)
     */
    T min() const;
    
    /**
     * @brief Reverses the order of elements in-place
     * Time complexity: O(n)
     */
    void reverse();
    
    /**
     * @brief Shifts all elements right by one position
     * First position becomes default value, last element is lost
     * @throws std::logic_error if array is empty
     * Time complexity: O(n)
     */
    void shift_right();
    
    /**
     * @brief Shifts all elements left by one position
     * Last position becomes default value, first element is lost
     * @throws std::logic_error if array is empty
     * Time complexity: O(n)
     */
    void shift_left();
    
    /**
     * @brief Rotates all elements right by one position
     * Last element moves to first position
     * @throws std::logic_error if array is empty
     * Time complexity: O(n)
     */
    void rotate_right();
    
    /**
     * @brief Rotates all elements left by one position
     * First element moves to last position
     * @throws std::logic_error if array is empty
     * Time complexity: O(n)
     */
    void rotate_left();
    
    // Capacity functions
    
    /**
     * @brief Returns the current allocated capacity
     * @return Total capacity of the array
     */
    size_t capacity() const { return size; }
    
    /**
     * @brief Returns the current number of elements
     * @return Number of elements in the array
     */
    size_t get_length() const { return length; }
    
    /**
     * @brief Checks if the array is empty
     * @return True if no elements, false otherwise
     */
    bool is_empty() const { return length == 0; }
    
    /**
     * @brief Removes all elements from the array
     * May shrink capacity if appropriate
     */
    void clear() { length = 0; tryShrink(); }
};

/**
 * @brief Resizes the array to a new capacity
 * 
 * Creates a new array of the specified size and moves all existing elements.
 * The old array is automatically deleted when the unique_ptr is reassigned.
 * 
 * @param newSize The new capacity to allocate
 */
template <typename T>
void Array<T>::resize(size_t newSize) {
    // Create new array with new size
    std::unique_ptr<T[]> newArray(new T[newSize]);
    
    // Move existing elements to new array
    for (size_t i = 0; i < length; i++) {
        newArray[i] = std::move(array[i]);
    }
    
    // Replace old array with new one (old array automatically deleted)
    array = std::move(newArray);
    size = newSize;
}

/**
 * @brief Attempts to shrink the array if it's significantly empty
 * 
 * Reduces memory usage when the array is mostly empty.
 * Only shrinks when array is 25% full or less and above minimum size.
 */
template <typename T>
void Array<T>::tryShrink() {
    // Shrink when array is 1/4 full to avoid thrashing
    // Also ensure we don't shrink very small arrays
    if (length > 0 && length <= size / 4 && size > 10) {
        resize(size / 2);
    }
}

/**
 * @brief Displays the contents of the array
 * 
 * Prints all elements in a readable format with commas between elements.
 */
template <typename T>
void Array<T>::display() const {
    std::cout << "[ ";
    for (size_t i = 0; i < length; i++) {
        std::cout << array[i];
        if (i != length - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

/**
 * @brief Adds an element to the end of the array
 * 
 * Increases length by 1 and resizes if necessary.
 * 
 * @param value Value to add
 */
template <typename T>
void Array<T>::append(const T& value) {
    // Double capacity if full
    if (length >= size) {
        resize(size == 0 ? 1 : size * 2);
    }
    // Add new element and increment length
    array[length++] = value;
}

/**
 * @brief Inserts an element at the specified index
 * 
 * Shifts all elements after the index one position right.
 * 
 * @param index Position to insert at
 * @param value Value to insert
 * @throws std::out_of_range if index is greater than length
 */
template <typename T>
void Array<T>::insert(size_t index, const T& value) {
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    
    // Double capacity if full
    if (length >= size) {
        resize(size == 0 ? 1 : size * 2);
    }
    
    // Shift elements to make space
    for (size_t i = length; i > index; i--) {
        array[i] = std::move(array[i - 1]);
    }
    
    // Insert new element and increment length
    array[index] = value;
    ++length;
}

/**
 * @brief Removes the last element from the array
 * 
 * Decreases length by 1 but doesn't actually modify the element.
 * May shrink the array if it becomes too empty.
 * 
 * @throws std::out_of_range if array is empty
 */
template <typename T>
void Array<T>::pop() {
    if (length == 0) {
        throw std::out_of_range("Array is empty");
    }
    // Just decrease the length - no need to modify the element
    --length;
    // Check if we should shrink the array
    tryShrink();
}

/**
 * @brief Deletes an element at the specified index
 * 
 * Shifts all elements after the index one position left.
 * 
 * @param index Index of element to delete
 * @throws std::out_of_range if index is out of bounds
 */
template <typename T>
void Array<T>::delete_item(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    
    // Shift elements to fill the gap
    for (size_t i = index; i < length - 1; i++) {
        array[i] = std::move(array[i + 1]);
    }
    
    // Decrease length and possibly shrink array
    --length;
    tryShrink();
}

/**
 * @brief Searches for a value using linear search
 * 
 * Examines each element sequentially until the value is found.
 * 
 * @param value Value to find
 * @return Index of the value or -1 if not found
 */
template <typename T>
size_t Array<T>::search(const T& value) const {
    // Check each element sequentially
    for (size_t i = 0; i < length; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    
    // Not found
    return static_cast<size_t>(-1);
}

/**
 * @brief Searches for a value using binary search
 * 
 * Assumes the array is sorted. Uses divide and conquer approach.
 * 
 * @param value Value to find
 * @return Index of the value or -1 if not found
 */
template <typename T>
size_t Array<T>::binary_search(const T& value) const {
    // Handle empty array case
    if (length == 0) {
        return static_cast<size_t>(-1);
    }
    
    size_t left = 0;
    size_t right = length - 1;
    
    // Binary search loop
    while (left <= right) {
        // Calculate middle index (avoiding overflow)
        size_t mid = left + (right - left) / 2;
        
        // Found the value
        if (array[mid] == value) {
            return mid;
        }
        
        // Adjust search bounds
        if (array[mid] < value) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }
    
    // Not found
    return static_cast<size_t>(-1);
}

/**
 * @brief Searches for a value using binary search with custom comparator
 * 
 * Allows custom comparison logic for complex types or special ordering.
 * 
 * @param value Value to find
 * @param comp Custom comparison function
 * @return Index of the value or -1 if not found
 */
template <typename T>
template <typename Compare>
size_t Array<T>::binary_search(const T& value, Compare comp) const {
    // Handle empty array case
    if (length == 0) {
        return static_cast<size_t>(-1);
    }
    
    size_t left = 0;
    size_t right = length - 1;
    
    // Binary search loop with custom comparator
    while (left <= right) {
        // Calculate middle index (avoiding overflow)
        size_t mid = left + (right - left) / 2;
        
        // Found the value - neither less than nor greater than
        if (!comp(array[mid], value) && !comp(value, array[mid])) {
            return mid;
        }
        
        // Adjust search bounds using custom comparator
        if (comp(array[mid], value)) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }
    
    // Not found
    return static_cast<size_t>(-1);
}

/**
 * @brief Gets element at the specified index (direct access)
 * 
 * Provides direct element access in O(1) time.
 * 
 * @param index Index of the element
 * @return Reference to the element
 * @throws std::out_of_range if index is out of bounds
 */
template <typename T>
T& Array<T>::get(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    
    // Direct array access - O(1)
    return array[index];
}

/**
 * @brief Gets element at the specified index (const version)
 * 
 * Provides direct element access in O(1) time.
 * 
 * @param index Index of the element
 * @return Const reference to the element
 * @throws std::out_of_range if index is out of bounds
 */
template <typename T>
const T& Array<T>::get(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    
    // Direct array access - O(1)
    return array[index];
}

/**
 * @brief Gets element using loop-based access (for educational purposes)
 * 
 * Demonstrates inefficient O(n) lookup by iterating through elements.
 * Included for educational purposes to compare with direct access.
 * 
 * @param index Index of the element
 * @return Copy of the element
 * @throws std::out_of_range if index is out of bounds
 */
template <typename T>
T Array<T>::get_with_loop(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
   
    // Loop through array to find element - O(n)
    for (size_t i = 0; i < length; i++) {
        if (i == index) {
            return array[i];
        }
    }

    throw std::logic_error("Unreachable code");
}

/**
 * @brief Sets element at specified index (direct access)
 * 
 * Provides direct element modification in O(1) time.
 * 
 * @param index Index of the element
 * @param value New value to set
 * @throws std::out_of_range if index is out of bounds
 */
template <typename T>
void Array<T>::set(size_t index, const T& value) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    // Direct array access - O(1)
    array[index] = value;
}

/**
 * @brief Sets element using loop-based access (for educational purposes)
 * 
 * Demonstrates inefficient O(n) modification by iterating through elements.
 * Included for educational purposes to compare with direct access.
 * 
 * @param index Index of the element
 * @param value New value to set
 * @throws std::out_of_range if index is out of bounds
 */
template <typename T>
void Array<T>::set_with_loop(size_t index, const T& value) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    
    // Loop through array to find and modify element - O(n)
    for (size_t i = 0; i < length; i++) {
        if (i == index) {
            array[i] = value;
            break;  // Exit loop once element is found and modified
        }
    }
}

/**
 * @brief Finds the maximum value in the array
 * 
 * Iterates through all elements to find the maximum.
 * 
 * @return The maximum value
 * @throws std::logic_error if array is empty
 */
template <typename T>
T Array<T>::max() const {
    if (length == 0) {
        throw std::logic_error("Cannot find max in empty array");
    }
    
    // Start with first element as current max
    T current_max = array[0];
    
    // Compare each element to current max
    for (size_t i = 1; i < length; i++) {
        if (array[i] > current_max) {
            current_max = array[i];
        }
    }
    
    return current_max;
}

/**
 * @brief Finds the minimum value in the array
 * 
 * Iterates through all elements to find the minimum.
 * 
 * @return The minimum value
 * @throws std::logic_error if array is empty
 */
template <typename T>
T Array<T>::min() const {
    if (length == 0) {
        throw std::logic_error("Cannot find min in empty array");
    }
    
    // Start with first element as current min
    T current_min = array[0];
    
    // Compare each element to current min
    for (size_t i = 1; i < length; i++) {
        if (array[i] < current_min) {
            current_min = array[i];
        }
    }
    
    return current_min;
}

/**
 * @brief Reverses the order of elements in-place
 * 
 * Swaps elements from both ends toward the middle.
 */
template <typename T>
void Array<T>::reverse() {
    // Nothing to do if array is empty or has only one element
    if (length <= 1) return;
    
    size_t left = 0;
    size_t right = length - 1;
    
    // Swap elements from both ends until we meet in the middle
    while (left < right) {
        std::swap(array[left], array[right]);
        left++;
        right--;
    }
}

/**
 * @brief Shifts all elements right by one position
 * 
 * First position becomes default value, last element is lost.
 * 
 * @throws std::logic_error if array is empty
 */
template <typename T>
void Array<T>::shift_right() {
    if (length == 0) {
        throw std::logic_error("Cannot shift an empty array");
    }
    
    // Start from the end and move each element right by one
    for (size_t i = length - 1; i > 0; --i) {
        array[i] = std::move(array[i - 1]);
    }
    
    // Set first element to default value
    array[0] = T{};
}

/**
 * @brief Shifts all elements left by one position
 * 
 * Last position becomes default value, first element is lost.
 * 
 * @throws std::logic_error if array is empty
 */
template <typename T>
void Array<T>::shift_left() {
    if (length == 0) {
        throw std::logic_error("Cannot shift an empty array");
    }
    
    // Start from the beginning and move each element left by one
    for (size_t i = 0; i < length - 1; ++i) {
        array[i] = std::move(array[i + 1]);
    }
    
    // Set last element to default value
    array[length - 1] = T{};
}

/**
 * @brief Rotates all elements right by one position
 * 
 * Last element moves to first position, all others shift right.
 * Unlike shift, no elements are lost or replaced with default values.
 * 
 * @throws std::logic_error if array is empty
 */
template <typename T>
void Array<T>::rotate_right() {
    if (length == 0) {
        throw std::logic_error("Cannot rotate an empty array");
    }
    
    // Save the last element
    T last = std::move(array[length - 1]);
    
    // Shift all elements right
    for (size_t i = length - 1; i > 0; --i) {
        array[i] = std::move(array[i - 1]);
    }
    
    // Place saved element at the beginning
    array[0] = std::move(last);
}

/**
 * @brief Rotates all elements left by one position
 * 
 * First element moves to last position, all others shift left.
 * Unlike shift, no elements are lost or replaced with default values.
 * 
 * @throws std::logic_error if array is empty
 */
template <typename T>
void Array<T>::rotate_left() {
    if (length == 0) {
        throw std::logic_error("Cannot rotate an empty array");
    }
    
    // Save the first element
    T first = std::move(array[0]);
    
    // Shift all elements left
    for (size_t i = 0; i < length - 1; ++i) {
        array[i] = std::move(array[i + 1]);
    }
    
    // Place saved element at the end
    array[length - 1] = std::move(first);
}



/**
 * @brief Example usage of the Array class
 */
// int main() {
//     Array<int> arr(5);
//     
//     // Add elements
//     arr.append(10);
//     arr.append(20);
//     arr.append(30);
//     
//     // Display array
//     arr.display();  // Output: [ 10, 20, 30 ]
//     
//     // Insert element
//     arr.insert(1, 15);
//     arr.display();  // Output: [ 10, 15, 20, 30 ]
//     
//     // Delete element
//     arr.delete_item(2);
//     arr.display();  // Output: [ 10, 15, 30 ]
//     
//     // Search
//     std::cout << "Search for 15: " << arr.search(15) << std::endl;  // Output: 1
//     
//     // Max and min
//     std::cout << "Max: " << arr.max() << std::endl;  // Output: 30
//     std::cout << "Min: " << arr.min() << std::endl;  // Output: 10
//     
//     // Reverse
//     arr.reverse();
//     arr.display();  // Output: [ 30, 15, 10 ]
//     
//     // Sort
//     arr.sort();
//     arr.display();  // Output: [ 10, 15, 30 ]
//     
//     // Rotate
//     arr.rotate_right();
//     arr.display();  // Output: [ 30, 10, 15 ]
//     
//     return 0;
// }