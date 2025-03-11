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

}


void Menu::run() {

    ACTIONS Pressed = NONE;
    while (Pressed != ACTIONS::EXIT)
        {

            clear_screen();
            print_menu();
            std::cout<<"Hello\n";
            get_input(Pressed);
            processKey(Pressed);
    }
}



void Menu::get_input(ACTIONS& Pressed) {
    int c = getchar();
    std::cout<<c<<"\n";
    switch (c) {
        case(ENTR):
            Pressed = ENTER;
            std::cout<<"Hello\n";
            break;
        case(81):
        case(113):
            Pressed = EXIT;
            break;
        default:
        if (TRAIL_CHR) {
            c = getchar();
            switch(c) {
                case(ARROW_UP):
                    Pressed = UP;
                    return;
                case(ARROW_DOWN):
                    Pressed = DOWN;
                    return;
                default:
                    Pressed = NONE;
                    return;
                }
            }
            Pressed = NONE;
       }

}


void Menu::print_menu() {
    int index = 0;
    std::cout<<TC_BOLD<<titles[current_menu]<<'\n'<<TC_NRM;
    for (auto p : menus[current_menu]) {
        if (index == selected_line) std::cout<<TC_BOLD<<TC_BLUE;
        if (p != *(--menus[current_menu].end())) {
            std::cout<<index+1<<". "<<p<<'\n';
        }else {
            std::cout<<0<<". "<<p<<'\n';
        }
        if (index == selected_line) std::cout<<TC_NRM;
        index++;
    }
}


void Menu::processKey(ACTIONS &Pressed) {
    switch (current_menu) {
        case(0):
            processMenu1(Pressed);
            break;
        case(1):
           // processMenu2(Pressed);
            break;
        case(2):
            //processMenu3(Pressed);
            break;
        case(3):
            //processMenu4(Pressed);
            break;
        default:
            break;
    }
}

void Menu::processMenu1(ACTIONS &Pressed) {
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
                selected_line = 0;
            }
        default:
            break;
    }
}

