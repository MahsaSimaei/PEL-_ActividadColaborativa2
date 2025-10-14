
template<typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray(size_t initialCapacity = 2) : size(0), capacity(initialCapacity) {
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void add(const T& element) {
        if (size == capacity) {
            resize();
        }
        data[size++] = element;
    }

    int find(const T& element) const {
        for (size_t i = 0; i < size; i++) {
            if (data[i] == element) {
                return i;
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
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }
};


#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#endif //DYNAMICARRAY_H
