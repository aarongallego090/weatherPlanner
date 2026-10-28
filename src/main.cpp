#include <iostream>
#include "heap.h"
#include "ui.h"
using namespace std;

int main(){
   Heap weather;

   bool scoreHeap = true;
   Heap scores(scoreHeap);


   menu(weather, scores);

  cout << "Ending Program" << endl;
}
