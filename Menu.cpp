#include "Menu.h"
#include <iostream>
#include <string>

void Menu::printPlayers() const {
    if (players.empty()) {
        std::cout<<"No saves found";
        std::cin.get();
        return;
    }
    for (size_t i = 0; i <players.size(); i++)
        std::cout << *players[i] << '\n';
}
int Menu::choosePlayer() const {
    if (players.empty()) {
        std::cout << "No saves found!";
        std::cin.get();
        return -1;
    }
    printPlayers();
    std::cout << "Choose player index (type 0 to cancel): ";
    int index;
    std::cin >> index;
    std::cin.ignore();
    if (index < 0 || index > (int)players.size()) {
        std::cout << "Invalid index!";
        return -1;
    }
    return index;
}

void Menu::mainMenu(){
    while(true){
        std::cout << "\n---Main Menu---\n\n";
        std::cout << "1 - Select farmer\n";
        std::cout << "2 - New Game\n";
        std::cout << "3 - Exit\n";
        std::cout << "\nOption: ";

        int option;
        std::cin >> option;
        std::cin.ignore();
        std::cout << '\n';

        switch(option){
            case 1:{
                int index = choosePlayer();
                if (index == 0) break;
                if (index != -1) gardenMenu(index);
                break;
            }
            case 2:{
                std::string name;
                std::cout << "Player name: ";
                std::getline(std::cin, name);
                Player* p = new Player(name);
                players.push_back(p);
                break;
            }
            case 3:{
                std::cout << "See you soon!\n";
                return;
            }
            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }
        }
    }
}

void Menu::gardenMenu(int playerIdx){
    playerIdx--;
    while(true){
        std::cout << "\n" << *players[playerIdx] << "'s garden\n";
        std::cout << "1 - Exit to main menu\n";
        std::cout << "2 - Head to the $hop";
        std::cout << "3 - Select plot of land";
        std::cout << "\nOption: ";

        int option;
        std::cin >> option;
        std::cin.ignore();
        std::cout << '\n';

        switch(option){
            case 1: {
                return;
            }
            case 2: {
              //  storeMenu(playerIdx);
                break;
            }
            case 3: {
               // int plotIdx = choosePlot();
               // if (plotIdx != -1) gardeningMenu(plotIdx);
                break;
            }
            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }

        }
    }
}

void Menu::gardeningMenu(int plotIdx){
    plotIdx--;
    while(true){
       // std::cout << "\n" << *plots[plotIdx] << "'s garden\n";
        std::cout << "Stats: ";
        std::cout << "1 - Exit to Garden\n";
        std::cout << "2 - Plant seeds";
        std::cout << "3 - Water plant";
        std::cout << "4 - Use fertilizer";
        std::cout << "5 - Harvest";
        std::cout << "6 - Remove seedling";
        std::cout << "\nOption: ";

        int option;
        std::cin >> option;
        std::cin.ignore();
        std::cout << '\n';

        switch(option){
            case 1: {
                return;
            }

            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }

        }
    }
}