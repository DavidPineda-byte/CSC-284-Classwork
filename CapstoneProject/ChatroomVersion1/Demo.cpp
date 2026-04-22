#include <ncurses.h>
#include <string>
#include <vector>

int main() {
    initscr();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    curs_set(1);
    echo();
    cbreak();

    std::vector<std::string> options = {
        "Add Student",
        "View Grades",
        "Delete Record",
        "Switch to Chat",
        "Exit"
    };

    int highlight = 0;

    int menuWidth = 18;
    int menu_start_x;
    int chat_start_y;
    int chat_height;

    menu_start_x = cols - menuWidth - 2;
    chat_start_y = 4;
    chat_height = rows - chat_start_y - 5;

    WINDOW* header_win = newwin(3, cols, 0, 0);
    WINDOW* menu_win   = newwin(10, menuWidth, 4, menu_start_x);
    keypad(menu_win, TRUE);
    WINDOW* chat_win   = newwin(chat_height, cols - menuWidth - 6, chat_start_y, 2);
    WINDOW* input_win  = newwin(3, cols - menuWidth - 6, chat_start_y + chat_height, 2);

    box(header_win, 0, 0);
    mvwprintw(header_win, 1, 2, "GUI HW: Advanced C++ - Student Menu");
    wrefresh(header_win);

    box(menu_win, 0, 0);
    box(chat_win, 0, 0);
    box(input_win, 0, 0);

    mvwprintw(chat_win, 1, 2, "Chat Window");
    mvwprintw(input_win, 1, 2, "Input: ");

    wrefresh(chat_win);
    wrefresh(input_win);

    bool chatMode = false;

    std::vector<std::string> chatHistory;

    while (true) {

        if (!chatMode) {
            // draw menu
            werase(menu_win);
            box(menu_win, 0, 0);

            for (int i = 0; i < (int)options.size(); i++) {
                if (i == highlight) wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, i + 1, 2, options[i].c_str());
                if (i == highlight) wattroff(menu_win, A_REVERSE);
            }

            wrefresh(menu_win);

            int ch = wgetch(menu_win);

            switch (ch) {
                case KEY_UP:
                    highlight = (highlight == 0) ? options.size() - 1 : highlight - 1;
                    break;

                case KEY_DOWN:
                    highlight = (highlight == options.size() - 1) ? 0 : highlight + 1;
                    break;

                case 10: // Enter
                    if (options[highlight] == "Exit") {
                        endwin();
                        return 0;
                    }

                    if (options[highlight] == "Switch to Chat") {
                        chatMode = true;
                        werase(chat_win);
                        box(chat_win, 0, 0);
                        mvwprintw(chat_win, 1, 2, "Switched to Chat. Type message:");
                        wrefresh(chat_win);
                    } else {
                        werase(chat_win);
                        box(chat_win, 0, 0);
                        mvwprintw(chat_win, 1, 2,
                                  ("Selected: " + options[highlight]).c_str());
                        wrefresh(chat_win);
                    }
                    break;
            }
        }
        else {
            char str[100];

            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 2, "Input: ");
            wrefresh(input_win);

            wgetnstr(input_win, str, 100);

            std::string msg = std::string(str);

            if (msg == "menu") {
                chatMode = false;
                continue;
            }

            chatHistory.push_back(msg);

            werase(chat_win);
            box(chat_win, 0, 0);

            int line = 1;
            for (auto &m : chatHistory) {
                mvwprintw(chat_win, line++, 2, m.c_str());
            }

            wrefresh(chat_win);

            if (chatHistory.size() > (unsigned)chat_height - 3) {
                chatHistory.erase(chatHistory.begin());
            }
        }
    }

  endwin();
    return 0;
}
