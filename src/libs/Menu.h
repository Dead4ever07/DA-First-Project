//
// Created by luis-santos on 3/9/25.
//
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

#include "GraphBuilder.h"
#include "RouteSearch.h"
#include "InputUtils.h"
#include "Graph.h"



enum ACTIONS{NONE, UP, DOWN, LEFT, RIGHT ,ENTER ,EXIT};

class Menu {
public:
    Menu();
    void init();
    void run();
private:
    /**
    * @brief Captures user input and translates to the associated action and stores it in Pressed.
    * @param[out] Pressed A reference to an `ACTIONS` object associated with a user's input key
    */
    void get_input(ACTIONS& Pressed);
    /**
    * @brief Displays the menu interface to the user.
    * Each line is stored in a predefine vector<string> and the selected line is printed in blue.
    */
    void print_menu();

    /**
     * @brief Redirects the control to the function responsible to process the user's input on that menu.
     * @param Pressed Key pressed by the user
     */
    void processKey(ACTIONS &Pressed);

    /**
     * @brief Handles the logic responsible for the ACTION done by the user in the Menu 1.
     * @param Pressed Key pressed by the user
     */
    void processMenu1(ACTIONS &Pressed);
    /**
     * @brief Handles the logic responsible for the ACTION done by the user in the Menu 2.
     * @param Pressed Key pressed by the user
     */
    void processMenu2(ACTIONS &Pressed);
    /**
     * @brief Handles the logic responsible for the ACTION done by the user in the Menu 3.
     * @param Pressed Key pressed by the user
     */
    void processMenu3(ACTIONS &Pressed);
    /**
     * @brief Simple function that reads the user input, allowing the user to see what it is typing in the process.
     * @param attribute Sentence to be printed
     */
    std::string getUserInput(std::string attribute);

    /**
     * @brief Responsible for moving the chosen option if the pressed action is either Up or Down.
     * @param Pressed Action of the user
    */
    void processArrowInMenu(const ACTIONS & Pressed);

/**
 * @brief Function responsible for printing the 10 vertices of the selected page
 * @param pos Page selected
 */
void print_vertex(int pos);

    std::pmr::vector<std::string> mainOptions =
        {"Large Data Set"
        ,"Small Data Set"
        ,"Custom Data Set"
        ,"Quit(Q)"
        };
    std::pmr::vector<std::string> secOptions =
        {"Find Driving Distance Between Two Places"
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
    Graph<std::string>* g;

    int current_menu = 0;
    int selected_line = 0;
    int vertex_page = 0;
};



#endif //MENU_H