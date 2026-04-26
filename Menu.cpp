#include "Menu.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <random>

Menu::~Menu() {
    for (Player* p: players)
        delete p;
}

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
    try {
        std::cin >> index;
        if (std::cin.fail()) throw std::runtime_error("Invalid input!");
    } catch (std::runtime_error& e) {
        std::cout << "Error: " << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore();
    }
    std::cin.get();
    if (index < 0 || index > static_cast<int>(players.size())) {
        std::cout << "\nInvalid index!\n";
        std::cin.get();
        return -1;
    }
    return index;
}

void Menu::mainMenu() {
    while(true){
        std::cout << "\n---Main Menu---\n\n";
        std::cout << "1 - Select farmer\n";
        std::cout << "2 - New Game\n";
        std::cout << "3 - Exit\n";
        std::cout << "\nOption: ";

        int option;
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
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
                players[players.size() - 1] -> setWeather();
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

void Menu::skip(int playerIdx) {
    players[playerIdx] -> setCurrentWeek(players[playerIdx] -> getCurrentWeek() + 1);
    players[playerIdx] -> setWeather();
    players[playerIdx] -> updateCrops();
    store.resetRagebait();
    store.resetPrices();
}

void Menu::gardenMenu(int playerIdx) {
    playerIdx--;
    while(true){
        if (playerIdx >= static_cast<int>(players.size())) return;
        std::cout << "\n========= WEEK " << players[playerIdx] -> getCurrentWeek() << " =========\n\n";
        std::cout << "---" << *players[playerIdx] << "'s garden---\n\n";
        std::cout << "1 - Exit to main menu\n";
        std::cout << "2 - View farmer's stats\n";
        std::cout << "3 - Head to the $hop\n";
        std::cout << "4 - Select plot of land\n";
        std::cout << "5 - Skip the week\n";
        std::cout << "\nOption: ";

        int option;
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin.ignore();
        std::cout << '\n';

        switch(option){
            case 1: {
                return;
            }
            case 2: {
                players[playerIdx] -> printStats();
                break;
            }
            case 3: {
                storeMenu(playerIdx);
                break;
            }
            case 4: {
                int plotIdx = players[playerIdx] -> choosePlot();
                if (plotIdx != -1) gardeningMenu(playerIdx, plotIdx);
                break;
            }
            case 5: {
                skip(playerIdx);
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
        std::cout<<"There are no seed packs in the inventory!";
        std::cin.get();
        return -1;
    }
    std::cout << "#1 Potato seed packs: " << potatoSeeds << '\n';
    std::cout << "#2 Tomato seed packs: " << tomatoSeeds << "\n\n";
    std::cout << "Choose seed pack index (type 0 to cancel): ";
    int index;
    try {
        std::cin >> index;
        if (std::cin.fail()) throw std::runtime_error("Invalid input!");
    } catch (std::runtime_error& e) {
        std::cout << "Error: " << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore();
    }
    if (index == 1 && potatoSeeds == 0) {
        std::cout << "\nThere are no potato seed packs in the inventory!\n";
        std::cin.get();
        return -1;
    }
    if (index == 2 && tomatoSeeds == 0) {
        std::cout << "\nThere are no tomato seed packs in the inventory!\n";
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
    std::cout << "Choose seed pack index (type 0 to cancel): ";
    int index;
    try {
        std::cin >> index;
        if (std::cin.fail()) throw std::runtime_error("Invalid input!");
    } catch (std::runtime_error& e) {
        std::cout << "Error: " << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore();
    }
    if (index == 1 && fertilizer == 0) {
        std::cout << "\nThere is no plain fertilizer in the inventory!";
        std::cin.get();
        return -1;
    }
    if (index == 2 && atomicFertilizer == 0) {
        std::cout << "\nThere is no atomic fertilizer in the inventory!";
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

bool Menu::unlucky() const {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    if (dist(gen) < 35) return true;
    return false;
}

void Menu::gameOver(int playerIdx) {
    delete players[playerIdx];
    players.erase(players.begin() + playerIdx);
}

void Menu::gardeningMenu (int playerIdx, int plotIdx) {
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
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
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
                    std::cout << "Your tank is empty!";
                    std::cin.get();
                }
                if (aux == -2) {
                    std::cout << "This plot's water level is max!";
                    std::cin.get();
                }
                break;
            }

            case 4: {
                if (players[playerIdx] -> fertilizationCheck(plotIdx)) {
                    std::cout << "This land plot has already been fertilized!";
                    std::cin.get();
                    break;
                }
                int fertilizerType = chooseFertilizer(playerIdx);
                if (fertilizerType == 0) break;
                if (fertilizerType != -1) players[playerIdx] -> fertilize(plotIdx, fertilizerType);
                break;
            }

            case 5: {
                if (players[playerIdx] -> emptyCheck(plotIdx)) {
                    std::cout << "This plot is empty!";
                    std::cin.get();
                    break;
                }
                if (players[playerIdx] -> growthCheck(plotIdx) != 1) {
                    std::cout << "This crop has not grown!";
                    std::cin.get();
                    break;
                }
                if (players[playerIdx] -> radioactivityCheck(plotIdx) && unlucky()) {
                    std::cout << "Oh no... The radiation gave birth to a vicious beast!";
                    std::cin.get();
                    bool survived = players[playerIdx] -> initiateFight(plotIdx);
                    if (!survived) {
                        gameOver(playerIdx);
                        return;
                    }
                    break;
                } else {
                    players[playerIdx] -> harvest(plotIdx);
                    break;
                }
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

void Menu::storeMenu(int playerIdx) {
    while(true){
        std::cout << "\n---Botanic Store---\n\n";
        std::cout << "1 - Exit to Garden\n";
        std::cout << "2 - Buy\n";
        std::cout << "3 - Sell\n";
        std::cout << "4 - fill up water tank\n";
        std::cout << "\nOption: ";

        int option;
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin.ignore();
        std::cout << '\n';

        switch(option){
            case 1: {
                return;
            }

            case 2: {
                buy(playerIdx);
                break;
            }

            case 3: {
                sell(playerIdx);
                break;
            }

            case 4: {
                players[playerIdx] -> fillWaterTank();
                break;
            }

            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }
        }
    }
}

void Menu::buy(int playerIdx) {
    if (store.ragebaitCheck()) {
        std::cout << "You are not welcome today!";
        std::cin.get();
        return;
    }
    while(true){
        std::cout << "\nI'm looking to buy...\n\n";
        std::cout << "1 - potato seeds: " << store.getPotatoPrice() << '\n';
        std::cout << "2 - tomato seeds: " << store.getTomatoPrice() << '\n';
        std::cout << "3 - reinforced shovel: " << store.getShovelPrice() << '\n';
        std::cout << "4 - upgrade water tank: " << store.getTankPrice() << '\n';
        std::cout << "5 - medkit: " << store.getMedkitPrice() << '\n';
        std::cout << "6 - fertilizer: " << store.getFerPrice() << '\n';
        std::cout << "7 - plot of land: " << store.getPlotPrice() << '\n';
        if (store.getKnowledge() == false)
            std::cout << "8 - Ask if there is any way to make plants grow faster...\n";
        else
            std::cout << "8 - atomic fertilizer: " << store.getAtomicFerPrice() << '\n';
        std::cout << "0 - Cancel\n";
        std::cout << "\nOption: ";

        int option;
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin.ignore();
        std::cout << '\n';

        switch(option) {
            case 0: {
                return;
            }

            case 1: {
                players[playerIdx] -> buy(store, 1);
                if (store.ragebaitCheck()) return;
                break;
            }

            case 2: {
                players[playerIdx] -> buy(store, 2);
                if (store.ragebaitCheck()) return;
                break;
            }

            case 3: {
                players[playerIdx] -> upgradeShovel(store);
                if (store.ragebaitCheck()) return;
                break;
            }

            case 4: {
                players[playerIdx] -> upgradeTank(store);
                break;
            }

            case 5: {
                players[playerIdx] -> buy(store, 3);
                break;
            }

            case 6: {
                players[playerIdx] -> buy(store, 4);
                if (store.ragebaitCheck()) return;
                break;
            }

            case 7: {
                players[playerIdx] -> buy(store, 5);
                break;
            }

            case 8: {
                players[playerIdx] -> buy(store, 6);
                if (store.ragebaitCheck()) return;
                break;
            }

            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }
        }
    }
}

void Menu::sell(int playerIdx) {
    while(true) {
        std::cout << "\nI'm looking to sell...\n\n";
        std::cout << "1 - potato crates: " << store.getPotatoPayment() << '\n';
        std::cout << "2 - tomato crates: " << store.getTomatoPayment()<< '\n';
        std::cout << "0 - Cancel\n";
        std::cout << "\nOption: ";

        int option;
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin.ignore();
        std::cout << '\n';

        switch(option) {
            case 0: {
                return;
            }

            case 1: {
                int crateCnt = players[playerIdx] -> getPotatoCrates();
                if (crateCnt == 0) {
                    std::cout << "You don't have any potato crates!";
                    std::cin.get();
                    break;
                }
                int amount = 0;
                std::cout << "Choose amount: ";
                std::cin >> amount;
                std::cin.get();
                if (amount < 1 || amount > crateCnt) {
                    std::cout << "Invalid amount!";
                    std::cin.get();
                    break;
                }
                players[playerIdx] -> sellPotatoes(store,amount);
                break;
            }

            case 2: {
                int crateCnt = players[playerIdx] -> getTomatoCrates();
                if (crateCnt == 0) {
                    std::cout << "You don't have any tomato crates!";
                    std::cin.get();
                    break;
                }
                int amount = 0;
                std::cout << "Choose amount: ";
                std::cin >> amount;
                std::cin.get();
                if (amount < 1 || amount > crateCnt) {
                    std::cout << "Invalid amount!";
                    std::cin.get();
                    break;
                }
                players[playerIdx] -> sellTomatoes(store,amount);
                break;
            }

            default:{
                std::cout << "Invalid option!";
                std::cin.get();
            }
        }
    }
}