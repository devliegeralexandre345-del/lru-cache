#include <iostream>
#include "../include/lrucache.h"

int main() {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    auto value = cache.get(1);
    if (value) {
        std::cout << *value << std::endl; // Output: one
    }
    cache.put(3, "three");
    value = cache.get(2);
    if (!value) {
        std::cout << "two was evicted" << std::endl;
    }
    return 0;
}