#include "heap.h"
#include <algorithm>
using namespace std;


// Weather Node
int rangeScore(double value, double idealLow, double idealHigh, int maxPoints) {
    if (value >= idealLow && value <= idealHigh)
        return maxPoints;

    double distance;

    if (value < idealLow)
        distance = idealLow - value;
    else
        distance = value - idealHigh;

    return max(0, (int)(maxPoints - distance));
}
void weatherNode::calculateScore(int activity){
    // Score for running
    if(activity == 0){
        score += rangeScore(temp, 18, 26, 5);
        score += rangeScore(wind, 0, 10, 2);
        if(precip == 0)
            score += 2;
    }
    // Score for tanning
    if(activity == 1){
        score += rangeScore(temp, 25, 32, 2);
        if(precip == 0)
            score += 5;
        score += rangeScore(cloudCover, 0, 25, 3);
    }
    // Score for swimming
    if(activity == 2){
        score += rangeScore(temp, 25, 37, 3);
        if(precip == 0)
            score += 2;
        score += rangeScore(cloudCover, 0, 25, 4);
    }
    // Score for picnic
    if(activity == 3){
        score += rangeScore(temp, 21, 29, 3);
        score += rangeScore(wind, 0, 5, 4);
        if(precip == 0)
            score += 2;
        score += rangeScore(cloudCover, 0, 50, 1);
    }
}



// Private helpers
void Heap::heapifyDown(int index){
    int size = heap.size();
    int max = index;

    int lChild = index*2+1;
    int rChild = index*2+2;

    if(lChild < size && heap[lChild] > heap[max]) max = lChild;
    if(rChild < size && heap[rChild] > heap[max]) max = rChild;

    if(max == index) return;

    else{
        swap(heap[index], heap[max]);
        heapifyDown(max);
    }
}
void Heap::heapifyUp(int index){
    if(index == 0) return;

    int parent = (index-1)/2;
    if(heap[index] > heap[parent]){
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
void Heap::clear() {
    heap.clear();
}

// Getters
weatherNode Heap::top(){
    return heap[0];
}
Heap Heap::kLargest(int k){
    Heap kHeap;

    for(int i = 0; i < heap.size(); i++){
        if(kHeap.size() < k){
            kHeap.insert(heap[i]);
        }
        else if(heap[i].score > kHeap.top().score){
            kHeap.pop();
            kHeap.insert(heap[i]);
        }
    }

    return kHeap;
}

bool Heap::empty(){
    return heap.empty();
}
int Heap::size(){
    return heap.size();
}