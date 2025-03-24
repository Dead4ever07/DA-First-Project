//
//Inspired by Gregg Ink(https://gitlab.com/greggink/youtube_episode_control_terminal)
//

#include <unistd.h>


#ifndef TC_H
#define TC_H

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

#define TC_BOLD "\033[1m" // Sets text to bold
#define TC_NRM "\x1B[0m" // normal color
#define TC_RED "\x1B[0;31m"
#define TC_GREEN "\x1B[0;32m"
#define TC_YLW "\x1B[0;33m"
#define TC_BLUE "\x1B[0;34m"
#define TC_MAG "\x1B[0;35m"
#define TC_CYN "\x1B[0;36m"
#define TC_WHT "\x1B[0;37m"

#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED " \x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1B[47m"

#define clear_screen() write(1, "\033[H\033[2J\033[3J", 11)

#ifdef _WIN64

#include<windows.h>
#include<conio.h>

#define getchar _getch
#define TRAIL_CHR 224
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define ENTR 13

void tc_echo_off() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
        std::cerr << "Couldn't get the standard input handle" << std::endl;
    }
    DWORD mode;
    if (GetConsoleMode(hStdin, &mode)) {
        std::cerr << "Couldn't get the standard input handle" << std::endl;
    }
    mode &= ~ENABLE_ECHO_INPUT;  // Disable echo
    SetConsoleMode(hStdin, mode);
}

void tc_echo_on() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
        std::cerr << "Couldn't get the standard input handle" << std::endl;
    }
    DWORD mode;
    if (GetConsoleMode(hStdin, &mode) != 0) {
        std::cerr << "Failed to get console mode" << std::endl;
    }
    mode |= ENABLE_ECHO_INPUT;  // Enable echo
    SetConsoleMode(hStdin, mode);
}
#else
#include <sys/ioctl.h>
#include <termios.h>

#define TRAIL_CHR (c == 27 && getchar()==91)
#define ARROW_UP 65
#define ARROW_DOWN 66
#define ARROW_RIGHT 67
#define ARROW_LEFT 68
#define ENTR 10
void tc_echo_off(){
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(1, TCSANOW, &term);
}
void tc_echo_on(){
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag |= (ECHO|ICANON);
    tcsetattr(1, TCSANOW, &term);
}

#endif
#endif //TC_H
