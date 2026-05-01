#include <iostream>
#include <string>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif

int main()
{
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
        "Exit"};

    int highlight = 0;

    int menuWidth = 18;
    int menu_start_x;
    int chat_start_y;
    int chat_height;

    menu_start_x = cols - menuWidth - 2;
    chat_start_y = 4;
    chat_height = rows - chat_start_y - 5;

    WINDOW *header_win = newwin(3, cols, 0, 0);
    WINDOW *menu_win = newwin(10, menuWidth, 4, menu_start_x);
    keypad(menu_win, TRUE);
    WINDOW *chat_win = newwin(chat_height, cols - menuWidth - 6, chat_start_y, 2);
    WINDOW *input_win = newwin(3, cols - menuWidth - 6, chat_start_y + chat_height, 2);

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
    bool userNameSet = false;
    std::string setName;

    std::vector<std::string> chatHistory;
    std::mutex chatMutex;
    std::atomic<bool> running(true);



#ifdef _WIN32
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        std::cerr << "Failed to create socket\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address\n";
        closesocket(clientSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    if (connect(clientSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Connection failed\n";
        closesocket(clientSocket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::thread receiver([&]() {
        char buffer[4096];

        while (running)
        {
            std::memset(buffer, 0, sizeof(buffer));
            int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesReceived > 0)
            {
                static std::string streamBuffer;

                streamBuffer.append(buffer, bytesReceived);

                size_t pos;
                while ((pos = streamBuffer.find('\n')) != std::string::npos)
                {
                    std::string msg = streamBuffer.substr(0, pos);
                    streamBuffer.erase(0, pos + 1);

                    if (!msg.empty())
                    {
                        std::lock_guard<std::mutex> lock(chatMutex);
                        chatHistory.push_back(msg);
                    }
                }
            }
            else if (bytesReceived == 0)
            {
                running = false;
                break;
            }
            else
            {
                // non-fatal in some cases; just continue loop
                continue;
            }
        }
    });
    receiver.detach();

    // MAIN LOOP TO SEND MESSAGES TO SERVER AND RECEIVE RESPONSES ===========================================

    // ==========================================================================================

    // MAIN LOOP TO HANDLE MENU NAVIGATION AND CHAT INPUT ===========================================
    while (true)
    {
        // If not in chat mode, show menu and handle navigation
        if (!chatMode)
        {
            // draw menu
            werase(menu_win);
            box(menu_win, 0, 0);

            for (int i = 0; i < (int)options.size(); i++)
            {
                if (i == highlight)
                    wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, i + 1, 2, options[i].c_str());
                if (i == highlight)
                    wattroff(menu_win, A_REVERSE);
            }

            wrefresh(menu_win);

            int ch = wgetch(menu_win);

            switch (ch)
            {
            case KEY_UP:
                highlight = (highlight == 0) ? options.size() - 1 : highlight - 1;
                break;

            case KEY_DOWN:
                highlight = (highlight == options.size() - 1) ? 0 : highlight + 1;
                break;

            case 10: // Enter
                if (options[highlight] == "Exit")
                {
                    endwin();
                    return 0;
                }

                if (options[highlight] == "Switch to Chat")
                {
                    chatMode = true;
                    werase(chat_win);
                    box(chat_win, 0, 0);
                    mvwprintw(chat_win, 1, 2, "Switched to Chat. Type message:");
                    wrefresh(chat_win);
                }
                else
                {
                    werase(chat_win);
                    box(chat_win, 0, 0);
                    mvwprintw(chat_win, 1, 2,
                              ("Selected: " + options[highlight]).c_str());
                    wrefresh(chat_win);
                }
                break;
            }
        }
        else
        {
            // IF USERNAME IS ONT
            if(userNameSet == false)
            {
                // Get user name for chat
                char name[50];
                werase(input_win);
                box(input_win, 0, 0);
                mvwprintw(input_win, 1, 2, "Enter your name: ");
                wrefresh(input_win);

                wgetnstr(input_win, name, 50);
                setName = std::string(name);
                userNameSet = true;
                continue;
            }

            // IF in CHAT MODE, HANDLE USER INPUT FOR CHAT AND COMMUNICATION WITH SERVER * SERVER IS NOT LISTENING IF NOT IN CHAT MODE, SO WE ONLY WANT TO SEND MESSAGES TO SERVER WHEN IN CHAT MODE **

            // SET WINDOW TO GET USER INPUT FOR CHAT ==================================
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 2, "Input: ");
            wrefresh(input_win);

            char str[100] = {0};
            int idx = 0;

            wtimeout(input_win, 100); // allow periodic refresh instead of blocking forever

            while (true)
            {
                int ch = wgetch(input_win);

                if (ch == ERR)
                {
                    // no input, just refresh chat continuously
                }
                else if (ch == '\n')
                {
                    str[idx] = '\0';
                    break;
                }
                else if (ch == KEY_BACKSPACE || ch == 127)
                {
                    if (idx > 0) idx--;
                    str[idx] = '\0';
                }
                else if (idx < 99)
                {
                    str[idx++] = (char)ch;
                }

                // ALWAYS refresh chat window continuously
                std::vector<std::string> snapshot;

                {
                    std::lock_guard<std::mutex> lock(chatMutex);
                    snapshot = chatHistory;
                }

                werase(chat_win);
                box(chat_win, 0, 0);

                int line = 1;
                for (auto &m : snapshot)
                {
                    mvwprintw(chat_win, line++, 2, m.c_str());
                }

                wrefresh(chat_win);

                wrefresh(input_win);
            }

            // END OF USER INPUT FOR CHAT =======================================

            // CONVERT AND HANLDE USER INPUT FROM CHAT =======================================

            std::string msg = std::string(str);
            if (msg == "menu")
            {
                chatMode = false;
                continue;
            }

            // Input Section from User for sending messages to server
            std::string input;
            char buffer[4096];

            std::cout << "> ";

            // assign input from window to message sent to server
            input = msg + "\n";
            {
                std::lock_guard<std::mutex> lock(chatMutex);
                chatHistory.push_back("Me: " + msg);
            }

            if (input == "quit")
                break;
            // SEND MESSAGE TO SERVER ************************************************************

            if (send(clientSocket, input.c_str(), input.size(), 0) < 0)
            {
                std::cerr << "Send failed\n";
                break;
            }
        }
        // END of Main Loop =========================================================================================

        //===============================================================================================

    }
    running = false;
    closesocket(clientSocket);

}