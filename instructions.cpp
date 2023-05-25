#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "filemanip.h"
#include "printgrid.h"
#include "instructions.h"
#include "storyline.h"
#include "stats.h"
#include "default.h"

using namespace std;

// opening treasure with bias and badluck options
void open_treasure(stats &S, int bias, bool badluck) {
  srand(time(NULL));
  stats original = S, change;
  int luck;
  if (badluck) {
    luck = -1;
    change.fullhp = - (rand() % (3 + bias) + bias + 15);
    change.hp = 0;
    change.pow = - (rand() % (2 + bias) + bias);
    change.defence = - (rand() % (1 + bias) + 2);
    change.crt = - (rand() % (2 + bias) + bias + 7);
    change.dodge = - (rand() % (2 + bias) + bias + 7);
    change.tools = {"any" + to_string(rand() % 3 + 1)};  // random tools removed
  }
  else {
    luck = rand() % 3 + 1;
    if (luck == 1) {
      change.fullhp = rand() % (2 + bias) + bias + 1;
      change.hp = rand() % (1 + bias) + bias + 1;
      change.pow = rand() % (2 + bias) + bias;
      change.defence = rand() % (1 + bias);
      change.crt = rand() % (2 + bias) + bias;
      change.dodge = rand() % (2 + bias) + bias;
      if (!(rand() % 6)) {
        change.tools.push_back("HP boost +" + to_string(rand() % 11 + 10));
      }
      if (!(rand() % 16)) {
        change.tools.push_back("full HP");
      }
      if (!(rand() % 16)) {
        change.tools.push_back("dodge " + to_string(rand() % 11 + 70)
        + "% & counter");
      }
    }
    else if (luck == 2) {
      change.fullhp = rand() % (2 + bias) + bias + 1;
      change.hp = rand() % (1 + bias) + bias + 2;
      change.pow = rand() % (2 + bias) + bias + 1;
      change.defence = rand() % (2 + bias);
      change.crt = rand() % (2 + bias) + bias;
      change.dodge = rand() % (2 + bias) + bias + 1;
      if (!(rand() % 5)) {
        change.tools.push_back("HP boost +" + to_string(rand() % 21 + 20));
      }
      if (!(rand() % 13)) {
        change.tools.push_back("full HP");
      }
      if (!(rand() % 13)) {
        change.tools.push_back("dodge " + to_string(rand() % 11 + 90) + "% & counter");
      }
    }
    else if (luck == 3) {
      change.fullhp = rand() % (3 + bias) + bias + 2;
      change.hp = rand() % (2 + bias) + bias + 3;
      change.pow = rand() % (2 + bias) + bias + 2;
      change.defence = rand() % (1 + bias) + 1;
      change.crt = rand() % (2 + bias) + bias + 1;
      change.dodge = rand() % (2 + bias) + bias + 1;
      if (!(rand() % 4)) {
        change.tools.push_back("HP boost +" + to_string(rand() % 31 + 30));
      }
      if (!(rand() % 10)) {
        change.tools.push_back("full HP");
      }
      if (!(rand() % 10)) {
        change.tools.push_back("dodge 100% & counter");
      }
    }
  }
  stats_change(S, change, !(badluck));
  print_stats(original, S, luck);
}

// move backwards after spike damage
char back(char x) {
  switch (x) {
    case('w'):
      return 's';
      break;
    case('a'):
      return 'd';
      break;
    case('s'):
      return 'w';
      break;
    default:
      return 'a';
      break;
  }
}

// to change from 1 zone to another by tracking arrows
void zone_change(zone &Z, zone &Y, pos &l, char c) {
  char original = Z.zonename[0], towards = Y.zonename[0];
  // for adjustment of which box out with exits spanning multiple blocks
  int leftshift = 0, upshift = 0;
  if (l.x == 0 || l.x == 11) {
    while (Z.grid[l.x][l.y + 1].find(towards) != -1) {
      leftshift += 1; l.y += 1;  // position to right, left shift to balance
    }
  }
  if (l.y == 0 || l.y == 11) {
    while (Z.grid[l.x + 1][l.y].find(towards) != -1) {
      upshift += 1; l.x += 1;  // position down, up shift to balance
    }
  }
  // find original zonename character in towards zone
  for (int i = 0; i < 12; ++i) {
  	for (int j = 0; j < 12; ++j) {
      if (Y.grid[i][j].find(original) != -1) {
    	  l.x = i - upshift; l.y = j - leftshift;
  	  }
    }
  }
  // get inside the 10 x 10 grid
  l.x -= (c == 'w') ? 1 : 0; l.x += (c == 's') ? 1 : 0;
  l.y -= (c == 'a') ? 1 : 0; l.y += (c == 'd') ? 1 : 0;
  Y.grid[l.x][l.y] = " ♀ ";  // assume nothing next to the arrow
}

// move from one location to another, possibly across zones
void return_to(zone &current, zone &towards, pos &l, pos to, char c) {
  // restore original position symbols
  if (c == '!') {
    current.grid[l.x][l.y] = "!!!";
  }
  else if (c == '^') {
    current.grid[l.x][l.y] = "^^^";
  }
  else if (c == '?') {
    current.grid[l.x][l.y] = " ? ";
  }
  else {
    current.grid[l.x][l.y] = "   ";
  }
  // assume no letters in landing spot
  towards.grid[to.x][to.y] = " ♀ ";
  l = to;
}

// procedures when dying (lives - 1)
void died(int &lives, bool &infile, map<string, zone> &zones, zone *&current,
pos &l, stats &S, char c, char file_number) {
  lives--;
  text(13);
  if (lives == 0) {  // game over
    text(14); 
    delete_file(file_number);
    cout << "Deleting file " + string(1, file_number) + "..." << endl;
    print("", 3);
    S.tools.clear(); // free up memory space;
    infile = false;
  }
  else {  // restart at Zone A (of current world) {1, 1}
    cout << "Lives: " << lives << endl;
    print("", 3);
    string current_world = string(1, (*current).zonename[1]);
    // boss fight zone has custom settings, must not restore
    if ((*current).zonename == "F1") {
      c = ' ';
    }
    return_to(*current, zones["A" + current_world], l, {1, 1}, c);
    current = &zones["A" + current_world];
    S.hp = S.fullhp;  // death grants back full HP
  }
}

void move_char(zone &Z, pos &l, char c, bool change_world) {
  if (c != 'w' && c != 'a' && c != 's' && c != 'd') {
    text(404);  // invalid
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  else {
    int o, k;
    switch(c) {
      case('w'):
        o = 0, k = -1;
        break;
      case('a'):
        o = -1, k = 0;
        break;
      case('s'):
        o = 0, k = 1;
        break;
      case('d'):
        o = 1, k = 0; 
        break;
      default:
        o = 0, k = 0;
        break;
    }
    // restore original position symbols
    if (Z.grid[l.x][l.y].find('T') != -1) {
      Z.grid[l.x][l.y] = " T ";
    }
    else if (Z.grid[l.x][l.y].find('?') != -1) {
      Z.grid[l.x][l.y] = " ? ";
    }
    else if (Z.grid[l.x][l.y].find('^') != -1) {
      Z.grid[l.x][l.y] = "^^^";
    }
    else if (Z.grid[l.x][l.y].find("✓") != -1) {
      Z.grid[l.x][l.y] = " ✓ ";
    }
    else if (Z.grid[l.x][l.y].find('|') != -1) {
      Z.grid[l.x][l.y] = " | ";
    }
    else if (Z.grid[l.x][l.y].find('-') != -1) {
      Z.grid[l.x][l.y] = "---";
    }
    else {
      Z.grid[l.x][l.y] = "   ";
    }
    // check if allow to move as cmd has told
    if (l.x + k > 0 && l.x + k < 11 && l.y + o > 0 && l.y + o < 11 &&
    Z.grid[l.x + k][l.y + o] != " X ") {  // inside 10 x 10 grid & not barrier
      l.x += k; l.y += o;
      // update new position symbols
      if (Z.grid[l.x][l.y] == " T ") {
        Z.grid[l.x][l.y] = "♀T "; 
      }     
      else if (Z.grid[l.x][l.y] == "!!!") {
        Z.grid[l.x][l.y] = "!♀!";
      }
      else if (Z.grid[l.x][l.y] == " ? ") {
        Z.grid[l.x][l.y] = "♀? ";
      }
      else if (Z.grid[l.x][l.y] == "^^^") {
        Z.grid[l.x][l.y] = "^♀^";
      }
      else if (Z.grid[l.x][l.y] == " ✓ ") {
        Z.grid[l.x][l.y] = "♀✓ ";
      }
      else if (Z.grid[l.x][l.y] == " | ") {
        Z.grid[l.x][l.y] = "♀| ";
      }
      else if (Z.grid[l.x][l.y] == "---") {
        Z.grid[l.x][l.y] = "-♀-";
      }
      else {
        Z.grid[l.x][l.y] = " ♀ ";
      }
    }
    else if (Z.grid[l.x + k][l.y + o].find("->") != -1 ||
    Z.grid[l.x + k][l.y + o].find("<-") != -1 ||
    Z.grid[l.x + k][l.y + o].find("↓") != -1 ||
    Z.grid[l.x + k][l.y + o].find("↑") != -1) {  // arrows indicate change zone
      l.x += k; l.y += o;
      // print change world/zone text
      if (change_world) {
        cout << endl;
        print("Moving to World " + string(1, Z.zonename[1] + 1) + " Zone A...");
        print("", 5);
      }
      else {
        int index = (Z.grid[l.x][l.y].find("-") != -1) ? 2 : 6;
        cout << "Moving to World " << string(1, Z.zonename[1]) << " Zone ";
        cout << Z.grid[l.x][l.y][index] << "..." << endl;
        print("", 5);
      }
    }
    else {
      if (Z.grid[l.x + k][l.y + o].find("⇟") != -1 ||
      Z.grid[l.x + k][l.y + o].find("⇞") != -1) {
        text(407);  // blocked
      }
      else {
        text(404);  // invalid
      }
      // restore original position symbols if invalid cmd
      if (Z.grid[l.x][l.y].find('T') != -1) {
        Z.grid[l.x][l.y] = "♀T ";
      }
      else if (Z.grid[l.x][l.y].find('?') != -1) {
        Z.grid[l.x][l.y] = "♀? ";
      }
      else if (Z.grid[l.x][l.y].find("✓") != -1) {
        Z.grid[l.x][l.y] = "♀✓ ";
      }
      else if (Z.grid[l.x][l.y].find('|') != -1) {
        Z.grid[l.x][l.y] = "♀| ";
      }
      else if (Z.grid[l.x][l.y].find('-') != -1) {
        Z.grid[l.x][l.y] = "-♀-";
      }
      else {
        Z.grid[l.x][l.y] = " ♀ ";
      }
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

void spike(int &lives, bool &infile, map<string, zone> &zones, zone *&current, pos &l, stats &S, char c, char cmd, char file_number, bool instantdeath) {
  // function call assumes '?' gives spikes
  if (c == '?') {
    (*current).grid[l.x][l.y] = "^♀^";
  }
  print_grid(*current);
  int temp;
  if (instantdeath) {  // instant death spikes
    temp = S.hp;
    text(18);
  }
  else {  // deadly spikes
    srand(time(NULL));
    temp = rand() % 20 + 30;
    text(12);
  }
  S.hp -= temp;
  cout << "Your health -"<< temp << endl;
  cout << "Your health: " << S.hp << " / " << S.fullhp << endl;
  print("", 3);
  if (S.hp <= 0) {  // death
    died(lives, infile, zones, current, l, S, c, file_number);
    return;
  }
  // if '?', restore original position symbols to prepare for backward move
  if (c == '?') {
    (*current).grid[l.x][l.y] = "♀? ";
  }
  move_char(*current, l, back(cmd));
}
