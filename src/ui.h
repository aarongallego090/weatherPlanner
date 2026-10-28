#pragma once
#include "heap.h"

//Modify this to take in hash maps
void menu(Heap& weather, Heap& scores);

//Heap
void readData(Heap& weather, int method);

void getDay(int& date, int& location, int& activity);
bool fillDayHeap(int& date, int& location, int& activity, Heap& weather, Heap& scores);