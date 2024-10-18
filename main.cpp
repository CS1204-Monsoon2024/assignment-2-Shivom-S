#include "HashTable.cpp"


#include <vector>
#include <cmath>
#include <stdexcept>

class HashTable {
private:
    struct Entry {
        int key;
        int value;
        bool isActive;
        Entry(int k, int v) : key(k), value(v), isActive(true) {}
    };

    std::vector<Entry*> table;
    int currentSize;
    int capacity;
    const double loadFactorThreshold = 0.8;

    int hashFunction(int key) const {
        return key % capacity;
    }

    void resize() {
        int oldCapacity = capacity;
        capacity = nextPrime(2 * capacity);
        std::vector<Entry*> oldTable = table;
        table = std::vector<Entry*>(capacity, nullptr);
        currentSize = 0;

        for (int i = 0; i < oldCapacity; ++i) {
            if (oldTable[i] != nullptr && oldTable[i]->isActive) {
                insert(oldTable[i]->key, oldTable[i]->value);
                delete oldTable[i];
            }
        }
    }

    int nextPrime(int n) {
        while (!isPrime(n)) {
            ++n;
        }
        return n;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

public:
    HashTable(int size = 11) : table(size, nullptr), currentSize(0), capacity(size) {}

    ~HashTable() {
        for (auto entry : table) {
            delete entry;
        }
    }

    void insert(int key, int value) {
        if (currentSize >= capacity * loadFactorThreshold) {
            resize();
        }

        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % capacity] != nullptr && table[(index + i * i) % capacity]->isActive) {
            if (table[(index + i * i) % capacity]->key == key) {
                table[(index + i * i) % capacity]->value = value;
                return;
            }
            ++i;
        }

        table[(index + i * i) % capacity] = new Entry(key, value);
        ++currentSize;
    }

    bool search(int key, int &value) const {
        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % capacity] != nullptr) {
            if (table[(index + i * i) % capacity]->key == key && table[(index + i * i) % capacity]->isActive) {
                value = table[(index + i * i) % capacity]->value;
                return true;
            }
            ++i;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (table[(index + i * i) % capacity] != nullptr) {
            if (table[(index + i * i) % capacity]->key == key && table[(index + i * i) % capacity]->isActive) {
                table[(index + i * i) % capacity]->isActive = false;
                --currentSize;
                return;
            }
            ++i;
        }
    }
};


int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
