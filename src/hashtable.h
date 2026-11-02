#ifndef WEATHERPLANNER_HASHTABLE_H
#define WEATHERPLANNER_HASHTABLE_H
#include <vector>
#include "heap.h"
using namespace std;

class HashTable {
private:
    vector<vector<weatherNode>> table;
    int numItems = 0;

    int hashFunction(double score);
    int getKey(double score);
    void rehash();

public:
    HashTable(int startSize = 11);
    void insert(weatherNode node);
    vector<weatherNode> search(double score);
    vector<weatherNode> kLargest(int k);
    void clear();
};


#endif //WEATHERPLANNER_HASHTABLE_H