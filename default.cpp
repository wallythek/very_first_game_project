#include <iostream>
#include <string>
#include <map>
#include <ctime>

#include "default.h"
#include "fightenemy.h"
#include "instructions.h"
#include "printgrid.h"
#include "stats.h"
#include "storyline.h"

using namespace std;

void default_stats(stats &S) {
  S.fullhp = 30; S.hp = 30; S.pow = 8; S.defence = 6; S.crt = 20; S.dodge = 20;
}

// set "   " for all grid elements of a zone
void nothing(string Z[][12]) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 12; j++) {
      Z[i][j] = (i == 0 || i == 11 || j == 0 || j == 11) ? " X " : "   ";
    }
  }
}

// return default zone settings of a zone
zone default_zones(string s) {
  zone Z;
  if (s == "A1") {  // start zone
    Z.zonename = "A1";
    Z.enemy_range[0] = {15, 15, 10, 1, 10, 10};
    Z.enemy_range[1] = {20, 20, 12, 1, 15, 15};
    nothing(Z.grid);
    for (int i = 4; i <= 10; i++) {
      Z.grid[1][i] = " X "; Z.grid[i][1] = " X ";
      Z.grid[2][i] = " X "; Z.grid[i][2] = " X ";
    }
    for (int i = 0; i <= 3; i++) {
      Z.grid[i + 7][10 - i] = " X ";
    }
    Z.grid[1][3] = " X "; Z.grid[3][1] = " X "; Z.grid[3][6] = " T ";
    Z.grid[4][11] = "->B"; Z.grid[5][11] = "->B"; Z.grid[7][8] = "!!!";
    Z.grid[8][4] = " T "; Z.grid[8][10] = "!!!"; Z.grid[9][9] = " T ";
    Z.grid[10][8] = " ? "; Z.grid[11][10] = "↓↓D";
  }  
  else if (s == "B1") {
    Z.zonename = "B1";
    Z.enemy_range[0] = {20, 20, 12, 3, 15, 15};
    Z.enemy_range[1] = {30, 30, 14, 4, 20, 20};
    nothing(Z.grid);
    for (int i = 0; i < 3; i++) {
      for (int j = i + 3; j < 9 - i; j++) {
        Z.grid[i + 1][j] = " X "; Z.grid[10 - i][j] = " X ";
        Z.grid[j][i + 1] = " X "; Z.grid[j][10 - i] = " X ";
      }
    }
    Z.grid[1][1] = " T "; Z.grid[1][10] = " ? "; Z.grid[2][9] = " T ";
    Z.grid[3][3] = "!!!"; Z.grid[5][5] = "^^^"; Z.grid[5][6] = "^^^";
    Z.grid[6][5] = "^^^"; Z.grid[6][6] = "^^^"; Z.grid[8][8] = " X ";
    Z.grid[9][0] = "<-A"; Z.grid[10][0] = "<-A"; Z.grid[11][9] = "↓↓C";
    Z.grid[11][10] = "↓↓C";
  }
  else if (s == "C1") {
    Z.zonename = "C1";
    Z.enemy_range[0] = {30, 30, 13, 5, 15, 15};
    Z.enemy_range[1] = {40, 40, 16, 7, 20, 20};    
    nothing(Z.grid);
    for (int i = 5; i <= 10; ++i) {
      Z.grid[i][10] = " X "; 
    }
    for (int i = 1; i <= 2; ++i){
      for (int j = i + 3; j <= 10; ++j) {
        Z.grid[i][j] = " X ";
      }
    }
    for (int i = 0; i < 3; ++i) {
      for (int j = i; j < 3; ++j) {
        Z.grid[10 - i][j + 7] = " X ";
      }
    }
    Z.grid[0][1] = "↑↑B"; Z.grid[0][2] = "↑↑B"; Z.grid[1][4] = " X ";
    Z.grid[1][8] = "^^^"; Z.grid[2][1] = "^^^"; Z.grid[2][7] = "^^^";
    Z.grid[2][8] = " ? "; Z.grid[2][9] = "^^^"; Z.grid[3][1] = " X ";
    Z.grid[3][7] = "^^^"; Z.grid[3][8] = " T "; Z.grid[3][9] = "^^^";
    Z.grid[4][1] = " X "; Z.grid[4][8] = "^^^"; Z.grid[4][10] = " X ";
    Z.grid[5][1] = " X "; Z.grid[6][1] = " X "; Z.grid[6][6] = " T ";
    Z.grid[7][0] = "<-D"; Z.grid[7][2] = "^^^"; Z.grid[8][0] = "<-D";
    Z.grid[8][2] = "!!!"; Z.grid[9][1] = "^^^"; Z.grid[9][2] = "^^^";
    Z.grid[10][1] = "^^^"; Z.grid[10][2] = "^^^"; Z.grid[10][3] = "^^^";
    Z.grid[10][6] = "!!!";
  }
  else if (s == "D1") {  // maze zone
    Z.zonename = "D1";
    Z.enemy_range[0] = {30, 30, 13, 6, 30, 30};
    Z.enemy_range[1] = {50, 50, 17, 8, 50, 50};
    nothing(Z.grid);
    Z.grid[0][2] = "↑↑A"; Z.grid[1][1] = "^^^"; Z.grid[1][3] = "^^^";
    Z.grid[1][4] = "^^^"; Z.grid[1][5] = "^^^"; Z.grid[1][6] = "^^^";
    Z.grid[2][1] = " T "; Z.grid[2][6] = "^^^"; Z.grid[2][8] = "^^^";
    Z.grid[2][9] = "^^^"; Z.grid[2][11] = "->C"; Z.grid[3][1] = "^^^";
    Z.grid[3][2] = "^^^"; Z.grid[3][3] = "^^^"; Z.grid[3][4] = "^^^";
    Z.grid[3][8] = "   "; Z.grid[3][9] = "^^^"; Z.grid[3][11] = "->C";
    Z.grid[4][1] = "^^^"; Z.grid[4][2] = "^^^"; Z.grid[4][6] = "^^^";
    Z.grid[4][7] = "^^^"; Z.grid[4][10] = "^^^"; Z.grid[5][4] = "^^^";
    Z.grid[5][6] = "^^^"; Z.grid[5][7] = "^^^"; Z.grid[5][8] = "^^^";
    Z.grid[6][2] = "^^^"; Z.grid[6][3] = "^^^"; Z.grid[6][4] = "^^^";
    Z.grid[6][7] = "^^^"; Z.grid[6][8] = "^^^"; Z.grid[6][9] = "^^^";
    Z.grid[7][2] = " ? "; Z.grid[7][5] = "^^^"; Z.grid[7][8] = " T ";
    Z.grid[7][9] = "^^^"; Z.grid[8][2] = "^^^"; Z.grid[8][3] = "^^^";
    Z.grid[8][7] = "^^^"; Z.grid[8][8] = "^^^"; Z.grid[8][9] = "^^^";
    Z.grid[9][1] = "   "; Z.grid[9][2] = "^^^"; Z.grid[9][3] = "^^^";
    Z.grid[9][4] = "^^^"; Z.grid[9][5] = "^^^"; Z.grid[9][6] = "^^^";
    Z.grid[9][7] = "^^^"; Z.grid[10][1] = "^^^"; Z.grid[10][2] = " ? ";
    Z.grid[10][3] = "^^^"; Z.grid[10][4] = "^^^"; Z.grid[10][5] = "^^^";
    Z.grid[10][6] = "^^^"; Z.grid[10][7] = " ? "; Z.grid[10][8] = "^^^";
    Z.grid[10][9] = "^^^"; Z.grid[10][10] = "^^^"; Z.grid[11][2] = "↓↓E";
    Z.grid[11][7] = "↓↓F";
  }
  else if (s == "E1") {
    Z.zonename = "E1";
    Z.enemy_range[0] = {40, 40, 14, 3, 40, 50};
    Z.enemy_range[1] = {60, 60, 18, 4, 60, 70};
    nothing(Z.grid);
    for (int i = 2 ; i < 9; ++i) {
      Z.grid[5][i] = " X ";
    }
    Z.grid[0][10] = "↑↑D"; Z.grid[1][1] = "!!!"; Z.grid[1][2] = " T ";
    Z.grid[1][4] = "^^^"; Z.grid[1][5] = " X "; Z.grid[2][2] = "^^^";
    Z.grid[2][5] = " X "; Z.grid[2][7] = "^^^"; Z.grid[3][2] = "^^^";
    Z.grid[3][8] = "^^^"; Z.grid[4][2] = " X "; Z.grid[4][3] = "^^^";
    Z.grid[4][9] = "^^^"; Z.grid[5][9] = "^^^"; Z.grid[6][5] = "^^^";
    Z.grid[6][6] = "^^^"; Z.grid[6][7] = "^^^"; Z.grid[7][1] = "^^^";
    Z.grid[7][2] = "^^^"; Z.grid[7][6] = "^^^"; Z.grid[7][7] = "^^^";
    Z.grid[7][9] = "^^^"; Z.grid[7][10] = "^^^"; Z.grid[8][3] = "^^^";
    Z.grid[8][6] = "^^^"; Z.grid[8][7] = "^^^"; Z.grid[8][8] = " T ";
    Z.grid[8][10] = "^^^"; Z.grid[9][1] = " T "; Z.grid[9][5] = "^^^";
    Z.grid[9][6] = "^^^"; Z.grid[9][10] = "^^^"; Z.grid[10][1] = " ? ";
    Z.grid[10][3] = "^^^"; Z.grid[10][9] = "^^^"; Z.grid[10][10] = "^^^";
  }
  else if (s == "F1") {  // W1 boss zone
    Z.zonename = "F1";
    Z.enemy_range[0] = {150, 150, 20, 5, 30, 30, {"full HP"}};
    Z.enemy_range[1] = {150, 150, 25, 8, 40, 50};
    nothing(Z.grid);
    for (int i = 1 ; i < 11; ++i) {
      if (i != 5 && i != 6) {
        Z.grid[i][4] = "^^^";
      }
    }
    for (int i = 5; i <= 7; i++) {
      Z.grid[4][i] = "^^^"; Z.grid[7][i] = "^^^";
    }
    for (int i = 4; i <= 7; i++) {
      for (int j = 8; j <= 10; j++) {
        Z.grid[i][j] = "???";
      }
    }
    Z.grid[0][2] = "↑↑D";
  } 
  else if (s == "A2") {
    Z.zonename = "A2";
    Z.enemy_range[0] = {80, 80, 15, 9, 10, 10, {"full HP"}};
    Z.enemy_range[1] = {100, 100, 20, 10, 20, 20};
    nothing(Z.grid);
    for (int i = 1; i <= 6; i++) {
      for (int j = 2; j <= 9 - i; j++) {
        Z.grid[i][j] = " X "; Z.grid[11 - i][11 - j] = " X ";
      }
    }
    Z.grid[0][1] = "⇞W1"; Z.grid[4][7] = "!!!"; Z.grid[5][6] = " T ";
    Z.grid[6][5] = "!!!"; Z.grid[7][4] = " T "; Z.grid[11][10] = "↓↓B";
  }
  else if (s == "B2") {  // center zone
    Z.zonename = "B2";
    Z.enemy_range[0] = {10, 10, 18, 10, 30, 70};
    Z.enemy_range[1] = {20, 20, 25, 11, 40, 90};
    nothing(Z.grid);
    for (int i = 1; i <= 4; i++) {
      for (int j = i + 6; j <= 10; j++) {
        Z.grid[i][j] = "^^^";
      }
    }
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
        Z.grid[i][j + 2] = "^^^"; Z.grid[i + 3][j] = "^^^";
        Z.grid[i + 5][j] = "^^^";
      }
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 6 - i; j <= 6 + i; j++) {
        Z.grid[i + 8][j] = "^^^";
      }
    }
    Z.grid[0][1] = "↑↑A"; Z.grid[0][6] = "↑↑D"; Z.grid[3][3] = "   ";
    Z.grid[4][3] = "   "; Z.grid[5][6] = "^^^"; Z.grid[5][7] = " T ";
    Z.grid[5][8] = "^^^"; Z.grid[5][10] = " X "; Z.grid[5][11] = "->F";
    Z.grid[6][6] = "^^^"; Z.grid[6][7] = "^^^"; Z.grid[6][8] = "^^^";
    Z.grid[6][10] = " X "; Z.grid[6][11] = "->F"; Z.grid[7][10] = "^^^";
    Z.grid[8][3] = "   "; Z.grid[8][9] = "^^^"; Z.grid[8][10] = "^^^";
    Z.grid[9][6] = " ? "; Z.grid[9][10] = "^^^"; Z.grid[11][2] = "↓↓C";
    Z.grid[11][3] = "↓↓C"; Z.grid[11][9] = "↓↓E";
  }
  else if (s == "C2") {  // 4 '?' zone
    Z.zonename = "C2";
    nothing(Z.grid);
    Z.grid[2][3] = " X "; Z.grid[2][8] = " X "; Z.grid[3][2] = " X ";
    Z.grid[3][3] = " ? "; Z.grid[3][4] = " X "; Z.grid[3][7] = " X ";
    Z.grid[3][8] = " ? "; Z.grid[3][9] = " X "; Z.grid[4][3] = " X ";
    Z.grid[4][8] = " X "; Z.grid[7][3] = " X "; Z.grid[7][8] = " X ";
    Z.grid[8][2] = " X "; Z.grid[8][3] = " ? "; Z.grid[8][4] = " X ";
    Z.grid[8][7] = " X "; Z.grid[8][8] = " ? "; Z.grid[8][9] = " X ";
    Z.grid[9][3] = " X "; Z.grid[9][8] = " X "; Z.grid[0][9] = "↑↑B";
    Z.grid[0][10] = "↑↑B"; Z.grid[10][1] = " ? ";
  }
  else if (s == "D2") {  // maze zone
    Z.zonename = "D2";
    nothing(Z.grid);
    Z.grid[1][3] = "^^^"; Z.grid[1][8] = "^^^"; Z.grid[2][2] = "^^^";
    Z.grid[2][4] = "^^^"; Z.grid[2][7] = "^^^"; Z.grid[2][9] = "^^^";
    Z.grid[3][1] = "^^^"; Z.grid[3][3] = " ? "; Z.grid[3][4] = "^^^";
    Z.grid[3][5] = "^^^"; Z.grid[3][6] = "^^^"; Z.grid[3][7] = "^^^";
    Z.grid[3][8] = " ? "; Z.grid[3][10] = "^^^"; Z.grid[4][2] = "^^^";
    Z.grid[4][4] = "^^^"; Z.grid[4][7] = "^^^"; Z.grid[4][9] = "^^^";
    Z.grid[5][2] = " ? "; Z.grid[5][3] = "^^^"; Z.grid[5][5] = " T ";
    Z.grid[5][6] = " ? "; Z.grid[5][8] = "^^^"; Z.grid[6][3] = "^^^";
    Z.grid[6][6] = " T "; Z.grid[6][8] = "^^^"; Z.grid[7][2] = "^^^";
    Z.grid[7][4] = "^^^"; Z.grid[7][7] = "^^^"; Z.grid[7][9] = "^^^";
    Z.grid[8][1] = "^^^"; Z.grid[8][3] = " ? "; Z.grid[8][5] = "^^^";
    Z.grid[8][6] = "^^^"; Z.grid[8][8] = " ? "; Z.grid[8][10] = "^^^";
    Z.grid[9][2] = "^^^"; Z.grid[9][7] = "^^^"; Z.grid[9][9] = "^^^";
    Z.grid[10][3] = "^^^"; Z.grid[10][8] = "^^^"; Z.grid[11][4] = "↓↓B";
  }
  else if (s == "E2") {  // enter-lock zone
    Z.zonename = "E2";
    Z.enemy_range[0] = {120, 120, 18, 8, 20, 20, {"full HP"}};
    Z.enemy_range[1] = {150, 150, 22, 10, 30, 30};
    nothing(Z.grid);
    for (int i = 2; i <= 9; i++) {
      Z.grid[i][9] = "^^^"; Z.grid[9][i] = "^^^";
      Z.grid[i][2] = "^^^"; Z.grid[2][i] = "^^^";
    }
    Z.grid[1][2] = "^^^"; Z.grid[2][3] = "   ";
    for (int i = 4; i <= 7; i++) {
      Z.grid[i][7] = "^^^"; Z.grid[7][i] = "^^^";
      Z.grid[i][4] = "^^^"; Z.grid[4][i] = "^^^";
    }
    Z.grid[0][1] = "↑↑B"; Z.grid[3][4] = "^^^"; Z.grid[4][5] = "   ";
    Z.grid[5][1] = " ? "; Z.grid[5][5] = " T "; Z.grid[5][6] = "^^^";
    Z.grid[5][8] = " ? "; Z.grid[6][6] = " ? "; Z.grid[8][3] = " ? ";
  }
  else if (s == "F2") {  // regen zone
    Z.zonename = "F2";
    nothing(Z.grid);
    for (int i = 4; i <= 7; i++) {
      Z.grid[i][11] = "->G";
    }
    Z.grid[1][3] = "^^^"; Z.grid[1][9] = "^^^"; Z.grid[1][10] = "^^^";
    Z.grid[2][2] = "^^^"; Z.grid[2][3] = " T "; Z.grid[2][10] = "^^^";
    Z.grid[3][1] = "^^^"; Z.grid[3][5] = "^^^"; Z.grid[3][6] = "^^^";
    Z.grid[3][7] = "^^^"; Z.grid[4][4] = "^^^"; Z.grid[4][8] = "^^^";
    Z.grid[5][0] = "<-B"; Z.grid[5][3] = "^^^"; Z.grid[5][8] = "^^^";
    Z.grid[5][9] = " T "; Z.grid[6][0] = "<-B"; Z.grid[6][3] = "^^^";
		Z.grid[6][8] = "^^^"; Z.grid[7][3] = "^^^"; Z.grid[7][7] = "^^^";
    Z.grid[8][1] = "^^^"; Z.grid[8][4] = "^^^"; Z.grid[8][5] = "^^^";
    Z.grid[8][6] = "^^^"; Z.grid[9][2] = "^^^"; Z.grid[9][8] = " T ";
    Z.grid[9][10] = "^^^"; Z.grid[10][3] = "^^^"; Z.grid[10][9] = "^^^";
    Z.grid[10][10] = "^^^";
  }
  else if (s == "G2") {  // W2 (final) boss zone
    Z.zonename = "G2";
    Z.enemy_range[0] = {250, 250, 25, 10, 30, 30, {"attack first", "full HP"}};
    Z.enemy_range[1] = {250, 250, 35, 13, 40, 40};
    nothing(Z.grid);
    for (int i = 4; i <= 7; i++) {
      Z.grid[i][0] = "<-F";
    }
    for (int i = 4; i <= 7; i++) {
      for (int j = 7; j <= 10; j++) {
        Z.grid[i][j] = "???";
      }
    }
  }
  return Z;
}

// listing all traps/actions of all '?' that require interacting ('x')
void questionmark(stats &S, zone &Z, map<string, zone> &zones, pos &l) {
  bool flag = true;  // true (default): '?' removed after interacting
  if (Z.zonename == "A1") {  // remove 1 blockage towards zones "E1", "F1"
    zones["C1"].grid[3][9] = "   "; zones["C1"].grid[3][10] = "^^^";
    zones["D1"].grid[9][2] = "   "; zones["D1"].grid[9][7] = "   ";
    text(15);
  }
  else if (Z.zonename == "B1") {  // remove blockage towards "C1"
    Z.grid[8][8] = "   ";
    text(11);
  }
  else if (Z.zonename == "C1" || (Z.zonename == "E2" && l.y == 1)) {
    open_treasure(S, rand() % 2, true);
  }
  else if (Z.zonename == "E1") {  // remove remaining blockage towards "F1"
    zones["D1"].grid[10][7] = "   "; Z.grid[10][4] = "^^^";
    text(19);
  }
  else if (Z.zonename == "B2") {  // remove blockage to "C2" 1 '?' access
    zones["C2"].grid[3][4] = "   "; zones["C2"].grid[4][3] = "   ";
    text(777);
  }
  else if (Z.zonename == "C2") {
    if (l.y == 1) {  // remove blockage to 1 '?' access
      Z.grid[3][7] = "   "; Z.grid[4][8] = "   ";
      text(777);
    }
    else {  // activate 1 '?'
      flag = false;  // not remove '?' (change to '✓')
      Z.grid[l.x][l.y] = "♀✓ ";
      // if all 4 '?' activated, perform laser beam animation and remove
      // blockage towards "F2"
      if (Z.grid[3][3].find("✓") != -1 && Z.grid[3][8].find("✓") != -1 &&
      Z.grid[8][3].find("✓") != -1 && Z.grid[8][8].find("✓") != -1) {
        print_grid(Z); print("", 1);
        for (int i = 4; i <= 7; ++i) {
          Z.grid[i][3] = " | ";
        }
        print_grid(Z); print("", 1);
        for (int i = 4; i <= 7; ++i) {
          Z.grid[8][i] = "---";
        }
        print_grid(Z); print("", 1);
        for (int i = 4; i <= 7; ++i) {
          Z.grid[i][8] = " | ";
        }
        print_grid(Z); print("", 1);
        for (int i = 4; i <= 7; ++i) {
          Z.grid[3][i] = "---";
        }
        print_grid(Z); print("", 1);
        zones["B2"].grid[5][10] = "   "; zones["B2"].grid[6][10] = "   ";
        text(23);
      }
    }
  }
  else if (Z.zonename == "D2") {
    // remove blockage to "C2" 1 '?' access and "B2" '?' access
    if (l.x == 5 && l.y == 6) {
      zones["B2"].grid[9][5] = " T "; zones["B2"].grid[9][7] = "!!!";
      zones["C2"].grid[7][3] = "   "; zones["C2"].grid[8][4] = "   ";
      text(777);
    }
    else {  // maze change state
      flag = false;  // not remove '?' (maze settings)
      if (l.x == 8 && l.y == 3) {
        change_state(Z, 2, 7); change_state(Z, 4, 9); change_state(Z, 9, 7);
        change_state(Z, 3, 5); change_state(Z, 3, 6);
      }
      else if (l.x == 8 && l.y == 8) {
        change_state(Z, 2, 7); change_state(Z, 7, 9); change_state(Z, 7, 2);
      }
      else if (l.x == 3 && l.y == 8) {
        change_state(Z, 3, 5); change_state(Z, 3, 6); change_state(Z, 4, 2);
      }
      else if (l.x == 3 && l.y == 3) {
        change_state(Z, 3, 5); change_state(Z, 3, 6); change_state(Z, 2, 7);
        change_state(Z, 7, 9);
      }
      else if (l.x == 5 && l.y == 2) {
        change_state(Z, 4, 9); change_state(Z, 9, 7);
      }
      text(778);
    }
  }
  else if (Z.zonename == "E2") {
    // remove bloackage back to "B2" and remove blockage to "C2" 1 '?' access
    if (l.x == 6) {
      zones["C2"].grid[7][8] = "   "; zones["C2"].grid[8][7] = "   ";
      Z.grid[5][4] = "   "; Z.grid[0][1] = "↑↑B"; 
      text(20);
    }
    else if (l.y == 3) {  // for convenience in movement
      Z.grid[5][2] = "   "; 
      text(21);
    }
  }
  if (flag) {  // remove '?'
    Z.grid[l.x][l.y] = " ♀ ";
  }
}

// "D2" maze '?' activation
void change_state(zone &Z, int x, int y) {
  Z.grid[x][y] = (Z.grid[x][y] == "   ") ? "^^^" : "   ";
}

// check if '?' requires interacting or not (not require: spike, enemy, e.t.c)
bool preq(zone current, pos l) {
  return current.zonename == "D1" || (current.zonename == "E2" && l.y == 8);
}

// listing all traps/actions of all '?' that require interacting ('x')
void prequestionmark(int &lives, bool &infile, map<string, zone> &zones, zone *&current, pos &l, stats &S, char cmd, char filenumber) {
  if ((*current).zonename == "D1") {
    if ((*current).grid[l.x + 1][l.y].find("F") != -1) {
      spike(lives, infile, zones, current, l, S, '?', cmd, filenumber, true);
    }  // true: instant death spike
    else if ((*current).grid[l.x + 1][l.y].find("E") != -1) {
      (*current).grid[l.x][l.y] = "!♀!";  // disguised enemy fight
      print_grid(*current); print("", 2);

      if (!(fight(S, *current))) {
        died(lives, infile, zones, current, l, S, '?', filenumber);
      }

      (*current).grid[l.x][l.y] = " ♀ ";
    }
    else {  // deadly spikes
      spike(lives, infile, zones, current, l, S, '?', cmd, filenumber);
    }
  }
  else if ((*current).zonename == "E2") {
    (*current).grid[l.x][l.y] = "!♀!";  // disguised enemy fight
    print_grid(*current); print("", 2);
    if (!(fight(S, *current))) {
      died(lives, infile, zones, current, l, S, '?', filenumber);
    }
    (*current).grid[l.x][l.y] = " ♀ ";
  }
}

// boss zone custom settings
void boss_zone(zone &Z, pos &l, bool pre) {
  switch (Z.zonename[1]) {
    case '1':
      if (pre) {  // pre W1 boss fight
        print_grid(Z); print("", 1);
        for (int i = 0; i < 4; ++i) {
          move_char(Z, l, 's');  // down 4 spaces
          print_grid(Z); print("", 1);
        }
        time_t t; t = time(NULL); while (time(NULL) < t + 2);
        for (int i = 0; i < 4; ++i) {
          move_char(Z, l, 'd');  // right 4 spaces
          print_grid(Z); print("", 1);
        }
        t = time(NULL); while (time(NULL) < t + 2);
        for (int i = 4; i <= 7; ++i) {
          for (int j = 8; j <= 10; ++j) {
            Z.grid[i][j] = "!!!";  // boss appears
          }
        }
        print_grid(Z);
        t = time(NULL); while (time(NULL) < t + 2);
      }
      else {  // post W1 boss fight (win)
        return_to(Z, Z, l, {8, 9});  
        Z.grid[11][9] = "↓W2";
        for (int i = 4; i <= 7; ++i) {
          for (int j = 8; j <= 10; ++j) {
            Z.grid[i][j] = "   ";  //  remove "!!!"
          }
        }
        print_grid(Z); print("", 1);
        // down 2 spaces and change world
        for (int i = 0; i < 2; ++i) {
          move_char(Z, l, 's');
          print_grid(Z); print("", 1);
        }
        move_char(Z, l, 's', true);  // true: change world
      }
      break;
    case '2':
      if (pre) {  // pre W2 (final) boss fight
        print_grid(Z); print("", 1);
        for (int i = 0; i < 4; ++i) {
          move_char(Z, l, 'd');  // right 4 spaces
          print_grid(Z); print("", 1);
        }
        time_t t; t = time(NULL); while (time(NULL) < t + 2);
        for (int i = 4; i <= 7; ++i) {
          for (int j = 7; j <= 10; ++j) {
            Z.grid[i][j] = "!!!";  // (final) boss appears
          }
          print_grid(Z);
          t = time(NULL); while (time(NULL) < t + 2);
        }
      }
      break;
  }
}
