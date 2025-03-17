//
// Created by luis-santos on 3/9/25.
//
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <map>
#include <vector>
#include "libs/GraphBuilder.h"
#include "Graph.h"

#define LINE_SIZE 20


enum ACTIONS{NONE, UP, DOWN, ENTER ,EXIT};

class Menu {
public:
    Menu();
    void init();
    void run();
private:
    void get_input(ACTIONS& Pressed);
    void print_menu();
    void processKey(ACTIONS &Pressed);
    void processMenu1(ACTIONS &Pressed);
    void processMenu2(ACTIONS &Pressed);
    void processMenu3(ACTIONS &Pressed);//Not implemented
    void processMenu4(ACTIONS &Pressed);//Not implemented;
    void getUserInput(std::string);
    void processArrowInMenu(const ACTIONS & Pressed);
    std::pmr::vector<std::string> mainOptions =
        {"Large Data Set"
        ,"Small Data Set"
        ,"Custom Data Set"
        ,"Quit(Q)"
        };
    std::pmr::vector<std::string> secOptions =
        {"Find Distance Between Two Places"
        ,"Execute Input.txt"
        , "Show Vertices"
        ,"Return"
        ,"Quit(Q)"
        };
    std::pmr::vector<std::string> thirdOptions =
        {
        };
    std::map<int, std::pmr::vector<std::string>> menus;
    std::map<int, std::string> titles = {{0, "Choose Your Data Set"}};
    std::map<std::string,int> argument_map;

    Graph<std::string>* g;

    int current_menu = 0;
    int selected_line = 0;
};

void to_int(const char c, int&n);




#endif //MENU_H