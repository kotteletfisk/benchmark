#include <iostream>
#include <chrono>
#include <memory>

struct Node {
    int data;
    Node* next;
};

void test_raw_pointers(size_t num_allocations) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < num_allocations; i++) {
        Node* n = new Node{i, nullptr};  // Heap allocation
        delete n;  // Deallocate
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Raw Pointer Allocation Time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;
}

void test_smart_pointers(size_t num_allocations) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < num_allocations; i++) {
        std::unique_ptr<Node> n = std::make_unique<Node>(Node{i, nullptr});
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Smart Pointer (unique_ptr) Allocation Time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;
}

int main() {
    size_t num_allocations = 1'000'000;
    
    test_raw_pointers(num_allocations);
    test_smart_pointers(num_allocations);
    
    return 0;
}
