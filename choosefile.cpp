#include <iostream>
#include <string>

#include "choosefile.h"
#include "filemanip.h"
#include "storyline.h"

using namespace std;

// allow only c1/c2 as input
char valid_two(char c1, char c2) {
  char cmd;
  while (true) {
    cin >> cmd;
    if (cmd == c1 || cmd == c2) {
      return cmd;
    }
    text(404);  // invalid
  }
}

// allow deleting files (with confirmation) in delete mode
void delete_mode() {
  char file_number, yn;
  while (true) {
    text(69);
    cin >> file_number;
    switch (file_number) {
      case '1': case '2': case '3':
        print("Are you sure you want to delete file " + string(1, file_number) + "?");
        print("y: yes  n: no");
        yn = valid_two('y', 'n');
        if (yn == 'y') {
          delete_file(file_number);
          cout << "Deleting file " + string(1, file_number) + "..." << endl;
          print("", 3);
        }
        break;
      case 's':  // back to select mode
        return;
        break;
      default:
        text(404);  // invalid
        break;
    }
  }
}

// select file to play
char select_mode() {
  char file_number, yn;
  while (true) {
    text(1);
    cin >> file_number;
    switch(file_number) {
      case '1': case '2': case '3':
        return file_number;
        break;
      case 'q':  // quit game
        print("Are you sure you want to quit the game?");
        print("y: yes  n: no");
        yn = valid_two('y', 'n');
        if (yn == 'y') {
          return file_number;
        }
        break;
      case 'd':  // to delete mode
        delete_mode();
        return select_mode();  // recursion back to select mode
        break;
      default:
        text(404);  // invalid
        break;
    }
  }
}
