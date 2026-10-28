#include <iostream>
#include "heap.h"
#include "ui.h"
using namespace std;

int main(){
   Heap weather;
   Heap scores(true);

   //Pass in map when implemented
   menu(weather, scores);

  cout << "Ending Program" << endl;
}
