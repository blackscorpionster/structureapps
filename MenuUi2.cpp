#include <stdio.h>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <map>

using namespace std;

// rawcow
// ------------------------ Classes
class MenuOptionConfiguration
{
public:
    std::string type;
    std::string source;
    std::string options;
};

class MenuOption
{
public:
    int row;
    int col;
    std::string label;
    bool selected = false;
    MenuOptionConfiguration config;
};

// ----------------------- Function definitions

vector<MenuOption> renderOptions(std::map<std::string, vector<std::string>> options);

void cycleThroughOptions(vector<MenuOption> &options, int character);

void highlightMenuOption(vector<MenuOption> &options, int selectedOption);

void addUnselectedMenuColours(vector<MenuOption> options);

void enterMenuOption(vector<MenuOption> options);

void runConsoleWindow(WINDOW *console, MenuOption selectedOption);

void printToConsole(WINDOW *console, std::string text);

// Code

int main(int argc, char **argv)
{
    std::map<
        std::string,
        vector<std::string>>
        options = {
            {"Game", {"console", "./game", ""}},
            {"Profile", {"console", "./profile", ""}},
            {"Chat", {"console", "./char", ""}},
            {"Web search", {"url", "www.google.com", ""}},
            {"Clock", {"console", "./clock", ""}},
            {"Calculator", {"console", "./calculator", ""}},
            {"Exit", {"exit", "exit", ""}},
        };

    int keyCode, currentX, currentY;
    bool keepGoing = true;
    vector<MenuOption> optionsx;

    initscr();
    noecho(); // stop multiple characters pressed at once
    cbreak(); // One character at a time

    keypad(stdscr, TRUE);

    printw("Util: \n\n");

    // Print menu options
    optionsx = renderOptions(options);
    // Get the screen position right after rendering the options
    getyx(stdscr, currentY, currentX);

    addUnselectedMenuColours(optionsx);
    // This higlights the first option in the menu by default
    highlightMenuOption(optionsx, 0);

    while (keepGoing)
    {
        // Reset the cursor position to the input box (last line)
        move(currentY, currentX);
        keyCode = getch();
        switch (keyCode)
        {
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        // Enter
        case 10:
            // Executes the menu action
            enterMenuOption(optionsx);
            // Reset menu/screen
            optionsx = renderOptions(options);
            break;
        default:
            printw("Unknown option (%d) - Bye!", keyCode);
            keepGoing = false;
            break;
        }
        clrtobot();
        refresh();

        // Moves the cursor around he menu
        cycleThroughOptions(optionsx, keyCode);
    }

    // Pause
    getch();
    endwin();

    exit(0);
}

vector<MenuOption> renderOptions(std::map<std::string, vector<std::string>> options)
{
    vector<MenuOption> optionsx;
    int currentY, currentX;
    std::string option;

    // Sets the initial positions of the menu on the main screen
    move(2, 0);

    for (const auto &[key, value] : options)
    {
        MenuOption optionObj;
        MenuOptionConfiguration optionConfig;
        option = key;

        // ***************************************
        // IMPORTANT, This renders the menu option
        printw("%s", option.data());
        // ***************************************

        // Build menu option config
        optionConfig.type = value[0];
        optionConfig.source = value[1];
        optionConfig.options = value[2];

        // Get current y/x values
        getyx(stdscr, currentY, currentX);
        optionObj.label = option;
        optionObj.row = currentY;
        optionObj.col = currentX;
        optionObj.config = optionConfig;

        // add the option to the menu objects
        optionsx.emplace_back(optionObj);

        // Moved to he next line
        printw("\n\n");
        refresh();
    }
    return optionsx;
}

void cycleThroughOptions(vector<MenuOption> &options, int character)
{
    int selectedOption;

    for (int i = 0; i < options.size(); i++)
    {
        if (true == options[i].selected)
        {
            selectedOption = i;
        }
    }

    switch (character)
    {
    case KEY_UP:
        selectedOption--;
        break;
    case KEY_DOWN:
        selectedOption++;
        break;
    default:
        break;
    }

    // Jumps to the last element of the array
    if (selectedOption < 0)
    {
        selectedOption = options.size() - 1;
    }
    // Jumps to the first element of the array if when pressing down, the position if grater than the last element
    else if (selectedOption >= options.size())
    {
        selectedOption = 0;
    }

    highlightMenuOption(options, selectedOption);
    return;
}

void highlightMenuOption(vector<MenuOption> &options, int selectedOption = 0)
{
    MenuOption option;

    if (options.size() == 0)
    {
        return;
    }

    option = options[selectedOption];
    options[selectedOption].selected = true;

    // Move to the start of the line where the menu option is currently located
    move(option.row, 0);
    // Clears the current line
    clrtoeol();

    /* Start color */
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printw("%s", option.label.data());
    attroff(COLOR_PAIR(1));
    refresh();

    // Deselect any other menu option
    for (int i = 0; i < options.size(); i++)
    {
        if (i != selectedOption)
        {
            options[i].selected = false;
        }
    }
    addUnselectedMenuColours(options);

    return;
}

/**
 * Agnostic function that changes the colour of not selected menu options
 *
 * @vector<MenuOption> options
 */
void addUnselectedMenuColours(vector<MenuOption> options)
{
    MenuOption option;
    start_color();
    for (int i = 0; i < options.size(); i++)
    {
        option = options[i];
        if (false == option.selected)
        {
            move(option.row, 0);
            clrtoeol(); // Clears the current line

            init_pair(2, COLOR_BLACK, COLOR_WHITE);
            attron(COLOR_PAIR(2));
            options[i].selected = false;
            printw("%s", option.label.data());
            attroff(COLOR_PAIR(2));
            refresh();
        }
    }
}

void enterMenuOption(vector<MenuOption> options)
{
    std::string consoleKey = "console";
    std::string urlKey = "url";
    std::string exitKey = "exit";
    MenuOption selectedOption;
    for (int i = 0; i < options.size(); i++)
    {
        if (options[i].selected == true)
        {
            selectedOption = options[i];
            break;
        }
    }

    if (selectedOption.config.type == consoleKey)
    {
        int currentX, currentY;
        getyx(stdscr, currentY, currentX);
        // Height, width, Y, X
        WINDOW *console = newwin(20, 40, 2, currentX + 15);
        refresh();

        box(console, 0, 0);
        wrefresh(console);

        // Run you code, remember adding a loop and a way oy finish it
        // Also, re-render the menu once the window is close so that the window borders are deleted
        runConsoleWindow(console, selectedOption);
        // Pause, remove once the loop inside runConsoleWindow has been coded
        getch();
        delwin(console);
    }

    if (selectedOption.config.type == urlKey)
    {
        printw("Web url %s, Yay!", selectedOption.label.data());
    }

    if (selectedOption.config.type == exitKey)
    {
        exit(0);
    }
}

void runConsoleWindow(WINDOW *console, MenuOption selectedOption)
{
    int currentX, currentY;
    char str[80];
    // printw Wil print to the main screen
    // wprintw mvwprintw Will print to the app window
    wprintw(console, "%s", selectedOption.label.data());
    // pushes x inwards

    wrefresh(console);
    sprintf(str, "Application type: %s", selectedOption.config.type.data());
    printToConsole(console, str);
    sprintf(str, "Application source: %s", selectedOption.config.source.data());
    printToConsole(console, str);

    wrefresh(console);
}

// Indents X wise the next printouts
void printToConsole(WINDOW *console, std::string text)
{
    int currentX, currentY;
    getyx(console, currentY, currentX);
    // Indents the next printouts inwards
    mvwprintw(console, currentY + 1, 1, "%s", text.data());
}
