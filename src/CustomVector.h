#include <iostream>
#include <stdexcept>
#include <string>
#include <initializer_list>

template<typename T>
class Vlist {
    private:
        T* data;
        size_t capacity;
        size_t size;

    void resize(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        
        // Construct new elements
        for (size_t i = 0; i < size; ++i) {
            new(new_data + i) T(std::move(data[i]));
            data[i].~T(); // Manually destroy old element
        }
        
        ::operator delete(data);
        data = new_data;
        capacity = new_capacity;
    }

    public:
        Vlist() : data(nullptr), capacity(0), size(0) {}

        Vlist(size_t initial_capacity) : data(new T[initial_capacity]), capacity(initial_capacity), size(0) {}

        Vlist(std::initializer_list<T> init_list) : data(new T[init_list.size()]), capacity(init_list.size()), size(init_list.size()) {
            std::copy(init_list.begin(), init_list.end(), data);
        }

        ~Vlist() {
            if (data) {
                for (size_t i = 0; i < size; ++i) {
                    data[i].~T();
                }
                ::operator delete(data);
            }
        }

        void push_back(const T& value) {
            if (size >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2);
            }
            data[size++] = value;
        }

        void push_back(T&& value) {
            if (size >= capacity) {
                resize(capacity == 0 ? 1 : capacity * 2);
            }
            data[size++] = std::move(value);
        }

        void pop_back() {
            if (size > 0) {
                --size;
            } else {
                throw std::out_of_range("Vector is empty");
            }
        }

        size_t get_size() const {
            return size;
        }

        size_t get_capacity() const {
            return capacity;
        }

        bool is_empty() const {
            return size == 0;
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

        void clear() {
            delete[] data;
            data = nullptr;
            capacity = 0;
            size = 0;
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
