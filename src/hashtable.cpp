#include <cmath>
#include "hashtable.h"
#include <iostream>

// Makes empty buckets with nothing stored yet
HashTable::HashTable(int startSize) {
    table.resize(startSize);
    numItems = 0;
}

// Helper function - Hash code: turns score into a whole number
int HashTable::getKey(double score) {
    return static_cast<int>(round(score * 10));
}

// Hash function: gets key -> reduces it to get bucket index
int HashTable::hashFunction(double score) {
    int key = getKey(score);
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

// Search: returns all nodes with score, empty is none
vector<weatherNode> HashTable::search(double score) {
    vector<weatherNode> result;
    int key = getKey(score);
    // Hashes score to find bucket, then checks each node in that bucket
    int index = hashFunction(score);
    for (const auto& node : table[index]) {
        if (key == getKey(node.score)) {
            result.push_back(node);
        }
    }
    return result;
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
