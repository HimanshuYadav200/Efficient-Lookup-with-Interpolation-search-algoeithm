#include "itfdatamap.h"
#include <algorithm>

itfdatamap::itfdatamap(uint32_t divisor) : n(divisor) {}

int itfdatamap::key_hash(uint32_t value) {
    return value / n; // Use integer division for hashing
}

void itfdatamap::insert(const itfData& data) {
    int key = key_hash(data.itfType);
    itfDataMap[key].push_back(data);
    std::sort(itfDataMap[key].begin(), itfDataMap[key].end(), [](const itfData& a, const itfData& b) {
        return a.itfType < b.itfType;
    });
}

bool itfdatamap::contains(uint32_t key, uint32_t target) {
    if (itfDataMap.find(key) == itfDataMap.end()) {
        return false;
    }

    std::vector<itfData>& values = itfDataMap[key];
    if (values.empty()) {
        return false;
    }

    uint32_t low = 0;
    uint32_t high = values.size() - 1;

    while (low <= high && target >= values[low].itfType && target <= values[high].itfType) {
        if (low == high) {
            return values[low].itfType == target;
        }

        uint32_t pos = low + ((target - values[low].itfType) * (high - low)) / (values[high].itfType - values[low].itfType);
        if (pos < low || pos > high) {
            return std::binary_search(values.begin() + low, values.begin() + high + 1, itfData{"", target}, 
                [](const itfData& a, const itfData& b) {
                    return a.itfType < b.itfType;
            });
        }

        if (values[pos].itfType == target) {
            return true;
        }

        if (values[pos].itfType < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return false; // Not found
}

itfdatamap::Iterator::Iterator(itfdatamap* dataMap, uint32_t key, size_t index)
    : dataMap(dataMap), key(key), index(index) {
    // Move to the first valid index
    if (dataMap->itfDataMap.find(key) != dataMap->itfDataMap.end() &&
        index >= dataMap->itfDataMap[key].size()) {
        this->key = UINT32_MAX; // Invalid key
    }
}

itfData& itfdatamap::Iterator::operator*() {
    return dataMap->itfDataMap[key][index];
}

itfData* itfdatamap::Iterator::operator->() {
    return &dataMap->itfDataMap[key][index];
}

itfdatamap::Iterator& itfdatamap::Iterator::operator++() {
    ++index;
    if (dataMap->itfDataMap.find(key) != dataMap->itfDataMap.end() &&
        index >= dataMap->itfDataMap[key].size()) {
        key = UINT32_MAX; // Invalid key
    }
    return *this;
}

bool itfdatamap::Iterator::operator!=(const Iterator& other) const {
    return key != other.key || index != other.index;
}

bool itfdatamap::Iterator::operator==(const Iterator& other) const {
    return !(*this != other);
}

itfdatamap::Iterator itfdatamap::begin(uint32_t key) {
    return Iterator(this, key, 0);
}

itfdatamap::Iterator itfdatamap::end(uint32_t key) {
    if (itfDataMap.find(key) != itfDataMap.end()) {
        return Iterator(this, key, itfDataMap[key].size());
    }
    return Iterator(this, UINT32_MAX, 0); // Invalid key
}

itfdatamap::Iterator itfdatamap::findItem(uint32_t key, uint32_t target) {
    if (itfDataMap.find(key) == itfDataMap.end()) {
        return end(key); // Key not found
    }

    std::vector<itfData>& values = itfDataMap[key];
    uint32_t low = 0, high = values.size() - 1;

    while (low <= high && target >= values[low].itfType && target <= values[high].itfType) {
        if (low == high) {
            return (values[low].itfType == target) ? Iterator(this, key, low) : end(key);
        }

        uint32_t pos = low + ((target - values[low].itfType) * (high - low)) / (values[high].itfType - values[low].itfType);
        if (pos < low || pos > high) {
            return end(key); // Out of bounds
        }

        if (values[pos].itfType == target) {
            return Iterator(this, key, pos);
        }

        if (values[pos].itfType < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return end(key); // Target not found

}
