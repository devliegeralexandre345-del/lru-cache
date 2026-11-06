#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <unordered_map>
#include <list>
#include <stdexcept>

template<typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t capacity) : m_capacity(capacity) {}

    void put(const Key& key, const Value& value) {
        auto it = m_cache.find(key);
        if (it != m_cache.end()) {
            // Move the element to the front of the list and update its value.
            m_list.splice(m_list.begin(), m_list, it->second);
            it->second->second = value;
        } else {
            if (m_list.size() == m_capacity) {
                // Remove the least recently used item from both map and list.
                auto last = --m_list.end();
                m_cache.erase(last->first);
                m_list.pop_back();
            }
            // Insert new element at the front of the list.
            m_list.push_front(std::make_pair(key, value));
            m_cache[key] = m_list.begin();
        }
    }

    Value get(const Key& key) {
        auto it = m_cache.find(key);
        if (it == m_cache.end()) {
            throw std::out_of_range("Key not found in cache.");
        } else {
            // Move the element to the front of the list.
            m_list.splice(m_list.begin(), m_list, it->second);
            return it->second->second;
        }
    }

private:
    size_t m_capacity;
    std::list<std::pair<Key, Value>> m_list;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> m_cache;
};

#endif // LRU_CACHE_HPP