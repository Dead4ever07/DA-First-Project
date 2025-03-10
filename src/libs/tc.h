//
//Inspired by Gregg Ink(https://gitlab.com/greggink/youtube_episode_control_terminal)
//

#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>

#ifndef TC_H
#define TC_H

/*
void clearScreen() {
#ifdef __unix__
    system("clear");
#else
    // assume windows
    system("cls");
#endif
}
*/

#define HIDE_CURSOR "\033[?25l"

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
#define tc_enter_alt_screen() puts("\033[?1049h\033[H")
#define move_cursor(x,y) printf("\033[%d;%dH", y, x);

//Return the columns and rows of the terminal
void tc_get_cols_rows(int *cols, int *rows);


void tc_get_cols_rows(int *cols, int *rows){

    struct winsize size;
    ioctl(1, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;

}
void tc_echo_off(){
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(1, TCSANOW, &term);
}
void tc_echo_on(){
    struct termios term;
    tcgetattr(1, &term);
    term.c_lflag |= ECHO;
    tcsetattr(1, TCSANOW, &term);
}
#endif //TC_H
