//
// Created by luis-santos on 3/9/25.
//

#include "../libs/Menu.h"

#include <fstream>
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
                    current_menu ++;
                    titles[current_menu] = mainOptions[selected_line];
                    selected_line = 0;
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
    std::string dep;
    std::string mode;
    std::ofstream ofs ("../resources/output.txt", std::ofstream::out);
    std::string out;
    switch (Pressed) {
        case(UP):
        case(DOWN):
            processArrowInMenu(Pressed);
        break;
        case(ENTER):
            switch (selected_line) {
                case(0):
                    dep.append("Mode:");
                    mode = getUserInput("Mode:");
                    dep.append(mode);
                    dep.append("Source:");
                    dep.append(getUserInput("Source:"));
                    dep.append("Destination:");
                    dep.append(getUserInput("Destination:"));
                    if (mode == "driving-walking\n") {
                        dep.append("MaxWalkTime:");
                        dep.append(getUserInput("MaxWalkTime:"));
                    }
                    dep.append("AvoidNodes:");
                    dep.append(getUserInput("AvoidNodes:"));
                    dep.append("AvoidSegments:");
                    dep.append(getUserInput("AvoidSegments:"));
                    if (mode == "driving\n") {
                        dep.append("IncludeNode:");
                        dep.append(getUserInput("IncludeNode:"));
                    }
                    clear_screen();
                    std::cout<<TC_BOLD<<"Best Route:\n";
                    readInputFromString(g,dep,out);
                    std::cout<<out<<'\n';
                    getchar();
                    break;
                case(1):
                    clear_screen();
                    std::cout<<TC_BOLD<<"Best Path\n";
                    readInputFromFile( g,"input.txt", out);
                    std::cout<<out<<'\n';
                    ofs<<out;
                    ofs.close();
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
std::string Menu::getUserInput(std::string Attribute) {
    clear_screen();
    std::cout<<TC_BOLD<<titles[current_menu]<<TC_NRM<<'\n';
    std::cout<<Attribute;
    std::cout<<SHOW_CURSOR;
    tc_echo_on();
    std::string result;
    char c;
    do {
        #ifdef WIN64
            std::cout<<c;
        #endif
        c = getchar();
        result += c;
    }
    while (c != ENTR);
    std::cout<<HIDE_CURSOR;
    tc_echo_off();
    return result;
}