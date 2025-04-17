// TO DO
// search(x)
// binarySearch(x)
// get(index)
// set(index,x)
// max()/min()
// reverse()
// shift()/rotate()

#include <iostream>


using namespace std;


template <typename T>

class Array {
    private:
        T* array;
        size_t size;
        size_t length = 0;

        void resize(size_t newSize);
        void tryShrink();
    public:

        Array(size_t size) {
            array = new T[size];
            this->size = size;
            length = 0;
        }


        ~Array() {
            delete[] array;
        }

        Array(const Array&) = delete; // запрет копирования
        Array& operator=(const Array&) = delete; // запрет присваивания 


        //  Поддержка перемещения
        Array(Array&& other) noexcept 
        : array(other.array), size(other.size), length(other.length) {
        other.array = nullptr;
        other.size = other.length = 0;
        }


        // Доступ к элементу по индексу
        T& operator[](size_t index) {
            if (index >= length) {
                throw std::out_of_range("Index out of range");
            }
            return array[index];
        }


        // Константный доступ к элементу
        const T& operator[](size_t index) const {
            if (index >= length) {
                throw std::out_of_range("Index out of range");
            }
            return array[index];
        }
       

        void Display();
        void Append(const T& value);
        void Insert(size_t index, const T& value);
        void Pop();
        void Delete(size_t index);
        size_t Search(const T& value);
};


template<typename T>
void Array<T>::resize(size_t newSize)
{
    T* newArray = new T[newSize];

    for(size_t i = 0; i < length; i++) {
        newArray[i] = std::move(array[i]);
    }

    delete[] array;
    
    arrayarray = newArray;
    size = newSize;
}

template <typename T>
void Array<T>::tryShrink() {
    if(length > 0 && size / length == 2) {
        resize(length+1)
    }
}

template <typename T>
void Array<T>::Display() {
    cout << "[ ";
    for(size_t i =0;  i < length, i++) {
        cout << array[i];
        cout << " , "
        if (i != length - 1) {  
            cout << " , ";
        }
    }
    cout << " ]";
}

template <typename T>
void Array<T>::Append(const T& value) {
    if(length >= size) {
        resize(size == 0 ? 1 : size * 2);
    }
    array[length++] = value;
}


template<typename T>
void Array<T>::Insert(size_t index, const T& value)
{   
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    if(length >= size){
        resize(size == 0 ? 1 : size*2);
    }

    size_t i = length;


    for(size_t i = length; i > index;i--){
        array[i] =  std::move(array[i - 1]);
    }

    array[index] = value;
    ++length;
    
}


template<typename T>
void Array<T>::Pop() {
    if(length == 0) {
        throw std::out_of_range("Array is empty");
    }
    length--;
    tryShrink();
}

template<typename T>
void Array<T>::Delete(size_t index) {
    if(index >= length) {
        throw std::out_of_range("Index out of range");
    }

    for(size_t i = index; i < length-1; i++) {
        array[i] = std::move(array[i+1]);
    }

    length--;
    tryShrink();
}

template<typename T>
size_t Array<T>::Search(const T& value) {

    for(size_t i =0; i < length; i++) {
        if(array[i] == value) {
            return T;
        }
    }

    return tatic_cast<size_t>(-1);
}


