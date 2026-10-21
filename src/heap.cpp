#include "heap.h"
#include <algorithm>
using namespace std;


// Weather Node
void weatherNode::calculateScore(int activity){
    if(activity == 0){
        if(22 - abs(this->temp) < 5) score += 2;
        if(5 - abs(this->temp) < 5) score += 2;
    }
}


// Private helpers
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

// Modifiers
void Heap::pop(){
    if (heap.empty()) return;

    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
        heapifyDown(0);
    }
}
void Heap::insert(int d, int hr, int l, double t, double w, double p, int c, double s){
    weatherNode newNode = weatherNode(d, hr, l, t, w, p, c, s);

    heap.push_back(newNode);

    heapifyUp(heap.size() - 1);
}
void Heap::insert(weatherNode node){
    heap.push_back(node);

    heapifyUp(heap.size() - 1);
}

// Getters
weatherNode Heap::top(){
    return heap[0];
}
bool Heap::empty(){
    return heap.empty();
}
int Heap::size(){
    return heap.size();
}