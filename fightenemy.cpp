#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#include "default.h"
#include "fightenemy.h"
#include "storyline.h"
#include "stats.h"
#include "instructions.h"

using namespace std;

void print_fight(stats enemy, stats me, string s) {
  string deh = "[";
  // 'X' for HP relative to full HP
  for (int i = 0; i < enemy.hp * 10 / enemy.fullhp; ++i) {
    deh += "X";
  }
  if (deh.length() == 1) {  // avoid confusion of no 'X' but > 0 HP
    deh += "X";
  }
  while (deh.length() < 11) {
    deh += "-";
  }
  deh += "]";
  print("+---+---+---+---+---+---+---+---+---+---+");
  print("|                                       |");
  if (s == "enemy") {  // enemy
    print("+    Enemy Health:        /()~ ~()\\     +");
    if (enemy.hp * 10 / enemy.fullhp > 5) {  // high health
      cout << "|    " + deh + "        {| _   _ |}    |" << endl;
    }
    else {  // low health
      cout << "|    " + deh + "        {| >   < |}    |" << endl;
    }
    print("+                         |  ^^^  |     +"); 
    print("|                          \\-----/      |");
    print("+                        O(       )O    +");
    print("|                          |     |      |");
    print("+                          \\_____/      +");
    print("|                          O    O       |");
    print("+                                       +");
    print("|     ^______^                          |");
    print("+    |        |                         +");
  }
  else if (s == "boss") {  // boss
    print("+    Boss Health:    (\\	~ ~  /)         +");
    print("|    " + deh + "    \\ \\\\  // /         |");
    print("+                   (  ◊   ◊  )         +"); 
    print("|  <^^^^^^^^^^^()   §\\  . .  /§  ()^^^^^|");
    print("+   \\___	   |\\\\    |	   |   //\\      +");
    print("|        \\__   | |\\   \\^^^/   /|  \\   __|");
    print("+            \\ /   \\\\  |     \\ //     \\/+");
    print("|            \\\\/_____ \\|   _   \\/_____//|");
    print("+                      \\_		 |      +");
    print("|     ^______^           \\_  _//        |");
    print("+    |        |             \\/          +");
  }
  print("|    (        )   /                     |");
  print("+    |________| </>                     +");
  print("|  ([|        |]/                       |");
  print("+    |        |                         +");
  print("|    |    |   |                         |");
  print("+    |___/\\___|                         +");
  print("|                                       |");
  print("+---+---+---+---+---+---+---+---+---+---+");
  cout << "a: attack   ";
  if (!(me.tools.empty())) {  // have tools
    cout << "t: tools";
  }
  cout << endl;
  print_tools(me);
}

stats enemy_stats(zone current) {
  srand(time(NULL));
  int fullhp = rand() % (current.enemy_range[1].fullhp - current.enemy_range[0].fullhp + 1) + current.enemy_range[0].fullhp;
  int hp = fullhp;
  int pow = rand() % (current.enemy_range[1].pow - current.enemy_range[0].pow + 1) + current.enemy_range[0].pow;
  int defence = rand() % (current.enemy_range[1].defence - current.enemy_range[0].defence + 1) + current.enemy_range[0].defence;
  int crt = rand() % (current.enemy_range[1].crt - current.enemy_range[0].crt + 1) + current.enemy_range[0].crt;
  int dodge = rand() % (current.enemy_range[1].dodge - current.enemy_range[0].dodge + 1) + current.enemy_range[0].dodge;
  return {fullhp, hp, pow, defence, crt, dodge, current.enemy_range[0].tools};
}

void character_attack(stats &S, stats &enemy, zone current, bool counter) {
  // string variables for deciding to print enemy or boss text
  string whoupper = (current.zonename == "F1" || current.zonename == "G2") ?
  "Boss" : "Enemy";
  string wholower = (current.zonename == "F1" || current.zonename == "G2") ?
  "boss" : "enemy";
  string cterupper = (counter) ? "Counter attack!" : "Attack!";
  string cterlower = (counter) ? " counter" : "";
  // counter attack cannot be dodged by enemy
  int dodged = (rand() % 100 + 1 <= enemy.dodge && !(counter)) ? 0 : 1;
  int crthit = (rand() % 100 + 1 <= S.crt) ? 2 : 1;
  int strength = (S.pow * crthit - enemy.defence >= 0) ?
  S.pow * crthit - enemy.defence : 0;
  enemy.hp -= strength * dodged;
  if (!(dodged)) {
    print("Attack!", 2);
    print("Oh no! The " + wholower + " dodged your attack!", 2);
  }
  else if (!(strength)) {  // defended
    print(cterupper, 2);
    print("Oh no! The " + wholower + " defended your" + cterlower + " attack",
    2);
  }
  else {
    if (crthit == 2) {
      print("Critical" + cterlower + " hit!", 2);
    }
    else {  // normal attack
      print(cterupper, 2);
    }
    cout << whoupper << " HP -" << strength;
    print("", 2);
  }
}

void enemy_attack(stats &S, stats &enemy, zone current) {
  srand(time(NULL));
  // string variables for deciding to print enemy or boss text
  string whoupper = (current.zonename == "F1" || current.zonename == "G2") ? "Boss" : "Enemy";
  string wholower = (current.zonename == "F1" || current.zonename == "G2") ? "boss" : "enemy"; 
  // if enemy/boss has "full HP" as tool, enemy/boss at low HP, and 50% chance
  // boss/enemy fully regenerates their HP
  if (find(enemy.tools.begin(), enemy.tools.end(), "full HP") 
  != enemy.tools.end() && enemy.hp * 10 / enemy.fullhp < 5 && rand() % 2) {
    enemy.hp = enemy.fullhp;
    enemy.tools.erase(find(enemy.tools.begin(), enemy.tools.end(), "full HP"));
    print("Oh no! The " + wholower + " has fully regenerated its HP!", 2);
  }
  else {
    int dodged = (rand() % 100 + 1 <= S.dodge) ? 0 : 1;
    int crthit = (rand() % 100 + 1 <= enemy.crt) ? 2 : 1;
    int strength = (enemy.pow * crthit - S.defence >= 0) ?
    enemy.pow * crthit - S.defence : 0;
    S.hp -= strength * dodged;
    if (!(dodged)) {
      print(whoupper + " attack...", 2);
      print("Great! You dodged the " + wholower + "'s attack!", 2);
    }
    else if (!(strength)) {  // defended
      print(whoupper + " attack...", 2);
      print("Great! You defended the " + wholower + "'s attack!", 2);
    }
    else {
      // critical hit ? critical : normal
      print(whoupper + ((crthit == 2) ? " critical hit..." : " attack..."), 2);
      cout << "Your HP -" << strength << endl;
      cout << "Your HP: " << S.hp;
      print("", 2);
    }
  }
}

void wrong_input(zone current) {
  if (current.zonename == "F1" || current.zonename == "G2") {
    print("Boss: Just die!", 2);
  }
  else {
    print("Enemy: Ha ha loser you pressed wrong!", 2);
  }
}

// return true if win, false if lose (character dead)
bool fight(stats &S, zone current) {
  // boss text is customized elsewhere (boss_fight())
  if (current.zonename != "F1" && current.zonename != "G2") {
    text(3);
    srand(time(NULL));
    text(rand() % 3 + 4);  // random enemy speech
  }
  stats enemy = enemy_stats(current);
  // attack first (final boss)
  if (find(enemy.tools.begin(), enemy.tools.end(), "attack first")
  != enemy.tools.end()) {
    enemy_attack(S, enemy, current);
  }
  char cmd;
  // while both parties not dead, the fight continues
  while (enemy.hp > 0 && S.hp > 0) {
    if (current.zonename == "F1" || current.zonename == "G2") {
      print_fight(enemy, S, "boss");
    }
    else {
      print_fight(enemy, S, "enemy");
    }
    cin >> cmd;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cmd == 'a') {
      character_attack(S, enemy, current);
      if (enemy.hp > 0) {
        enemy_attack(S, enemy, current);
      }
    }
    else if (cmd == 't') {
      if (S.tools.empty()) {  // wrong input but accepted
        print("You do not have any tools!", 2);  // enemy does not attack
      }
      else {
        bool existf = find(S.tools.begin(), S.tools.end(), "full HP")
        != S.tools.end(), existh = false, existd = false;
        for (int i = 0; i < S.tools.size(); i++) {
          if (S.tools[i][0] == 'H') {  // {H}P boost ...
            existh = true;
            break;
          }
        }
        for (int i = 0; i < S.tools.size(); i++) {
          if (S.tools[i][0] == 'd') {  // {d}odge ...
            existd = true;
            break;
          }
        }
        // print only if corresponding tools exist
        if (existf) {
          cout << "f: full HP  ";
        }
        if (existh) {
          cout << "h+{↑}: HP boost +{↑}  ";
        }
        if (existd) {
          cout << "d{%}: dodge {%}% & counter  ";
        }
        cout << "b: back" << endl;  // allow back to choose attack
        string toolcmd;
        getline(cin, toolcmd);
        bool back = false, correcth = false, correctd = false;
        // record original dodge chance if dodge tool is used
        int originaldodge;
        if (toolcmd == "f" && existf) {
          S.hp = S.fullhp;
          S.tools.erase(find(S.tools.begin(), S.tools.end(), "full HP"));
          print("Great! You have fully regenerated your HP!", 2);
        }
        else if (toolcmd[0] == 'h') {
          string substr = toolcmd.substr(1);
          vector<string>::iterator itr;
          for (itr = S.tools.begin(); itr != S.tools.end(); itr++) {
            // check if inputted number following '+' sign is correct
            if ((*itr)[0] == 'H' && (*itr).substr(9) == substr) {
              int increase = stoi(substr);  // increase HP as inputted
              int real = (S.hp + increase > S.fullhp) ?
              S.fullhp - S.hp : increase;  // avoid HP overshoot
              S.hp += real;
              cout << "Your HP +" << real << endl;
              cout << "Your HP: " << S.hp;
              print("", 2);
              S.tools.erase(itr);
              correcth = true;  // correct
              break;
            }
          }
          if (!(correcth)) {  // wrong
            wrong_input(current);
          }
        }
        else if (toolcmd[0] == 'd') {
          string substr = toolcmd.substr(1);
          vector<string>::iterator itr;
          for (itr = S.tools.begin(); itr != S.tools.end(); itr++) {
            // check if inputted number (w/o '%') following "dodge" is correct
            if ((*itr)[0] == 'd' && (*itr).substr(6, substr.length())
            == substr) {
              originaldodge = S.dodge;
              S.dodge = stoi(substr);
              S.tools.erase(itr);
              correctd = true;  // correct
              break;
            }
          }
          if (!(correctd)) {  // wrong
            wrong_input(current);
          }
        }
        else if (toolcmd == "b") {
          back = true;  // skip enemy attack, but re-print fight scene
        }
        else {
          wrong_input(current);  // invalid
        }
        if (enemy.hp > 0 && !(back)) {
          enemy_attack(S, enemy, current);
          if (correctd) {
            // counter attack
            character_attack(S, enemy, current, true);  // true: counter
            S.dodge = originaldodge;  // return to original dodge chance
          }
        }
      }
    }
    else {
      wrong_input(current);  // invalid
      enemy_attack(S, enemy, current);
    }
  }
  if (S.hp <= 0) {  // character dead
    return false;
  }
  else {  // boss/enemy dead
    if (current.zonename == "F1" || current.zonename == "G2") {
      print("WORLD " + string(1, current.zonename[1]) + " BOSS HAS FALLEN!", 3);
    }
    else {
      print("The enemy has died! You win the fight!", 3);
    }
    open_treasure(S, rand() % 2);  // treasure with 50% +ve bias
    return true;
  }
}
