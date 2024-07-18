#include <iostream>
#include <stdexcept>
#include <string>
#include <initializer_list>
template<typename T>
class Vlist {
    private:
        T* data = nullptr;
        size_t capacity = 0;
        size_t size = 0;

    void resize(size_t new_capacity) {
        T* new_data = (T*) ::operator new(new_capacity * sizeof(T));
        
        if (new_capacity < size) {
            size = new_capacity;
        }
        for (size_t i = 0; i < size; i++) {
            new(&new_data[i]) T(std::move(data[i]));
        }
        for (size_t i = 0; i < size; i++) {
            data[i].~T();
        }        
        ::operator delete(data, capacity * sizeof(T));
        data = new_data;
        capacity = new_capacity;
    }

    public:
        Vlist(){
            resize(2);
        }

        Vlist(size_t initial_capacity) : data(new T[initial_capacity]), capacity(initial_capacity), size(0) {}

        Vlist(std::initializer_list<T> init_list) : data(new T[init_list.size()]), capacity(init_list.size()), size(init_list.size()) {
            std::copy(init_list.begin(), init_list.end(), data);
        }

        ~Vlist() {
            clear();
        }

        void pushBack(const T& value) {
            if (size >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2);
            }
            data[size] = value;
            size++;
        }

        void pushBack(T&& value) {
            if (size >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2);
            }
            data[size] = std::move(value);
            size++;
        }

        template<typename... Args>
        T& emplaceBack(Args&&... args) {
            if (size >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2);
            }
            new(&data[size]) T(std::forward<Args>(args)...);
            return data[size++];
        }

        void popBack() {
            if (size > 0) {
                size--;
                data[size].~T();
            } else {
                throw std::out_of_range("Vector is empty");
            }
        }

        void clear() {
            for (size_t i = 0; i < size; i++) {
                data[i].~T();
            }
            size = 0;
        }

        T& operator[](size_t index) {
            if (index >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }

        const T& operator[](size_t index) const {
            if (index >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }

        size_t getSize() const {
            return size;
        }

        size_t getCapacity() const {
            return capacity;
        }

        bool isEmpty() const {
            return size == 0;
        }

        T* begin() {
            return data;
        }

        T* end() {
            return data + size;
        }

        const T* begin() const {
            return data;
        }

        const T* end() const {
            return data + size;
        }

        void insert(size_t index, const T& value) {
            if (index > size) {
                throw std::out_of_range("Index out of bounds");
            }
            if (size >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2);
            }
            for (size_t i = size; i > index; --i) {
                data[i] = std::move(data[i - 1]);
            }
            data[index] = value;
            ++size;
        }

        void erase(size_t index) {
            if (index >= size) {
                throw std::out_of_range("Index out of bounds");
            }
            for (size_t i = index; i < size - 1; ++i) {
                data[i] = std::move(data[i + 1]);
            }
            --size;
        }
        
};