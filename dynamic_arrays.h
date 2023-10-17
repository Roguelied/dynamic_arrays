#ifndef DYNAMIC_ARRAYS_DYNAMIC_ARRAYS_H
#define DYNAMIC_ARRAYS_DYNAMIC_ARRAYS_H

#include <iostream>
#include <algorithm>

template<typename T> class Array;
template<typename T> std::ostream& operator<<(std::ostream & os, const Array<T> & arr) {
    size_t size = arr.getSize();
    T* array = arr.getPtr();
    if (array) {
        for (int i = 0; i < size; i++) { os << array[i] << ' '; }
    } return os;
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

template<typename T>
class Array
{
    static_assert(
            std::is_same<int, T>::value ||
            std::is_same<double, T>::value ||
            std::is_same<float, T>::value
    );

private:
    T *arr;
    size_t size{0};


public:
    Array() : arr(nullptr), size(0) {}

    Array(size_t size) : arr(new T[size]), size(size) {}

    Array(const Array &array) {
        this->arr = new T[array.size];
        this->size = array.size;
        for (int i = 0; i < size; i++) {
            arr[i] = array.arr[i];
        }
    }

    Array(size_t size, T item) {
        this->size = size;
        arr = new T[size];
        for (size_t i = 0; i < size; i++) { arr[i] = item; }
    }

    ~Array() {
        for (size_t i = 0; i < size; i++) { arr[i] = 0; }
        delete[] arr;
        arr = nullptr;
    }



    [[nodiscard]] int *getPtr() const { return arr; }
    [[nodiscard]] int getSize() const  { return this->size; }



    void resize_to(size_t newSize);
    void erase() {this->resize_to(size - 1);}
    void erase(size_t index);
    void add(T item) { this->resize_to(size + 1); this->arr[size - 1] = item; }
    void add(T item, size_t index);


    int max() {
        T max = arr[0];
        for (size_t i = 0; i < size; i++) {
            if (arr[i] > max) { max = arr[i]; }
        } return max;
    }

    int min() {
        T min = arr[0];
        for (size_t i = 0; i < size; i++) {
            if (arr[i] < min) { min = arr[i]; }
        } return min;
    }

    size_t index(T item) {
        for (size_t i = 0; i < size; i++) {
            if (arr[i] == item) return i;
        } return -1;
    }



    Array& operator = (const Array & other) {
        if (arr == other.arr) {
            return *this;
        }
        this->resize_to(other.size);
        for (size_t i = 0; i < other.size; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    }

    friend std::ostream &operator << <T>(std::ostream & os, const Array<T> & arr);

};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


template<typename T>
void Array<T>::erase(size_t index) {

    if (index > size) {
        std::cout << "Index error";
        exit(100);
    }
    T *temp = new T[size - 1];
    for (size_t i = 0; i < size - 1; i++) { temp[i] = arr[i]; }
    for (size_t i = index + 1; i < size; i++) { temp[i - 1] = arr[i]; }

    delete[] arr;
    arr = new T[--size];

    for (size_t i = 0; i < size; i++) { arr[i] = temp[i]; }
    for (size_t i = 0; i < size; i++) { temp[i] = 0; }

    delete[] temp;
    temp = nullptr;
}

template<typename T>
void Array<T>::add(T item, size_t index) {
    if (index > size) {
        std::cout << "Index error";
        exit(100);
    }
    T *temp = new T[size + 1];
    for (size_t i = 0; i < index; i++) { temp[i] = arr[i]; }
    temp[index] = item;
    for (size_t i = index + 1; i < size + 1; i++) { temp[i] = arr[i - 1]; }

    delete[] arr;
    arr = new T[++size];

    for (size_t i = 0; i < size; i++) { arr[i] = temp[i]; }
    for (size_t i = 0; i < size; i++) { temp[i] = 0; }

    delete[] temp;
    temp = nullptr;
}

template<typename T>
void Array<T>::resize_to(size_t newSize) {
    T* newData = new T[newSize];

    if (newSize > size) {
        for (size_t i = 0; i < size; i++) { newData[i] = arr[i]; }
        for (size_t i = size; i < newSize; i++) { newData[i] = 0; }

    } else if (newSize <= size) {
        for (size_t i = 0; i < newSize; i++) { newData[i] = arr[i]; }
    }

    for (size_t i = 0; i < size; i++) { arr[i] = 0; }
    delete[] arr;
    arr = newData;
    size = newSize;
}

//----------------------------------------------------------------------------------------------------------------------



#endif //DYNAMIC_ARRAYS_DYNAMIC_ARRAYS_H
