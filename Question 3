#include <iostream>
#include <vector>
#include <stdexcept>

class HashTable {
private:
    std::vector<int> table;
    int size;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int s) : size(s) {
        table.resize(size, -1); // Initialize table with -1 indicating empty slots
    }

    void insert(int key) {
        int index = hashFunction(key);
        while (table[index] != -1) {
            index = (index + 1) % size; // Linear probing
        }
        table[index] = key;
    }

    void remove(int key) {
        int index = hashFunction(key);
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1; // Mark as deleted
                return;
            }
            index = (index + 1) % size;
        }
    }

    int search(int key) {
        int index = hashFunction(key);
        while (table[index] != -1) {
            if (table[index] == key) {
                return index;
            }
            index = (index + 1) % size;
        }
        return -1; // Not found
    }

    void printTable() {
        for (int i = 0; i < size; ++i) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    void resize() {
        int oldCapacity = capacity;
        capacity *= 2;
        std::vector<Entry*> oldTable = table;
        table = std::vector<Entry*>(capacity, nullptr);
        currentSize = 0;

        for (int i = 0; i < oldCapacity; ++i) {
            if (oldTable[i] != nullptr && !oldTable[i]->isDeleted) {
                insert(oldTable[i]->key, oldTable[i]->value);
                delete oldTable[i];
            }
        }
    }

    int findIndex(int key) const {
        int index = hash(key);
        int i = 0;
        while (table[index] != nullptr && (table[index]->key != key || table[index]->isDeleted)) {
            index = (index + i * i) % capacity;
            i++;
            if (i == capacity) {
                throw std::runtime_error("Hash table is full");
            }
        }
        return index;
    }

public:
    HashTable(int initialCapacity = 0.8) : capacity(initialCapacity), currentSize(0) {
        table = std::vector<Entry*>(capacity, nullptr);
    }

    ~HashTable() {
        for (auto entry : table) {
            delete entry;
        }
    }

    void insert(int key, int value) {
        if ((double)currentSize / capacity >= loadFactorThreshold) {
            resize();
        }

        int index = findIndex(key);
        if (table[index] == nullptr || table[index]->isDeleted) {
            table[index] = new Entry(key, value);
            currentSize++;
        } else {
            table[index]->value = value;
        }
    }

    int search(int key) const {
        int index = findIndex(key);
        if (table[index] == nullptr || table[index]->isDeleted) {
            throw std::runtime_error("Key not found");
        }
        return table[index]->value;
    }

    void remove(int key) {
        int index = findIndex(key);
        if (table[index] == nullptr || table[index]->isDeleted) {
            throw std::runtime_error("Key not found");
        }
        table[index]->isDeleted = true;
        currentSize--;
    }
};

int main() {
    HashTable ht;
    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);
    ht.insert(4, 40);

    std::cout << "Value for key 1: " << ht.search(1) << std::endl;
    std::cout << "Value for key 2: " << ht.search(2) << std::endl;

    ht.remove(2);
    try {
        std::cout << "Value for key 2: " << ht.search(2) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
