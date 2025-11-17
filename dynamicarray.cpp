#include <iostream>
#include <algorithm>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];

        size_t elements_to_copy = std::min(size_, new_capacity);
        for (size_t i = 0; i < elements_to_copy; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity_ = new_capacity;
        size_ = elements_to_copy;
    }

public:
    DynamicArray(size_t initial_capacity = 4)
        : size_(0), capacity_(initial_capacity) {
        data = new T[capacity_];
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other)
        : size_(other.size_), capacity_(other.capacity_) {
        data = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(DynamicArray other) {
        std::swap(data, other.data);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        return *this;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        data[size_] = value;
        size_++;
    }

    void pop_back() {
        if (size_ == 0) {
            return;
        }
        size_--;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            std::cerr << "Error: Index out of bounds!\n";
            exit(1);
        }
        return data[index];
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void print_status() const {
        std::cout << "Status: Size = " << size_ << ", Capacity = " << capacity_ << "\n";
        if (size_ > 0) {
            std::cout << "Elements: [";
            for (size_t i = 0; i < size_; ++i) {
                std::cout << data[i] << (i == size_ - 1 ? "" : ", ");
            }
            std::cout << "]\n";
        }
    }
};

int main() {
    DynamicArray<int> vec;
    vec.print_status();

    for (int i = 0; i < 8; ++i) {
        vec.push_back((i + 1) * 10);
        vec.print_status();
    }

    vec.pop_back();
    vec.print_status();

    vec.pop_back();
    vec.print_status();

    if (vec.size() > 2) {
        vec[2] = 999;
    }
    vec.print_status();

    DynamicArray<int> vec2 = vec;
    vec2.print_status();

    DynamicArray<int> vec3;
    vec3.push_back(100);
    vec3 = vec;
    vec3.print_status();

    return 0;
}
