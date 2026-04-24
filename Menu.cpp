#include "Menu.h"
#include "Player.h"
#include <iostream>
#include <string>

void Menu::printPlayers() const {
    if (players.empty()) {
        std::cout<<"No saves found";
        std::cin.get();
        return;
    }
    for (size_t i = 0; i <players.size(); i++)
        std::cout << *players[i] << "\n\n";
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
    if (index < 0 || index > (int)players.size()) {
        std::cout << "\nInvalid index!\n";
        std::cin.get();
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
        std::cout << "\n---" << *players[playerIdx] << "'s garden---\n\n";
        std::cout << "1 - Exit to main menu\n";
        std::cout << "2 - Head to the $hop\n";
        std::cout << "3 - Select plot of land\n";
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
                storeMenu(playerIdx);
                break;
            }
            case 3: {
                int plotIdx = players[playerIdx] -> choosePlot();
                if (plotIdx != -1) gardeningMenu(playerIdx, plotIdx);
                break;
            }
            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }

        }
    }
}

int Menu::chooseSeeds(int playerIdx) const {
    int potatoSeeds = players[playerIdx] -> getPotatoSeeds();
    int tomatoSeeds = players[playerIdx] -> getTomatoSeeds();
    if (potatoSeeds == 0 && tomatoSeeds == 0) {
        std::cout<<"There are no seedpacks in the inventory!";
        std::cin.get();
        return -1;
    }
    std::cout << "#1 Potato seedpacks: " << potatoSeeds << '\n';
    std::cout << "#2 Tomato seedpacks: " << tomatoSeeds << "\n\n";
    std::cout << "Choose seedpack index (type 0 to cancel): ";
    int index;
    std::cin >> index;
    if (index == 1 && potatoSeeds == 0) {
        std::cout << "\nThere are no potato seedpacks in the inventory!\n";
        std::cin.get();
        return -1;
    }
    if (index == 2 && tomatoSeeds == 0) {
        std::cout << "\nThere are no tomato seedpacks in the inventory!\n";
        std::cin.get();
        return -1;
    }
    if (index < 0 || index > 2) {
        std::cout << "\nInvalid index!\n";
        std::cin.get();
        return -1;
    }
    return index;
}

int Menu::chooseFertilizer(int playerIdx) const {
    int fertilizer = players[playerIdx] -> getFertilizer();
    int atomicFertilizer = players[playerIdx] -> getAtomicFertilizer();
    if (fertilizer == 0 && atomicFertilizer == 0) {
        std::cout<<"There is no fertilizer in the inventory!";
        std::cin.get();
        return -1;
    }
    std::cout << "#1 plain fertilizer " << fertilizer<< '\n';
    std::cout << "#2 atomic fertilizer " << atomicFertilizer << "\n\n";
    std::cout << "Choose seedpack index (type 0 to cancel): ";
    int index;
    std::cin >> index;
    if (index == 1 && fertilizer == 0) {
        std::cout << "\nThere is no plain fertilizer in the inventory!\n";
        std::cin.get();
        return -1;
    }
    if (index == 2 && atomicFertilizer == 0) {
        std::cout << "\nThere is no atomic fertilizer in the inventory!\n";
        std::cin.get();
        return -1;
    }
    if (index < 0 || index > 2) {
        std::cout << "\nInvalid index!\n";
        std::cin.get();
        return -1;
    }
    return index;
}

void Menu::gardeningMenu(int playerIdx, int plotIdx){
    plotIdx--;
    while(true){
        std::cout << "\n---Plot #" << plotIdx + 1 <<"---\n\n";
        std::cout << "Stats: \n";
        players[playerIdx] -> printPlotStats(plotIdx);
        std::cout << "1 - Exit to Garden\n";
        std::cout << "2 - Plant seeds\n";
        std::cout << "3 - Water land plot\n";
        std::cout << "4 - Use fertilizer\n";
        std::cout << "5 - Harvest\n";
        std::cout << "6 - Remove seedling\n";
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
                int seedType = chooseSeeds(playerIdx);
                if (seedType == 0) break;
                if (seedType != -1) players[playerIdx] -> plantSeeds(plotIdx, seedType);
                break;
            }

            case 3: {
                int aux = players[playerIdx] -> waterPlant(plotIdx);
                if (aux == -1) {
                    std::cout << "Your tank is empty!\n";
                    std::cin.get();
                }
                if (aux == -2) {
                    std::cout << "This plot's water level is max!\n";
                    std::cin.get();
                }
                break;
            }

            case 4: {
                if (players[playerIdx] -> fertilizationCheck(plotIdx)) {
                    std::cout << "This land plot has already been fertilized!\n";
                    std::cin.get();
                    break;
                }
                int fertilizerType = chooseFertilizer(playerIdx);
                if (fertilizerType == 0) break;
                if (fertilizerType != -1) players[playerIdx] -> fertilize(plotIdx, fertilizerType);
                break;
            }

            case 5: {
                break;
            }

            case 6: {
                players[playerIdx] -> emptyPlot(plotIdx);
                break;
            }

            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }

        }
    }
}

void Menu::storeMenu(int playerIdx){
    playerIdx--;
    while(true){
        std::cout << "\n---Botanic Store---\n\n";
        std::cout << "1 - Exit to Garden\n";
        std::cout << "2 - Buy\n";
        std::cout << "3 - Sell\n";
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