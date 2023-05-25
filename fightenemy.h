#ifndef FIGHTENEMY_H
#define FIGHTENEMY_H

#include "stats.h"
#include "default.h"

using namespace std;

void print_fight(stats, stats, string);
stats enemy_stats(zone);
void character_attack(stats &, stats &, zone, bool = false);
void enemy_attack(stats &, stats &, zone);
void wrong_input(zone);
bool fight(stats &, zone);

#endif
