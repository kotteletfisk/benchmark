#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <random>
#include <sys/resource.h>
#include <algorithm>

using namespace std;
using namespace chrono;

// Struct representing a large object with fixed size (1KB)
struct LargeObject {
    uint8_t* data; // Pointer to dynamic data
    size_t size;   // Size of the allocated memory
    
    // Constructor for fixed size allocation
    LargeObject(size_t s) : size(s), data(new uint8_t[s]) {}  
    ~LargeObject() { delete[] data; }  // Destructor for deallocation
};

// Function to get the memory usage in bytes
long get_mem_usage() {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        return usage.ru_maxrss;  // Memory usage in kilobytes (platform dependent)
    } else {
        cerr << "Failed to call getrusage" << endl;
        return 0;
    }
}

void run_test() {
    const size_t NUM_OBJECTS = 1'000'000;
    vector<LargeObject*> objects;
    objects.reserve(NUM_OBJECTS);

    // Measure allocation time
    auto start_alloc = high_resolution_clock::now();
    for (size_t i = 0; i < NUM_OBJECTS; ++i) {
        size_t size = 1024;  // Fixed size of 1KB
        objects.push_back(new LargeObject(size));  // Allocate a new LargeObject on the heap
    }
    auto end_alloc = high_resolution_clock::now();
    auto alloc_duration = duration_cast<duration<double>>(end_alloc - start_alloc);

    // Shuffle the objects to simulate memory fragmentation
    shuffle(objects.begin(), objects.end(), std::random_device{});

    // Measure deallocation time
    auto start_dealloc = high_resolution_clock::now();
    for (auto obj : objects) {
        delete obj;  // Deallocate the objects
    }
    objects.clear();
    auto end_dealloc = high_resolution_clock::now();
    auto dealloc_duration = duration_cast<duration<double>>(end_dealloc - start_dealloc);

    // Print memory usage in bytes and MB

    // Measure total time for the whole test (allocation + deallocation)
    auto total_end = high_resolution_clock::now();
    auto total_duration = duration_cast<duration<double>>(end_dealloc - start_alloc);

    cout << "Fixed Size (1KB) Allocation Time: " << alloc_duration.count() << " seconds" << endl;
    cout << "Fixed Size (1KB) Deallocation Time: " << dealloc_duration.count() << " seconds" << endl;
    cout << "Memory usage: " << get_mem_usage() << " KB (" << get_mem_usage() / 1024.0 << " MB)" << endl;
    cout << "Total Test Time: " << total_duration.count() << " seconds" << endl;

}

int main() {
    // Run tests with fixed size (1KB) only
    cout << "Testing with Fixed Size (1KB)..." << endl;
    run_test();
    
    return 0;
}