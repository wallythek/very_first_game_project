#ifndef STATS_H
#define STATS_H

#include <vector>

using namespace std;

struct stats {
  int fullhp;
  int hp;
  int pow;
  int defence;
  int crt;
  int dodge;
  vector<string> tools;
};

void stats_change(stats &, stats, bool = true);
void print_tools(stats);
void print_stats(stats, stats, int = 0, bool = false);

#endif
