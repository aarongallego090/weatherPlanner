#pragma once
#include<string>
using namespace std;

class Heap {
private:
    struct weatherNode{
        int date;
        int hour;
        string loc;

        int temp = 0;
        int wind = 0;
        int precip = 0;
        int cloudCover = 0;
        double score = 0;

        weatherNode(int d, int h, const string& l, int t, int w, int p, int c, double s) :
                date(d), hour(h), loc(l), temp(t), wind(w), precip(p), cloudCover(c), score(s) {}

        bool operator<(const weatherNode& other) const {
            if(date != other.date) return date < other.date;
            return hour < other.hour;
        }

        bool operator>(const weatherNode& other) const {
            if(date != other.date) return date > other.date;
            return hour > other.hour;
        }
    };
    vector<weatherNode> heap;

    void heapifyDown(int index);
    void heapifyUp(int index);

public:
    void buildHeap();
    void pop();
    void insert(int d, int hr, const string& l, int t, int w, int p, int c, double s);
};