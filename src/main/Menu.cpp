//
// Created by luis-santos on 3/9/25.
//

#include "../libs/Menu.h"
#include "libs/tc.h"


Menu::Menu() {
    menus[0] =  mainOptions;
    menus[1] =  secOptions;
}




void Menu::init() {
    std::cout << HIDE_CURSOR;
    tc_echo_off();
    initscr();
}


void Menu::run() {
    clear_screen();
    ACTIONS Pressed = NONE;
    while (Pressed != ACTIONS::EXIT)
        {
            clear_screen();
            print_menu();
            get_input(Pressed);
            processKey(Pressed);
    }
}



void Menu::get_input(ACTIONS& Pressed) {
    int c = getchar();
    switch (c) {
        case(27):
            c = getchar();
            switch (c) {
                case(91):
                    c = getchar();
                    switch(c) {
                        case(65):
                            Pressed = UP;
                            break;
                        case(66):
                            Pressed = DOWN;
                            break;
                        default:
                            Pressed = NONE;
                            break;
                    }
                    break;
                default:
                    Pressed = NONE;
                    break;
            }
            break;
        case(13):
            Pressed = ENTER;
        break;
        case(81):
        case(113):
            Pressed = EXIT;
        break;
        default: Pressed = NONE;
    }
}


void Menu::print_menu() {
    int index = 0;
    int x = 0, y = 0;
    tc_get_cols_rows(&x,&y);
    x = x/2 - LINE_SIZE/2;
    y = y/2 - menus[current_menu].size()/2 - 1;
    move_cursor(x+((LINE_SIZE-titles[current_menu].size())/2),y-2);
    std::cout<<TC_BOLD<<titles[current_menu]<<TC_NRM;
    for (auto p : menus[current_menu]) {
        move_cursor(x,y+index);
        if (index == selected_line) std::cout<<TC_BOLD<<TC_BLUE;
        if (p != *(--menus[current_menu].end())) {
            std::cout<<index+1<<". "<<p;
        }else {
            std::cout<<0<<". "<<p;
        }
        if (index == selected_line) std::cout<<TC_NRM;
        index++;
    }
}


void Menu::processKey(ACTIONS &Pressed) {
    switch (Pressed) {
        case(UP):
            selected_line--;
            if (selected_line<0) {
                selected_line = menus[current_menu].size()-1;
            }
            break;
        case(DOWN):
            selected_line = (selected_line+1)%menus[current_menu].size();
            break;
        case(ENTER):
            if (selected_line == menus[current_menu].size()-1) Pressed = EXIT;
            else {
                titles[current_menu+1] = menus[current_menu][selected_line];
                current_menu ++;
            }
        default:
            break;
    }
}
