#include "term.hpp"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace Terminal {
#ifdef _WIN32
    char getch() {
        return _getch();
    }
    void getch(char& ch) {
        ch = _getch();
    }

    void get_terminal_size(int& rows, int& cols) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        } else {
            rows = cols = 0;
            std::cout << "Failed to get terminal size\n";
        }
    }
#else
    char getch() {
        char buf = 0;
        struct termios old = {0};
        fflush(stdout);
        if (tcgetattr(0, &old) < 0)
            perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1; old.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSANOW, &old) < 0)
            perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
            perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
            perror ("tcsetattr ~ICANON");
        return (buf);
    }

    void getch(char& ch) {
        ch = getch();
    }

    void get_terminal_size(int& rows, int& cols) {
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        rows = size.ws_row;
        cols = size.ws_col;
    }

    void clear_console() {
        std::cout << "\033[2J\033[1;1H";
    }

#endif
}

// If you won't specify all this types for int, char, string and so on then it wouldn't work,
// I dont remember exactly why but something connected with how compiler connects all
// files together
namespace Colors {
    template<typename T> void gray(const T& toOutput) {
        std::cout << "\033[0;90m" << toOutput << "\033[0m";
    }
    template void gray<int>(const int& toOutput);
    template void gray<char>(const char& toOutput);
    template void gray<std::string>(const std::string& toOutput);
    template void gray<float>(const float& toOutput);
    template void gray<double>(const double& toOutput);

    template<typename T> void green(const T& toOutput) {
        std::cout << "\033[32m" << toOutput << "\033[0m";
    }
    template void green<int>(const int& toOutput);
    template void green<char>(const char& toOutput);
    template void green<std::string>(const std::string& toOutput);
    template void green<float>(const float& toOutput);
    template void green<double>(const double& toOutput);

    template<typename T> void red(const T& toOutput) {
        std::cout << "\033[1;31m" << toOutput << "\033[0m";
    }
    template void red<int>(const int& toOutput);
    template void red<char>(const char& toOutput);
    template void red<std::string>(const std::string& toOutput);
    template void red<float>(const float& toOutput);
    template void red<double>(const double& toOutput);

    template<typename T> void underline(const T& toOutput) {
        std::cout << "\033[1;4;37m" << toOutput << "\033[0m";
    }
    template void underline<int>(const int& toOutput);
    template void underline<char>(const char& toOutput);
    template void underline<std::string>(const std::string& toOutput);
    template void underline<float>(const float& toOutput);
    template void underline<double>(const double& toOutput);

	void red_block() {
		std::cout << "\033[41m \033[0m";
	}
}
