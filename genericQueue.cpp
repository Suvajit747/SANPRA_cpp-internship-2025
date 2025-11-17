#include <iostream>
#include <string>
#include <list>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::list<T> elements;

public:
    void enqueue(const T& value) {
        elements.push_back(value);
        std::cout << "[ENQUEUE] Added: " << value << "\n";
    }

    T dequeue() {
        if (is_empty()) {
            throw std::runtime_error("Cannot dequeue: Queue is empty.");
        }
        T front_value = elements.front();
        elements.pop_front();
        std::cout << "[DEQUEUE] Removed: " << front_value << "\n";
        return front_value;
    }

    const T& front() const {
        if (is_empty()) {
            throw std::runtime_error("Cannot access front: Queue is empty.");
        }
        return elements.front();
    }

    bool is_empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }

    void print_queue() const {
        std::cout << "Queue Content (Front -> Back, Size: " << size() << "): [";
        bool first = true;
        for (const auto& item : elements) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << item;
            first = false;
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "--- 1. Integer Queue Demonstration ---\n";

    Queue<int> int_queue;
    int_queue.enqueue(10);
    int_queue.enqueue(20);
    int_queue.enqueue(30);

    int_queue.print_queue();

    try {
        std::cout << "Front element is: " << int_queue.front() << "\n";
        int_queue.dequeue();
        int_queue.dequeue();
        int_queue.print_queue();
    } 
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "\n--- 2. String Queue Demonstration ---\n";

    Queue<std::string> string_queue;
    string_queue.enqueue("Apple");
    string_queue.enqueue("Banana");
    string_queue.enqueue("Cherry");

    string_queue.print_queue();

    try {
        std::cout << "Front element is: " << string_queue.front() << "\n";
        string_queue.dequeue();
        string_queue.enqueue("Date");
        string_queue.print_queue();

        string_queue.dequeue();
        string_queue.dequeue();
        string_queue.dequeue();
    } 
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
