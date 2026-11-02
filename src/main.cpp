#include <iostream>
#include "heap.h"
#include "ui.h"
using namespace std;

int main(){
    Heap weather;
    Heap scores(true);
    HashTable hashScores;

    menu(weather, scores, hashScores);
    cout << "Ending Program" << endl;
}
