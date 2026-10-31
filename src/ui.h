#pragma once
#include "heap.h"
#include "hashtable.h"
#include <vector>

void menu(Heap& weather, Heap& scores, HashTable& hashScores);

//Heap
void readData(Heap& weather, int method);

void getDay(int& date, int& location, int& activity);

vector<weatherNode> getDayNodes(int date, int location, int activity, Heap& weather);
void fillHeap(const vector<weatherNode>& dayNodes, Heap& scores);
void fillHashTable(const vector<weatherNode>& dayNodes, HashTable& hashScores);