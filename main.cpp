#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iomanip>
#include <limits>

#include "choosefile.h"
#include "default.h"  // structs pos, zone
#include "fightenemy.h"  // fight()
#include "filemanip.h"  // load, save, delete
#include "instructions.h"  // actions, changes, consequences
#include "printgrid.h"
#include "stats.h"  // struct stat
#include "storyline.h"  // print(), text()

using namespace std;

// RPG
int main() {
  bool ingame = true;
  while (ingame) {
    map<string, zone> zones;  // the map
    zone *current;  // pointer to current zone
    int lives; // number of lives left
    stats S; // stats of character
    pos pt; // position of character
    string fragments; // super machine fragments
    char file_number = select_mode(); 
    switch (file_number) {
      case '1':
        load_file('1', current, zones, S, lives, fragments, pt);
        break;
      case '2':
        load_file('2', current, zones, S, lives, fragments, pt);
        break;
      case '3':
        load_file('3', current, zones, S, lives, fragments, pt);
        break;
      default:
        ingame = false; // leave game
        break;
    }
    if (!(ingame)) {
      break;
    }
    bool infile = true;
    char cmd;
    while (infile) {
      print_grid(*current); print_instructions();
      cin >> cmd;
      if (cmd == 'x') { // interact
        if ((*current).grid[pt.x][pt.y] == "♀T ") {  // treasure
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          open_treasure(S);
          (*current).grid[pt.x][pt.y] = " ♀ "; // treasure gone
        }
        else if ((*current).grid[pt.x][pt.y] == "♀? ") {  // question mark
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          questionmark(S, *current, zones, pt);
        }
        else {
          text(404);  // wrong command
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      }
      else if (cmd == 'z') {  // save file
        save_file(file_number, zones, S, lives, fragments);
        print("Game saved!"); print("", 3);
      }
      else if (cmd == 'h') {  // help
        cout << "d: data  w: what are we doing" << endl;
        char help = valid_two('d', 'w');  // make sure valid
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (help == 'd') {
          cout << "Lives: " << lives << endl;
          cout << "Fragments: ";
          for (int i = 0; i < fragments.size(); i++) {
            cout << '\'' << fragments[i] << '\'';
            if (i != fragments.size() - 1) {
              cout << ", ";
            }
          }
          cout << endl;
          print_stats(S, S, 0, true);  // true: help mode
        }
        else {
          text(420);  // explain the goal
        }
      }
      else if (cmd == 'q') {  // quit
        print("Are you sure you want to quit the gameplay?");
        print("y: yes  n: no");
        char yn = valid_two('y', 'n');  // make sure valid
        if (yn == 'y') {
					S.tools.clear(); // freeing the memory
          infile = false;
          text(999);
        }
      }
      else {  // move character, and all sorts of game events occur
        move_char(*current, pt, cmd);
        if ((*current).grid[pt.x][pt.y] == "!♀!") {  // enemy fight
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          print_grid(*current);
          print("", 2);
          // if the fight loses, then lose a life, return to Zone A {1, 1}
          if (!(fight(S, *current))) {
            died(lives, infile, zones, current, pt, S, '!', file_number);
          }
          if ((*current).zonename == "E1") {
            fragments += "1";
            text(101);
          }
          (*current).grid[pt.x][pt.y] = " ♀ ";
        }
        else if ((*current).grid[pt.x][pt.y] == "^♀^") {  // spikes
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          spike(lives, infile, zones, current, pt, S, '^', cmd, file_number);
        }
        else if ((*current).grid[pt.x][pt.y] == "♀? ") {  // question mark
          if (preq(*current, pt)) {  // check if '?' needs interact or not
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            prequestionmark(lives, infile, zones, current, pt, S, cmd,
            file_number); 
            if ((*current).zonename == "E2") {
              fragments += "4";
              text(103);
            }
          }
        }
        else if ((*current).grid[pt.x][pt.y].find("->") != -1 || (*current).grid[pt.x][pt.y].find("<-") != -1 ||
                 (*current).grid[pt.x][pt.y].find("↓") != -1 || (*current).grid[pt.x][pt.y].find("↑") != -1) {  // change zone
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          // characters '↓, '↑' span 3 spaces, exist "-" implies "->" or "<-"
          int index = ((*current).grid[pt.x][pt.y].find("-") != -1) ? 2 : 6;
          string towards = string(1, (*current).grid[pt.x][pt.y][index])
          + string(1, (*current).zonename[1]);
          // if the towards zone not in the map, add it by assignment 
          // with zonename as key and default settings
          if (!(zones.count(towards))) {
            zones[towards] = default_zones(towards);
          }
          zone_change(*current, zones[towards], pt, cmd);
          current = &zones[towards];  // current pointer points to towards zone
          // below: settings of zones right after entering
          if (towards == "F1") {
            boss_zone(*current, pt, true);  // true: pre W1 boss fight
            text(100);
            if (!(fight(S, *current))) {
              died(lives, infile, zones, current, pt, S, '!', file_number);
              for (int i = 4; i <= 7; i++) {
                for (int j = 8; j <= 10; j++) {
                  zones["F1"].grid[i][j] = "???";  // turn "!!!" back to "???"
                }
              }
            }
            else {  // win W1 boss fight
              fragments += "3";
              text(102);
              boss_zone(*current, pt, false);  // false: post W1 boss fight
              zones["A2"] = default_zones("A2");
              zones["C2"] = default_zones("C2");  // for loading puzzle in C2
              return_to(*current, zones["A2"], pt, {1, 1});
              current = &zones["A2"];
            }
          }
          else if (towards == "E2" && zones[towards].grid[6][6] == " ? ") {
            zones[towards].grid[0][1] = "⇞⇞B";  // obstacles blocking way out
            text(22);
          }
          else if (towards == "G2") {
            boss_zone(*current, pt, true);  // true: pre W2 (final) boss fight
            text(100);
            if (!(fight(S, *current))) {
              died(lives, infile, zones, current, pt, S, '!', file_number);
              for (int i = 4; i <= 7; i++) {
                for (int j = 7; j <= 10; j++) {
                  zones["G2"].grid[i][j] = "???";  // turn "!!!" back to "???"
                }
              }
            }
            else {  // win W2 (final) boss fight
              fragments += "0";
              text(104); text(1000);
              delete_file(file_number);  // delete file if win game
	            S.tools.clear(); // freeing the memory
              infile = false;
            }
          }
        }
      }
    }
  }
  text(689);  // thanks for playing
  return 0;
}
