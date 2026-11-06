#include <optional>
#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <utility>

template<typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t capacity) : m_capacity(capacity) {}

    void put(const Key& key, const Value& value);
    std::optional<Value> get(const Key& key);

private:
    size_t m_capacity;
    std::list<std::pair<Key, Value>> m_cache;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> m_map;
};

template<typename Key, typename Value>
void LRUCache<Key, Value>::put(const Key& key, const Value& value) {
    auto it = m_map.find(key);
    if (it != m_map.end()) {
        m_cache.erase(it->second);
        m_map.erase(it);
    }

    m_cache.push_front({key, value});
    m_map[key] = m_cache.begin();

    if (m_cache.size() > m_capacity) {
        auto last = --m_cache.end();
        m_map.erase(last->first);
        m_cache.pop_back();
    }
}

template<typename Key, typename Value>
std::optional<Value> LRUCache<Key, Value>::get(const Key& key) {
    auto it = m_map.find(key);
    if (it == m_map.end()) return std::nullopt;

    m_cache.splice(m_cache.begin(), m_cache, it->second);
    return it->second->second;
}

#endif // LRUCACHE_H