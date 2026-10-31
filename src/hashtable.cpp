#include <cmath>
#include "hashtable.h"

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


// K largest: returns k largest elements or fewer if there aren't k elements
vector<weatherNode> HashTable::kLargest(int k) {
    vector<weatherNode> result;
    if (k <= 0 ) {
        return result;
    }
    // Walks the keys from the highest score (100) down
    // Using search to get nodes with each score
    double score = 0;
    for (int key = 100; key >= 0; key--) {
        score = key / 10.0;
        vector<weatherNode> found = search(score);
        // Get the first k nodes found or fewer
        for (const auto& node : found) {
            result.push_back(node);
            k--;
            if (k == 0) {
                return result;
            }
        }
    }
    return result;
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


// Clear: removes all nodes and resets the table to its starting size
void HashTable::clear() {
    table.clear();
    table.resize(11);
    numItems = 0;
}
