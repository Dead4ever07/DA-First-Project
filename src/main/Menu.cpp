#include "../libs/Menu.h"

#include <fstream>
#include <sstream>

#include "libs/InputUtils.h"
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
            print_menu();
            get_input(Pressed);
            processKey(Pressed);
    }
}
///
/// @brief Captures user input and updates the associated action.
/// @param[out] Pressed A reference to an `ACTIONS` object where the user's input
///
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
                case(ARROW_LEFT):
                    Pressed = LEFT;
                    return;
                case(ARROW_RIGHT):
                    Pressed = RIGHT;
                    return;
                default:
                    Pressed = NONE;
                    return;
                }
            }
            Pressed = NONE;
       }

}
///
/// @brief Displays the menu interface to the user.
///
void Menu::print_menu() {
    if (current_menu == 2) return;
    clear_screen();
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
            processMenu3(Pressed);
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
                    graphLocation(this->g, "../resources/Locations/Locations.csv");
                    graphDistance(this->g, "../resources/Distances/Distances.csv");
                    current_menu++;
                    titles[current_menu] = mainOptions[selected_line];
                    selected_line = 0;
                    break;
                case 1:
                    if (g != nullptr) {
                        delete g;
                        g = new Graph<std::string>();
                    }
                    graphLocation(this->g, "../resources/Locations/SmallLocations.csv");
                    graphDistance(this->g, "../resources/Distances/SmallDistances.csv");
                    current_menu ++;
                    titles[current_menu] = mainOptions[selected_line];
                    selected_line = 0;
                    break;
                case 2:
                    if (g != nullptr) {
                        delete g;
                        g = new Graph<std::string>();
                    }
                    graphLocation(this->g, "../resources/Locations/CustomLocations.csv");
                    graphDistance(this->g, "../resources/Distances/CustomDistances.csv");
                    current_menu ++;
                    titles[current_menu] = mainOptions[selected_line];
                    selected_line = 0;
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
    std::ostringstream oss;
    std::ofstream ofs ("../resources/output.txt", std::ofstream::out);
    std::string out;
    std::string mode;
    switch (Pressed) {
        case(UP):
        case(DOWN):
            processArrowInMenu(Pressed);
        break;
        case(ENTER):
            switch (selected_line) {
                case(0):
                    oss<<"Mode:";
                    mode = getUserInput("Mode:");
                    oss<<mode;
                    oss<<"Source:";
                    oss<<getUserInput("Source:");
                    oss<<"Destination:";
                    oss<<getUserInput("Destination:");
                    if (mode == "driving-walking\n") {
                        oss<<"MaxWalkTime:";
                        oss<<getUserInput("MaxWalkTime:");
                    }
                    oss<<"AvoidNodes:";
                    oss<<getUserInput("AvoidNodes:");
                    oss<<"AvoidSegments:";
                    oss<<getUserInput("AvoidSegments:");
                    if (mode == "driving\n") {
                        oss<<("IncludeNode:");
                        oss<<(getUserInput("IncludeNode:"));
                    }
                    clear_screen();
                    std::cout<<TC_BOLD<<"Best Route:\n";
                    readInputFromString(g,oss.str(),out);
                    std::cout<<out<<'\n';
                    deselect(g);
                    deselect(this->g);
                    getchar();
                    break;
                case(1):
                    clear_screen();
                    std::cout<<TC_B_BLUE<<"Best Path:\n"<<TC_NRM;
                    readInputFromFile( g,"input.txt", out);
                    std::cout<<out<<'\n';
                    ofs<<out;
                    deselect(this->g);
                    getchar();
                break;
                case(2):
                    //Call menu that reads all the vertex
                    current_menu++;
                    titles[current_menu] = "Vertex:";
                    clear_screen();
                    std::cout<<"Press Right/Left Arrow to see the Vertex\n";
                    break;
                case(3):
                    current_menu--;
                    selected_line = 0;
                    break;
                case(4):
                    Pressed = EXIT;
                    break;
                default:
                    Pressed = NONE;
                    break;
            }
        default:
            break;
    }
    ofs.close();
}

void Menu::processMenu3(ACTIONS &Pressed) {
    //char c;
    clear_screen();
    switch (Pressed) {
        case(RIGHT):
            if (this->vertex_page+1<this->g->getNumVertex()/10 + (this->g->getNumVertex()%10>0)) {
                this->vertex_page++;
            }
            std::cout<<titles[current_menu]<<'\n';
            print_vertex(this->vertex_page, this->g);
            std::cout<<'\t'<<'<'<<this->vertex_page+1<<'/'<<this->g->getNumVertex()/10 + (this->g->getNumVertex()%10>0)<<'>'<<'\n';
            break;
        case(LEFT):
            if (this->vertex_page>0) {
                this->vertex_page--;
            }
            std::cout<<titles[current_menu]<<'\n';
            print_vertex(this->vertex_page, this->g);
            std::cout<<'\t'<<'<'<<this->vertex_page+1<<'/'<<this->g->getNumVertex()/10 + (this->g->getNumVertex()%10>0)<<'>'<<'\n';
            break;
        case(ENTER):
            current_menu--;
            break;
        default:
            std::cout<<titles[current_menu]<<'\n';
            print_vertex(this->vertex_page, this->g);
            std::cout<<'\t'<<'<'<<this->vertex_page+1<<'/'<<this->g->getNumVertex()/10 + (this->g->getNumVertex()%10>0)<<'>'<<'\n';
            break;
    }
    std::cout<<"Press ENTER to return\n";
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
std::string Menu::getUserInput(std::string Attribute) {
    clear_screen();
    std::cout<<TC_BOLD<<titles[current_menu]<<TC_NRM<<'\n';
    std::cout<<Attribute;
    std::cout<<SHOW_CURSOR;
    //tc_echo_on();
    std::string result;
    char c;
    do {
        c = getchar();
        if (c == 127 && result.size()>0) {
            std::cout<<"\b";
            std::cout<<" ";
            std::cout<<"\b";
            result.pop_back();
        }else if (c != 127) {
            result += c;
            std::cout<<c;
        }
        if (c == EOF) break;
    }
    while (c != ENTR);
    std::cout<<HIDE_CURSOR;
    //tc_echo_off();
    return result;
}


void print_vertex(int pos, Graph<std::string> *g) {
    if (pos < 0) pos = 0;
    for (int i = 0; i<10 && i+pos*10<g->getNumVertex(); i++) {
        if (g->getVertexSet()[pos*10+i] == nullptr) continue;
        std::cout<<g->getVertexSet()[pos*10+i]->getId()<<". "<<g->getVertexSet()[pos*10+i]->getLocation()<<'\n';
    }
}

