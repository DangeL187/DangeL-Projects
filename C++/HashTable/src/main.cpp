#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "split.h"

int hashCode(std::string string) {
    system(("(echo -n " + string + " | md5sum) > hash.txt").c_str());
    std::string line;
    std::ifstream file;
    file.open("hash.txt");
    if (file.is_open()) {
        while (file) {
            std::getline(file, line);
            line = (split(line, ' ')[0]).erase(0, 25);
            return std::stoi(line, nullptr, 16);
        }
    }
    file.close();
    return 0;
}

class Object {
public:
    std::string key;
    int value;

    Object(std::string key_, int value_) {
        key = key_;
        value = value_;
    }
    bool operator==(const Object& other) {
        return (this->key == other.key);
    }
};

class HashTable {
private:
    int names_amount = 0;
    std::vector<std::vector<Object>> buckets;
public:
    HashTable() {
        for (int i = 0; i < 5; i++) {
            std::vector<Object> v;
            buckets.push_back(v);
        }
    }

    void add(Object other) {
        if (!(contains(other))) {
            if (names_amount == buckets.size()) {
                std::vector<std::vector<Object>> new_buckets(buckets.size()*2);
                for (auto& i: buckets) {
                    for (auto& j: i) {
                        new_buckets[hashCode(j.key) % new_buckets.size()].push_back(j);
                    }
                }
                buckets = new_buckets;
            }
            buckets[hashCode(other.key) % buckets.size()].push_back(other);
            names_amount++;
        }
    }
    bool contains(Object other) {
        for (auto& i: buckets[hashCode(other.key) % buckets.size()]) {
            if (i.key == other.key) {
                return true;
            }
        }
        return false;
    }
    void remove(Object other) {
        std::vector<Object>& temp_v = buckets[hashCode(other.key) % buckets.size()];
        auto itr = std::find(temp_v.begin(), temp_v.end(), other);
        if (itr != temp_v.end()) temp_v.erase(itr);
        names_amount--;
    }
    auto get(auto other) {
        for (auto& i: buckets[hashCode(other) % buckets.size()]) {
            if (i.key == other) {
                return i.value;
            }
        }
    }

    std::vector<std::vector<Object>> getBuckets() {
        return buckets;
    }
};

void printHashTable(std::vector<std::vector<Object>> v) {
    std::cout << "\n";
    for (auto& i: v) {
        std::cout << "[ ";
        for (auto& j: i) {
            std::cout << j.key << " ";
        }
        std::cout << "]\n";
    }
}

int main() {
    HashTable hash_table;

    hash_table.add(Object("Миша", 13));
    hash_table.add(Object("Рома", 14));
    hash_table.add(Object("Толя", 15));
    hash_table.add(Object("Даша", 16));
    hash_table.add(Object("Катя", 17));
    printHashTable(hash_table.getBuckets());
    hash_table.remove(Object("Миша", 13));
    printHashTable(hash_table.getBuckets());
    hash_table.add(Object("Ваня", 18));
    printHashTable(hash_table.getBuckets());
    hash_table.add(Object("Коля", 19));
    printHashTable(hash_table.getBuckets());
    std::cout << "\n";
    std::cout << hash_table.get("Коля") << std::endl;

    return 0;
}
