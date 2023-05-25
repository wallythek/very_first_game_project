#include <iostream>
#include <string>
#include <ctime>

#include "storyline.h"

using namespace std;

// to print and delay the storyline text
void print(string s, int delay) {
  cout << s << endl;
  time_t t = time(NULL);
  if (delay != 0) {
    while (time(NULL) < t + delay);  // delay for {delay} seconds
  }
}

void text(int k) {
  switch (k) {
    case 1:  // select mode
      print("Input the game file number to play!");
      print(string(13, ' ') + "/ ‾ \\   / ‾ \\   / ‾ \\");
      print("Game files: |  1  | |  2  | |  3  |");
      print(string(13, ' ') + "\\ _ /   \\ _ /   \\ _ /");
      print("d: delete mode  q: leave game");
      break;
    case 2:  // intro
      print("At the moment...", 3);
      print("The whole world is in danger due to an evil kingdom.", 3);
      print("The boss and the enemies are destroying the whole world!", 3);
      print("You, Donkey, have to embark on a journey", 3);
      print("to find treasure and fragments of a super machine", 3);
      print("to restore prosperity of the whole world.", 3);
      print("I am a small useful helper to help you along the way.", 3);
      print("You currently have 4 fragments: 'E', 'N', 'G', 'G'", 3);
      print("The remaining fragments are owned by enemies and bosses.", 3);
      print("You have to kill the enemies to obtain the fragments.", 3);
      print("Your final goal is to annihilate the final boss", 3);
      print("and to obtain all machine fragments to restore properity.", 3);
      print("Time to go!"); print("", 3);
      break;
    case 3:  // start enemy fight
      print(string(30, '-'));
      print("------ FIGHT ENEMY !!!! ------");
      print(string(30, '-'), 2);
      break;
    case 4:  // enemy speech (4, 5, 6)
      print("Enemy: Ha! I will defeat you!", 2);
      break;
    case 5:
      print("Enemy: Just give up. Say goodbye.", 2);
      break;
    case 6:
      print("Enemy: You can never defeat me!", 2);
      break;
    case 7:
      cout << endl << "Loading..." << endl;
      print("", 3);
      break;
    case 8:  // stats changes (8, 9, 10)
      cout << endl;
      print(string(7, '-') + " STATS CHANGE ! " + string(7, '-'));
      print(string(12, '-') + " Good " + string(12, '-'));
      print(string(30, '-'));
      break;
    case 9:
      cout << endl;
      print(string(7, '-') + " STATS CHANGE ! " + string(7, '-'));
      print(string(8, '-') + " Great One !! " + string(8, '-'));
      print(string(30, '-'));
      break;
    case 10:
      cout << endl;
      print(string(7, '-') + " STATS CHANGE ! " + string(7, '-'));
      print(string(8, '-') + " SUPER !!!!!! " + string(8, '-'));
      print(string(30, '-'));
      break;
    case 11:  // "B1" '?'
      print("Helper: The barrier at (8, 8) is removed!"); print("", 3);
      break;
    case 12:  // spikes
      print("Helper: Oh no! You stepped on some deadly spikes!");
      print("", 3);
      break;
    case 13:  // death
      print("YOU DIED.", 5);
      break;
    case 14:  // game over
      print("Lives: 0"); print("", 3);
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀");
      print("██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼");
      print("██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀");
      print("██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼");
      print("███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄");
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼");
      print("██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼");
      print("██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼");
      print("██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼");
      print("███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄");
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("", 5);
      break;
    case 15:  // "A1" '?'
      print("Helper: Some stuffs have moved..."); print("", 3);
      break;
    case 16:  // quit
      cout << endl;
      cout << "Quitting..." << endl;
      print("", 5);
      break;
    case 17:  // guaranteed badluck stats change
      cout << endl;
      print(string(7, '-') + " STATS CHANGE ! " + string(7, '-'));
      print(string(10, '-') + " Oh no... " + string(10, '-'));
      print(string(30, '-'));
      break;
    case 18:  // spikes: instant death
      print("Helper: Oh no! You stepped on instant death spikes!");
      print("", 3);
      break;
    case 19:  // "E1" '?'
      print("Helper: The hidden spikes at Zone D (10, 7) are removed!");
      print("", 3);
      break;
    case 20:  // "E2" '?' (20, 21)
      print("Helper: The obstacles between Zones B and E are removed!", 3);
      print("You can go back to Zone B!");
      print("", 3);
      break;
    case 21:
      print("Helper: The deadly spikes at (5, 2) are removed!");
      print("", 3);
      break;
    case 22:  // "E2" enter situation
      print("Helper: The path back to Zone B is blocked by obstacles...");
      print("", 3);
      break;
    case 23:  // "C2" activating 4 '?'s
      print("Helper: The barriers at Zone B (5, 10), (6, 10) are removed!");
      print("", 3);
      break;
    case 69:  // delete mode
      print("Input the game file number to delete!");
      print(string(13, ' ') + "/ ‾ \\   / ‾ \\   / ‾ \\");
      print("Game files: |  1  | |  2  | |  3  |");
      print(string(13, ' ') + "\\ _ /   \\ _ /   \\ _ /");
      print("s: select mode");
      break;
    case 100:  // boss speech
      print("");
      print("Boss: Just die!");
      print("", 2);
      break;
    case 101:  // fragments (101, 102, 103, 104)
      print("You just obtained a super machine fragment '1'!", 5);
      print("Helper: You need 3 more of these fragments...", 3);
      print("to build the super machine...", 2);
      print("to bring back prosperity to the world!", 3);
      break;
    case 102:
      print("You just obtained a super machine fragment '3'!", 5);
      print("Helper: You need 2 more of these fragments!", 3);
      break;
    case 103:
      print("You just obtained a super machine fragment '4'!", 5);
      print("Helper: You just need 1 more!", 3);
      break;
    case 104:
      print("You just obtained a super machine fragment '0'!", 5);
      print("Helper: You have gathered all fragments!", 3);
      print("'E', 'N', 'G', 'G', '1', '3', '4', '0'", 3);
      break;
    case 404:  // invalid
      print("Invalid command! Try again!");
      print("", 2);
      break;
    case 407:  // blocked
      print("Helper: You cannot go this way...");
      print("", 2);
      break;
    case 420:  // what are we doing
      print("Helper: You have to annihilate the final boss", 3);
      print("and to collect all machine fragments.", 3);
      print("This is the only way to restore prosperity to the world!", 3);
      break;
    case 689:  // quit game
      print("Thanks for playing!", 5);
      break;
    case 777:  // "C2" barriers to '?'
      print("Helper: ?????");
      print("", 3);
      break;
    case 778:  // "D2" maze
      print("The maze has changed...");
      print("", 2);
      break;
    case 999:
      cout << endl << "Quitting..." << endl;
      print("", 3);
      break; 
    case 1000:  // win
      print("The world's properity has been successfully restored!");
      print("", 5);
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼┼▄┼┼┼┼┼┼┼┼┼▄┼┼▄▄▄▄▄▄▄▄▄▄▄┼┼▄┼┼┼┼┼┼┼┼┼▄┼┼┼┼");
      print("┼▐░▌┼┼┼┼┼┼┼▐░▌▐░░░░░░░░░░░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼▐░▌┼┼┼┼┼┼┼▐░▌▐░█▀▀▀▀▀▀▀█░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼▐░▌┼┼┼┼┼┼┼▐░▌▐░▌┼┼┼┼┼┼┼▐░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼▐░█▄▄▄▄▄▄▄█░▌▐░▌┼┼┼┼┼┼┼▐░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼▐░░░░░░░░░░░▌▐░▌┼┼┼┼┼┼┼▐░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼┼▀▀▀▀█░█▀▀▀▀┼▐░▌┼┼┼┼┼┼┼▐░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌┼┼┼┼┼┼┼▐░▌▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼");
      print("┼┼┼┼┼┼▐░▌┼┼┼┼┼▐░█▄▄▄▄▄▄▄█░▌▐░█▄▄▄▄▄▄▄█░▌┼┼┼");
      print("┼┼┼┼┼┼▐░▌┼┼┼┼┼▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌┼┼┼");
      print("┼┼┼┼┼┼┼▀┼┼┼┼┼┼┼▀▀▀▀▀▀▀▀▀▀▀┼┼▀▀▀▀▀▀▀▀▀▀▀┼┼┼┼");
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("┼▄┼┼┼┼┼┼┼┼┼▄┼┼▄▄▄▄▄▄▄▄▄▄▄┼┼▄▄┼┼┼┼┼┼┼┼▄┼┼┼▄┼");
      print("▐░▌┼┼┼┼┼┼┼▐░▌▐░░░░░░░░░░░▌▐░░▌┼┼┼┼┼┼▐░▌┼▐░▌");
      print("▐░▌┼┼┼┼┼┼┼▐░▌┼▀▀▀▀█░█▀▀▀▀┼▐░▌░▌┼┼┼┼┼▐░▌┼▐░▌");
      print("▐░▌┼┼┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌▐░▌┼┼┼┼▐░▌┼▐░▌");
      print("▐░▌┼┼┼▄┼┼┼▐░▌┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌┼▐░▌┼┼┼▐░▌┼▐░▌");
      print("▐░▌┼┼▐░▌┼┼▐░▌┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌┼┼▐░▌┼┼▐░▌┼▐░▌");
      print("▐░▌┼▐░▌░▌┼▐░▌┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌┼┼┼▐░▌┼▐░▌┼▐░▌");
      print("▐░▌▐░▌┼▐░▌▐░▌┼┼┼┼┼▐░▌┼┼┼┼┼▐░▌┼┼┼┼▐░▌▐░▌┼┼▀┼");
      print("▐░▌░▌┼┼┼▐░▐░▌┼▄▄▄▄█░█▄▄▄▄┼▐░▌┼┼┼┼┼▐░▐░▌┼┼▄┼");
      print("▐░░▌┼┼┼┼┼▐░░▌▐░░░░░░░░░░░▌▐░▌┼┼┼┼┼┼▐░░▌┼▐░▌");
      print("┼▀▀┼┼┼┼┼┼┼▀▀┼┼▀▀▀▀▀▀▀▀▀▀▀┼┼▀┼┼┼┼┼┼┼┼▀▀┼┼┼▀┼");
      print("┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼");
      print("", 5);
      break;
  }
}
