#include"./../includes/utility.hpp"

#include<iostream>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

#else

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#endif

namespace utils {
    void clearTerminal() {
        std::cout<<"\033[2J\033[H";
    }

    void waitForEnter() {
        std::cin.get();
    }

    bool isKeyPressed() {
        #ifdef _WIN32
            return _kbhit();
        #else
            struct termios oldt, newt;
            int ch;
            int oldf;

            // Save the current terminal attributes
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;

            // Set the terminal to non-blocking mode
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            // Set stdin to non-blocking mode
            oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

            ch = getchar();

            // Restore the old terminal attributes
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

            // Restore stdin to blocking mode
            fcntl(STDIN_FILENO, F_SETFL, oldf);

            if (ch != EOF) {
                ungetc(ch, stdin);
                return 1;
            }

            return 0;
        #endif
    }

    char getPressedKey() {
        #if _WIN32
            return _getch();
        #else
            return getc(stdin);
        #endif
    }

    void sleep100ms() {
        #ifdef _WIN32
            Sleep(100); 
            // Sleep for a short duration to avoid high CPU usage
        #else
            usleep(100000); 
            // Sleep for 100 milliseconds on Linux
        #endif
    }

    int generateRandomNum(const int min, const int max) {
        return std::rand() % (max - min) + min;
    }
}
