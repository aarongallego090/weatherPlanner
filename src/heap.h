#pragma once
#include<string>
#include<vector>
using namespace std;

struct weatherNode{
    int date;
    int hour;
    int loc;

    double temp = 0;
    double wind = 0;
    double precip = 0;
    int cloudCover = 0;
    double score = 0;

    weatherNode(int d, int h, int l, double t, double w, double p, int c, double s) :
            date(d), hour(h), loc(l), temp(t), wind(w), precip(p), cloudCover(c), score(s) {}

    bool operator<(const weatherNode& other) const {
        if(date != other.date) return date < other.date;
        return hour < other.hour;
    }

    bool operator>(const weatherNode& other) const {
        if(date != other.date) return date > other.date;
        return hour > other.hour;
    }

    void calculateScore(int activity);
};

class Heap {
private:
    vector<weatherNode> heap;

    void heapifyDown(int index);
    void heapifyUp(int index);


public:
    // Modifiers
    void pop();
    void insert(int d, int hr, int l, double t, double w, double p, int c, double s);
    void insert(weatherNode node);

    // Getters
    weatherNode top();
    weatherNode kLargest(int k);
    bool empty();
    int size();

};