#ifndef FILEMANIP_H
#define FILEMANIP_H

#include <map>

#include "default.h"
#include "stats.h"

using namespace std;

void load_file(char, zone * &, map<string, zone> &, stats &, int &, string &, pos &);
void save_file(char, map<string, zone>, stats, int, string);
void delete_file(char);

#endif
