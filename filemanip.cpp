#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

#include "default.h"
#include "stats.h"
#include "filemanip.h"
#include "storyline.h"

using namespace std;

void load_file(char file_number, zone * &current, map<string, zone> &zones,
stats &S, int &lives, string &fragments, pos &l) {
  text(7);
  ifstream fin;
  fin.open("savegrids" + string(1, file_number) + ".txt");
  if (fin.peek() == ifstream::traits_type::eof()) {  // new game (no text)
    zones["A1"] = default_zones("A1");  // start at "A1"
    // set all initial info
    current = &zones["A1"];
    default_stats(S);
    lives = 3;
    fragments = "ENGG";
    l = {1, 1};
    (*current).grid[l.x][l.y] = " ♀ ";
    text(2);  // intro
  }
  else {
    // read saved info one by one
    fin >> fragments >> lives >> S.fullhp >> S.hp >> S.pow >> S.defence;
    fin >> S.crt >> S.dodge;
    // required for getline for tools
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    // read tools line by line, tools and grid info separated by one empty line
    string entry;
    while (getline(fin, entry) && entry != "") {
      S.tools.push_back(entry);
    }
    // while reading zonename, assign new key to map, enter all grid info
    while (fin >> entry) {
      zones[entry] = default_zones(entry);
      for (int i = 0; i < 12; ++i) {
        for (int j = 0 ; j < 12; ++j) {
          fin >> zones[entry].grid[i][j];
          if (zones[entry].grid[i][j].find("♀") != -1) {  // locate character
            current = &zones[entry];  // current position
            l = {i, j};
          }
          if (zones[entry].grid[i][j].find("#") != -1) {  // nothing
            zones[entry].grid[i][j] = " ";
          }
          // fin skips all spaces, fill spaces where necessary
          if (zones[entry].grid[i][j].length() == 1) {
            zones[entry].grid[i][j] = " " + zones[entry].grid[i][j] + " ";
          }
          else if (zones[entry].grid[i][j].length() == 3) {
            if (zones[entry].grid[i][j].find("♀") != -1) {
              zones[entry].grid[i][j] = " " + zones[entry].grid[i][j] + " ";
            }
            else if (zones[entry].grid[i][j].find("✓") != -1) {
              zones[entry].grid[i][j] = " " + zones[entry].grid[i][j] + " ";
            }
          }
          else if (zones[entry].grid[i][j].length() == 4 ||
          zones[entry].grid[i][j].length() == 6) {
            zones[entry].grid[i][j] += " ";
          }
        }
      }
    }
  }
  cout << "Lives: " << lives << endl;
  print("", 3);
  fin.close();
}

void save_file(char file_number, map<string, zone> zones, stats S, int lives, string fragments) {
  ofstream fout("savegrids" + string(1, file_number) + ".txt");
  // output info to be saved one by one
  fout << fragments << ' ' << lives << ' ' << S.fullhp << ' ' << S.hp << ' ';
  fout << S.pow << ' ' << S.defence << ' ' << S.crt << ' ' << S.dodge << endl;
  // output tools line by line
  vector<string>::iterator i;
  for (i = S.tools.begin(); i != S.tools.end(); i++) {
    fout << *i << endl;
  }
  fout << endl; // empty line to separate tools and grid info (for load file)
  map<string, zone>::iterator itr;
  for (itr = zones.begin(); itr != zones.end(); itr++) {
    fout << (*itr).first << endl;
    for (int i = 0; i < 12; i++) {
      for (int j = 0; j < 12; j++) {
        if ((*itr).second.grid[i][j] == "   ") {
          fout << " #  ";  // replacing nothing (for load file)
        }
        else {
          fout << (*itr).second.grid[i][j] << ' ';
        }
        if (j == 11) {
          fout << endl;
        }
      }
    }
  }
  fout.close();
}

// simply reopen the file and write nothing
void delete_file(char file_number) {
  ofstream fout("savegrids" + string(1, file_number) + ".txt");
  fout.close();
}
