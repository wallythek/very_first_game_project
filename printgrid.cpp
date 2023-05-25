#include <iostream>
#include <string>

#include "default.h"
#include "printgrid.h"

using namespace std;

void print_grid(zone Z) {
  cout << "You are at World " << Z.zonename[1] << " Zone " << Z.zonename[0] << endl;

  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 11; j++) {
      if (i == 0 || i == 11) {
        cout << Z.grid[i][j] << " ";
      }
      else {
        cout << Z.grid[i][j] << "|";      
      }
    }
    cout << Z.grid[i][11] << endl;
    // edge cases
    if (i != 11) {
      cout <<  "   ";
      for (int i = 0; i < 10; i++) {
        cout << "+---";
      }
      cout << "+" << endl;
    }
  }
}

// might not be printed in case of enemy fight, default movement, e.t.c
void print_instructions() {
  cout << "w: up  a: left  s: down  d: right  x: interact" << endl;
  cout << "h: help  z: save  q: quit" << endl;
}
