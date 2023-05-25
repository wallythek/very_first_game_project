#ifndef DEFAULT_H
#define DEFAULT_H

#include <map>

#include "stats.h"

using namespace std;

struct zone {
  string zonename;
  string grid[12][12];
  stats enemy_range[2]; 
};

struct pos {
  int x;  // top: x = 1; bottom: x = 10;
  int y;  // leftmost: y = 1; rightmost: y = 10;
};

void default_stats(stats &);
void nothing(string [][12]);
zone default_zones(string);
void questionmark(stats &, zone &, map<string, zone> &, pos &);
void change_state(zone &, int, int);
bool preq(zone, pos);
void prequestionmark(int &, bool &, map<string, zone> &, zone *&, pos &, stats &, char, char);
void boss_zone(zone &, pos &, bool);

#endif
