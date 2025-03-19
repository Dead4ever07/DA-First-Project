//
// Created by luis-santos on 3/9/25.
//

#include "../libs/Menu.h"

#include "libs/tc.h"
Menu::Menu() {
    menus[0] =  mainOptions;
    menus[1] =  secOptions;
    menus[2] = thirdOptions;
    g = new Graph<std::string>();
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
            get_input(Pressed);
            processKey(Pressed);
    }
}

void Menu::get_input(ACTIONS& Pressed) {
    int c = getchar();
    switch (c) {
        case(ENTR):
            Pressed = ENTER;
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
            processMenu2(Pressed);
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
        case(DOWN):
            processArrowInMenu(Pressed);
            break;
        case(ENTER):
            switch (selected_line) {
                case 0:
                    if (g != nullptr) {
                        delete g;
                        g = new Graph<std::string>();
                    }
                    graphLocation(this->g, "../resources/Locations.csv");
                    graphDistance(this->g, "../resources/Distances.csv");
                    current_menu++;
                    titles[current_menu] = mainOptions[selected_line];
                    selected_line = 0;
                    break;
                case 1:
                    if (g != nullptr) {
                        delete g;
                        g = new Graph<std::string>();
                    }
                    graphLocation(this->g, "../resources/SmallLocations.csv");
                    graphDistance(this->g, "../resources/SmallDistances.csv");
                    selected_line = 0;
                    current_menu ++;
                    break;
                case 2:
                        std::cout<<"Not Implemented\n";
                    break;
                case 3:
                    Pressed = EXIT;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Menu::processMenu2(ACTIONS & Pressed) {
    int dep;
    int arr;
    switch (Pressed) {
        case(UP):
        case(DOWN):
            processArrowInMenu(Pressed);
        break;
        case(ENTER):
            switch (selected_line) {
                case(0):
                    dep = getUserInput("Departure:");
                    arr = getUserInput("Arrival:");
                    clear_screen();
                    std::cout<<'\n'<<"Press Enter To Return";
                    do {
                        get_input(Pressed);
                    }while (Pressed!= ENTER);

                    clear_screen();
                    break;
                case(1):
                    clear_screen();
                    std::cout<<TC_BOLD<<"Best Path\n";
                    readInput( g,"input.txt");
                    getchar();
                    //CALL readInput that should print the result to the output.txt
                break;
                case(2):
                    //Call menu that reads all the edges
                    break;
                case(3):
                    current_menu--;
                    selected_line = 0;
                    break;
                case(4):
                    Pressed = EXIT;
                    break;
            }
        default:
            break;
    }
}
void Menu::processArrowInMenu(const ACTIONS & Pressed) {
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
        default:
            break;
    }
}

/**
 * @brief Simple function that reads the user input, allowing the user to see what it is typing in the process
 * @param Attribute Sentence to be printed
 */
int Menu::getUserInput(std::string Attribute) {
    clear_screen();
    std::cout<<TC_BOLD<<titles[current_menu]<<TC_NRM<<'\n';
    std::cout<<Attribute;
    std::cout<<SHOW_CURSOR;
    tc_echo_on();
    char c = 0;
    int t = 0;
    do {
        c = getchar();
        if (c == EOF) break;
        to_int(c, t);
    }
    while (c != ENTR & c != 32);
    std::cout<<HIDE_CURSOR;
    tc_echo_off();




    return t;
}

/**
 * @brief Simple way to read the user input without filling the terminal buffer
 * @param c one of the many character of the integer input
 * @param n integer that will be incremented concatenated with the c character
 */
void to_int(const char c, int& n) {
    if (c<48 || c>57) {
        return;
    }
    n = n*10 + (c-48);
}