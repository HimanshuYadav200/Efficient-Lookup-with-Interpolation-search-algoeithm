#ifndef ITFDATAMAP_H
#define ITFDATAMAP_H

#include <map>
#include <vector>
#include "itfdata.h"  // Include the itfData header

class itfdatamap {
private:
    std::map<uint32_t, std::vector<itfData>> itfDataMap;
    uint32_t n;

public:
    itfdatamap(uint32_t divisor);

    int key_hash(uint32_t value);
    void insert(const itfData& data);
    bool contains(uint32_t key, uint32_t target);

    class Iterator {
    public:
        using value_type = itfData;
        using pointer = itfData*;
        using reference = itfData&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator(itfdatamap* dataMap, uint32_t key, size_t index);

        reference operator*();
        pointer operator->();
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        bool operator==(const Iterator& other) const;

    private:
        itfdatamap* dataMap;
        uint32_t key;
        size_t index;
    };

    Iterator begin(uint32_t key);
    Iterator end(uint32_t key);
    Iterator findItem(uint32_t key, uint32_t target);
};

#endif // ITFDATAMAP_H
