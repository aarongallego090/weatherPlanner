#include <cmath>
#include "hashtable.h"
#include <iostream>

// Makes empty buckets with nothing stored yet
HashTable::HashTable(int startSize) {
    table.resize(startSize);
    numItems = 0;
}

// Hash function: converts score into hash code -> reduces it to get bucket index
int HashTable::hashFunction(double score) {
    // hash code
    int key = static_cast<int>(round(score * 10));
    // reduce
    int index = key % static_cast<int>(table.size());
    return index;
}

// Insert: adds the node using separate chaining, rehashed if the max load factor (0.8) is reached
void HashTable::insert(weatherNode node) {
    int index = hashFunction(node.score);
    // insert value at index, increment num of items
    table[index].push_back(node);
    numItems++;
    double loadFactor = static_cast<double>(numItems) / table.size();
    if (loadFactor >= 0.8) {
        rehash();
    }
}

// Search:
vector<weatherNode> HashTable::search(double score) {
    //find the hash of the value
    // reduce the hash to get an index
    // check if value is not at index -> return false
    // otherwise, search based on collision resolution strategy
    return vector<weatherNode>();
}

// K largest:
vector<weatherNode> HashTable::kLargest(int k) {
    return vector<weatherNode>();
}

// Rehash: doubles the table size when the max load factor is reached, and re-inserts every node
void HashTable::rehash() {
    vector<vector<weatherNode>> oldTable = table;
    int newSize = static_cast<int>(table.size()) * 2;
    table.clear();
    table.resize(newSize);
    numItems = 0;
    for (const auto& bucket : oldTable) { // each bucket
        for (const auto& node : bucket) { // each node in bucket
            insert(node);
        }
    }
}
