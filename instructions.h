#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <map>

#include "default.h"
#include "stats.h"

using namespace std;

void open_treasure(stats &, int = 0, bool = false);
char back(char);
void zone_change(zone &, zone &, pos &, char c);
void return_to(zone &, zone &, pos &, pos, char = ' ');
void died(int &, bool &, map<string, zone> &, zone * &, pos &, stats &, char, char);
void move_char(zone &, pos &, char, bool = false);
void spike(int &, bool &, map<string, zone> &, zone * &, pos &, stats &, char, char, char, bool = false);

#endif
