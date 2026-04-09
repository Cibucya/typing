#pragma once

// ANSI Color Codes
#define DEFAULT_CODE "\033[0m"

#define BLACK_CODE "\033[30m"
#define DARK_RED_CODE "\033[31m"
#define DARK_GREEN_CODE "\033[32m"
#define DARK_YELLOW_CODE "\033[33m"
#define DARK_BLUE_CODE "\033[34m"
#define DARK_MAGENTA_CODE "\033[35m"
#define DARK_CYAN_CODE "\033[36m"
#define DARK_WHITE_CODE "\033[37m"

#define BRIGHT_BLACK_CODE "\033[90m"
#define BRIGHT_RED_CODE "\033[91m"
#define BRIGHT_GREEN_CODE "\033[92m"
#define BRIGHT_YELLOW_CODE "\033[93m"
#define BRIGHT_BLUE_CODE "\033[94m"
#define BRIGHT_MAGENTA_CODE "\033[95m"
#define BRIGHT_CYAN_CODE "\033[96m"
#define BRIGHT_WHITE_CODE "\033[97m"

#define BOLD_CODE "\033[1m"
#define UNDERLINE_CODE "\033[4m"
#define NO_UNDERLINE_CODE "\033[24m"
#define REVERSE_TEXT_CODE "\033[7m"
#define POSITIVE_TEXT_CODE "\033[27m"

// Terminal control
namespace Terminal {
    void clear_console();
    char getch();
    void getch(char& ch);
    void get_terminal_size(int &rows, int &cols);
}

// Color Formatting Functions
namespace Colors {
    template<typename T> void gray(const T& toOutput);
    template<typename T> void green(const T& toOutput);
    template<typename T> void red(const T& toOutput);
    template<typename T> void underline(const T& toOutput);
	void red_block();
}
