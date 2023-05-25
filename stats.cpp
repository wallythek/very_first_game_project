#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "stats.h"
#include "storyline.h"

using namespace std;

void stats_change(stats &S, stats change, bool add) {
  S.fullhp += change.fullhp; S.hp += change.hp + change.fullhp;
  S.pow += change.pow; S.defence += change.defence;
  S.crt += change.crt; S.dodge += change.dodge;
  if (S.hp > S.fullhp) {
    S.hp = S.fullhp;  // prevent HP overshoot
  }
  if (add) {  // add tools to tools vector
    while (!(change.tools.empty())) {
      S.tools.push_back(change.tools.back());
      change.tools.pop_back();
    }
    sort(S.tools.begin(), S.tools.end());
  }
  else {
    srand(time(NULL));
    // randomly remove specified number of items in tools vector
    for (char i = '0'; i < change.tools[0][3] && S.tools.size() != 0; i++) {
      S.tools.erase(S.tools.begin() + rand() % S.tools.size());
    }
  }
}

// show available tools
void print_tools(stats S) {
  if (!(S.tools.empty())) {
    cout << "Your tool(s): ";
    for (int i = 0; i < S.tools.size(); i++) {
      cout << S.tools[i];
      if (i != S.tools.size() - 1) {
        cout << ", ";
      }
      if (i % 2 == 0 && i != S.tools.size() - 1) {
        cout << endl;  // prevent tool wordings overshoot a line
      }
    }
    cout << endl;
  }
}

void print_stats(stats original, stats S, int luck, bool help) {
  if (help) {
    cout << "HP: " << S.hp << " / " << S.fullhp << endl;
    cout << "Power: " << S.pow << endl;
    cout << "Defence: " << S.defence << endl;
    cout << fixed << setprecision(2);
    cout << "Critical hit chance: " << S.crt / 100.0 << endl;
    cout << "Dodge chance: " << S.dodge / 100.0 << endl;
    cout.unsetf(ios_base::floatfield);
    print_tools(S); print("", 5);
  }
  else {
    if (luck == 1) {
      text(8);
    }
    else if (luck == 2) {
      text(9);
    }
    else if (luck == 3) {
      text(10);
    }
    else if (luck == -1) {
      text(17);
    }
    cout << "HP: " << original.hp << " / " << original.fullhp << " -> ";
    cout << S.hp << " / " << S.fullhp << endl;
    cout << "Power: " << original.pow << " -> " << S.pow << endl;
    cout << "Defence: " << original.defence << " -> " << S.defence << endl;
    cout << fixed << setprecision(2);
    cout << "Critical hit chance: " << original.crt / 100.0 << " -> ";
    cout << S.crt / 100.0 << endl;
    cout << "Dodge chance: " << original.dodge / 100.0 << " -> ";
    cout << S.dodge / 100.0 << endl;
    cout.unsetf(ios_base::floatfield);
    print_tools(S); print("", 5);
  }
}
