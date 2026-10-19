#include "heap.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void Heap::heapifyDown(int index){
    int size = heap.size();
    int min = index;

    int lChild = index*2+1;
    int rChild = index*2+2;

    if(lChild < size && heap[lChild] < heap[min]) min = lChild;
    if(rChild < size && heap[rChild] < heap[min]) min = rChild;

    if(min == index) return;
    else{
        swap(heap[index], heap[min]);
        heapifyDown(min);
    }
}

void Heap::heapifyUp(int index){
    if(index == 0) return;

    int parent = (index-1)/2;
    if(heap[index] < heap[parent]){
        swap(heap[parent], heap[index]);
        heapifyUp(parent);
    }
    else return;
}

void Heap::buildHeap() {
    for(int i = (int)heap.size() / 2 - 1; i >= 0; i--){
        heapifyDown(i);
    }
}

void Heap::pop(){
    if (heap.empty()) return;

    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }
}

void Heap::insert(int d, int hr, const string& l, int t, int w, int p, int c, double s){
    Heap::weatherNode newNode = Heap::weatherNode(d, hr, l, t, w, p, c, s);

    heap.push_back(newNode);

    heapifyUp(heap.size() - 1);
}

