#include <cassert>
#include "../include/lrucache.h"

int main() {
    LRUCache<int, int> cache(2);
    assert(!cache.get(1));
    cache.put(1, 10);
    cache.put(2, 20);
    assert(*cache.get(1) == 10);
    cache.put(3, 30);
    assert(!cache.get(2));
    assert(*cache.get(3) == 30);
    cache.put(4, 40);
    assert(!cache.get(1));
    assert(*cache.get(4) == 40);
    return 0;
}