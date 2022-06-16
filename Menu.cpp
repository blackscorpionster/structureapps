#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>

using namespace std;

void renderMenu(vector<string> options);

int main()
{
  vector<string> options = {"(p) Profile", "(g) Game", "(q) Exit"};
  bool ask = true;
  int ch, x, y;
  char lineBreak[] = "\n";
  std::string message;
  
  initscr();			/* Start curses mode 		  */
  renderMenu(options);
	keypad(stdscr, true);

  // Get current position
  getyx(stdscr, y, x);
  while (true == ask) {
    ch = getch();			/* Wait for user input */
    move(y, 0);
    // Clean line from current position till the end
    clrtoeol();
    switch (ch)
    {
      case 259:
        message = "Arriba";
        break;
      case 260:
        message = "Izquierda";
        break;
      case 258:
        message = "Abajo";
        break;
      case 261:
        message = "Derecha";
        break;
      case 27:
        message = "Good bye";
        ask = false;
        break;
      default:
        message = "No valido";
        move(0, 0);
        break;
    }
    printw(message.data());
    // printw(lineBreak);
    refresh();			/* Print it on to the real screen */
  }
  // Pause
  getch();
	endwin();			/* End curses mode		  */

  return 0;
}

void renderMenu(vector<string> options)
{
  int row,col;
  std::string rows, cols;
  getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
  rows = row;
  cols = "COLUMNS:" + col + '\n';
  //printw(cols.data());
  char c  = static_cast<char>(row);
  printw();
  printw("\n");
  std::string option;
  for(int i=0; i<options.size(); i++) {
    option = options[i] + "\n";
    printw(option.data());
  }
  refresh();
}