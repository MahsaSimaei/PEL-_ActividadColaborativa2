#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstddef>
#include <stdexcept>

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray(size_t initialCapacity = 2) : size(0), capacity(initialCapacity) {
        if (capacity == 0) capacity = 2;
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    // Copia prohibida (opcional, para evitar errores)
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    void add(const T& element) {
        if (size == capacity) {
            resize();
        }
        data[size++] = element;
    }

    int find(const T& element) const {
        for (size_t i = 0; i < size; i++) {
            if (data[i] == element) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    void removeAt(size_t index) {
        if (index < size) {
            for (size_t i = index; i < size - 1; i++) {
                data[i] = data[i + 1];
            }
            size--;
        }
    }

    size_t getSize() const {
        return size;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }
};

#endif //DYNAMICARRAY_H