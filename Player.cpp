#include "Player.h"
#include "Store.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>

int Player::playerCnt = 0;

Player::Player(const std::string& name)
    : id(playerCnt++),
      name(name),
      currentWeek(1),
      HP(100),
      medkits(0),
      coins(200),
      potatoSeeds(0),
      tomatoSeeds(0),
      potatoCrates(0),
      tomatoCrates(0),
      fertilizer(0),
      atomicFertilizer(0),
      attackEvent(false),
      taxes(30),
      offenses(0){
    for (int i =0; i < 4; i++)
        plots.push_back(new Plot());
}

Player::Player(const std::string& name,
               int currentWeek,
               int HP,
               int medkits,
               int coins,
               int potatoSeeds,
               int tomatoSeeds,
               int potatoCrates,
               int tomatoCrates,
               int fertilizer,
               int atomicFertilizer,
               bool attackEvent,
               int taxes,
               int offenses)
                   :
               id(playerCnt++),
               name(name),
               currentWeek(currentWeek),
               HP(HP),
               medkits(medkits),
               coins(coins),
               potatoSeeds(potatoSeeds),
               tomatoSeeds(tomatoSeeds),
               potatoCrates(potatoCrates),
               tomatoCrates(tomatoCrates),
               fertilizer(fertilizer),
               atomicFertilizer(atomicFertilizer),
               attackEvent(attackEvent),
               taxes(taxes),
               offenses(offenses){}

Player::Player(const Player& obj)
          : id(playerCnt++),
            name(obj.name),
            currentWeek(obj.currentWeek),
            HP(obj.HP),
            medkits(obj.medkits),
            coins(obj.coins),
            shovel(obj.shovel),
            tank(obj.tank),
            potatoSeeds(obj.potatoSeeds),
            tomatoSeeds(obj.tomatoSeeds),
            potatoCrates(obj.potatoCrates),
            tomatoCrates(obj.tomatoCrates),
            fertilizer(obj.fertilizer),
            atomicFertilizer(obj.atomicFertilizer),
            attackEvent(obj.attackEvent),
            taxes(obj.taxes),
            offenses((obj.offenses)){
    for (Plot* p : obj.plots)
        plots.push_back(new Plot(*p));
}

Player& Player::operator=(const Player& obj) {
    if (this != &obj) {
        name = obj.name;
        currentWeek =obj.currentWeek;
        HP = obj.HP;
        medkits = obj.medkits;
        coins = obj.coins;
        potatoSeeds = obj.potatoSeeds;
        tomatoSeeds = obj.tomatoSeeds;
        potatoCrates = obj.potatoCrates;
        tomatoCrates = obj.tomatoCrates;
        fertilizer = obj.fertilizer;
        atomicFertilizer = obj.atomicFertilizer;
        attackEvent = obj.attackEvent;
        taxes = obj.taxes;
        offenses = obj.offenses;
        for (Plot* p : plots) delete p;
        plots.clear();
        for (Plot* p : obj.plots)
            plots.push_back(new Plot(*p));
    }
    return *this;
}

Player::~Player() {
    for (Plot* p: plots)
        delete p;
}

void Player::printStats() const {
    std::cout << "HP: " << HP << '\n';
    std::cout << "Coins: " << coins << '\n';
    std::cout << "potato crates: " << potatoCrates << '\n';
    std::cout << "tomato crates: " << tomatoCrates << '\n';
    std::cout << "medkits: " << medkits << '\n';
    std::cout << "\nequipment:\n";
    std::cout << shovel << '\n';
    std::cout << tank << '\n';

    std::cin.get();
}

void Player::setWeather() const{
    Plot::calculateWeather();
    for (Plot* p: plots)
        p -> setWaterLevel(Plot::getRainLevel());
}

void Player::updateCrops() const {
    for (Plot* p: plots)
        p -> growPlant();
}

void Player::printPlotStats(int plotIdx) const {
    plots[plotIdx] -> printPlant();
    std::cout << "water level: " << plots[plotIdx] -> getWaterLevel() << '\n';
    std::cout << "sunlight level: " << plots[plotIdx] -> getSunlightLevel() << "/10\n";
    if (plots[plotIdx] -> getFertilization())
        std::cout << "fertilized\n\n";
    else
        std::cout << "not fertilized\n\n";
}

void Player::printPlots() const {
    for (size_t i = 0; i < plots.size(); i++) {
        std::cout << "PLot # " << i + 1 << '\n';
        std::cout << *plots[i] << '\n';
    }
}

int Player::choosePlot() const {
    std::cout << "Available land plots:\n\n";
    printPlots();
    std::cout << "Choose plot index (type 0 to cancel): ";
    int index;
    try {
        std::cin >> index;
        if (std::cin.fail()) throw std::runtime_error("Invalid input!");
    } catch (std::runtime_error& e) {
        std::cout << "Error: " << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore();
    }
    std::cin.ignore();
    if (index == 0) return -1;
    if (index < 0 || index > static_cast<int>(plots.size())) {
        std::cout << "\nInvalid index!";
        std::cin.get();
        return -1;
    }
    return index;
}

void Player::decreaseSeeds(int seedType) {
    switch (seedType) {
        case 1: {
            potatoSeeds--;
            break;
        }
        case 2: {
            tomatoSeeds--;
            break;
        }
        default: {
            std::cout << "Invalid seed type!";
            std::cin.get();
        }
    }
}

void Player::plantSeeds(int plotIdx, int seedType) {
    if (plots[plotIdx] -> empty()) {
        plots[plotIdx] -> assignPlant(seedType);
        decreaseSeeds(seedType);
    } else {
        std::cout << "\nThis plot is currently occupied!\n";
        std::cin.get();
    }
}

bool Player::emptyCheck(int plotIdx) const {
   return plots[plotIdx] -> empty();
}

bool Player::radioactivityCheck(int plotIdx) const {
    if (plots[plotIdx] -> getRadioactivity()) return true;
    return false;
}

void Player::emptyPlot(int plotIdx) const {
    plots[plotIdx] -> removePlant();
}

int Player::waterPlant(int plotIdx) {
    int waterVolume = tank.getWaterVolume();
    int plotWaterLevel = plots[plotIdx] -> getWaterLevel();
    if (waterVolume == 0 )
        return -1;
    if (plotWaterLevel == 300)
        return -2;
    int remainder = plots[plotIdx] -> increaseWaterLevel(waterVolume);
    tank.setWaterVolume(remainder);
    return 0;
}

void Player::fertilize(int plotIdx, int fertilizerType) {
    plots[plotIdx] -> increaseFertilization();
    if (fertilizerType == 2) {
        plots[plotIdx] -> increaseRadioactivity();
        atomicFertilizer--;
    } else {
        fertilizer--;
    }
}

int Player::calculateYield(int plotIdx) const{
    int crateCnt;

    static std::random_device seed;
    static std::mt19937 gen(seed());

    if (plots[plotIdx] -> getRadioactivity() == 1) {

        std::normal_distribution<> atomicDist(7.5,1);
        crateCnt = std::clamp(static_cast<int>(std::round(atomicDist(gen))), 5, 10);
        return crateCnt;
    }
    int sunlightLevel = Plot::getSunlightLevel();
    double mean = 2.5 + (sunlightLevel / 10.0) * 2.5;
    std::normal_distribution<> normalDist(mean,1);
    crateCnt = std::clamp(static_cast<int>(std::round(normalDist(gen))), 2, 5);
    return crateCnt;
}

void Player::harvest(int plotIdx) {
    int crateCnt = calculateYield(plotIdx);
    if (plots[plotIdx] -> getPlant() == "potato") {
        potatoCrates += crateCnt;
    } else {
        tomatoCrates += crateCnt;
    }
    emptyPlot(plotIdx);
}

void Player::buy(Store& store, int product) {
    int price = store.getShovelPrice();

    switch(product) {
        case 1: price = store.getPotatoPrice(); break;
        case 2: price = store.getTomatoPrice(); break;
        case 3: price = store.getMedkitPrice(); break;
        case 4: price = store.getFerPrice(); break;
        case 5: price = store.getPlotPrice(); break;
        case 6: {
            if (!store.getKnowledge()) {
                std::cout << "I might have something for you, but you have to use it at your own risk...\n\n";
                std::cout << "1 - Yes\n";
                std::cout << "2 - No\n\n";
                std::cout << "Choose option: ";
                int option;
                std::cin >> option;
                std::cin.ignore();
                if (option == 1) store.setKnowledge(true);
                return;
            } else {
                price = store.getAtomicFerPrice();
            }
            break;
        }
        default: {
            std::cout << "Incorrect type!";
            std::cin.get();
        }
    }

    if (coins < price) {
        std::cout << "Insufficient funds!... Attempt barter?\n\n";
        int option;
        std::cout << "1 - Yes\n";
        std::cout << "2 - No\n";
        std::cout << "Choose option: ";
        try {
            std::cin >> option;
            if (std::cin.fail()) throw std::runtime_error("Invalid input!");
        } catch (std::runtime_error& e) {
            std::cout << "Error: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin.ignore();
        if (option == 1) {
            int newPrice = store.barter(coins, price);
            if ( newPrice != -1) {
                std::cout << "\nYou struck a deal!";
                std::cin.get();
                switch(product) {
                    case 1: potatoSeeds++; break;
                    case 2: tomatoSeeds++; break;
                    case 3: medkits++; break;
                    case 4: fertilizer++; break;
                    case 5: plots.push_back(new Plot()); break;
                    case 6: atomicFertilizer++; break;
                    default: {
                        std::cout << "Incorrect type!";
                        std::cin.get();
                    }
                }
                coins -= newPrice;
                return;
            } else {
                std::cout << "\nNo luck! The shopkeeper gives you nasty look...";
                std::cin.get();
                store.increaseRagebait(coins, price);
                return;
            }
        }
    } else {
        setCoins(coins - price);
        switch(product) {
            case 1: potatoSeeds++; break;
            case 2: tomatoSeeds++; break;
            case 3: medkits++; break;
            case 4: fertilizer++; break;
            case 5: plots.push_back(new Plot()); break;
            case 6: atomicFertilizer++; break;
            default: {
                std::cout << "Incorrect type!";
                std::cin.get();
            }
        }
    }
}

void Player::upgradeShovel(Store& store) {
    int type = shovel.getType();
    if (type == 3) {
        std::cout << "You already own the best shovel!";
        std::cin.get();
        return;
    }
    int price =store.getShovelPrice();
    if (coins < price) {
        std::cout << "Insufficient funds!";
        std::cin.get();
        return;
    }

    switch(type) {
        case 1 : {
            shovel.mediumUpgrade();
            coins -= price;
            store.setShovelPrice(1000);
            break;
        }
        case 2 : {
            shovel.bigUpgrade();
            coins -= price;
            store.setShovelPrice(0);
            break;
        }
        default : {
            std::cout << "Incorrect type!";
            std::cin.get();
        }
    }
}

void Player::upgradeTank(Store& store) {
    int size = tank.getSize();
    if (size == 4000) {
        std::cout << "You already own the biggest tank!";
        std::cin.get();
        return;
    }
    int price =store.getTankPrice();
    if (coins < price) {
        std::cout << "Insufficient funds!";
        std::cin.get();
        return;
    }

    switch(size) {
        case 2000 : {
            tank.mediumUpgrade();
            coins -= price;
            store.setTankPrice(1000);
            break;
        }
        case 3000 : {
            tank.bigUpgrade();
            coins -= price;
            store.setTankPrice(0);
            break;
        }
        default : {
            std::cout << "Incorrect type!";
            std::cin.get();
        }
    }
}

void Player::sellPotatoes(Store& store, int amount) {
    coins += store.getPotatoPayment() * amount;
    potatoCrates -= amount;
}

void Player::sellTomatoes(Store& store, int amount) {
    coins += store.getTomatoPayment() * amount;
    tomatoCrates -= amount;
}

void Player::fillWaterTank() {
    int size = tank.getSize();
    switch (size) {
        case 2000: {
            if (coins < 80) {
                std::cout << "Insufficient funds!";
                std::cin.get();
                return;
            } else {
                tank.setWaterVolume(size);
                coins -= 80;
                break;
            }
        }
        case 3000: {
            if (coins < 120) {
                std::cout << "Insufficient funds!";
                std::cin.get();
                return;
            } else {
                tank.setWaterVolume(size);
                coins -= 120;
                break;
            }
        }
        case 4000: {
            if (coins < 160) {
                std::cout << "Insufficient funds!";
                std::cin.get();
                return;
            } else {
                tank.setWaterVolume(size);
                coins -= 160;
                break;
            }
        }
        default: {
            std::cout << "Invalid size!";
            std::cin.get();
        }
    }
}

void Player::takeDamage(int damage) {
    HP -= damage;
    if (HP < 0) HP =0;
}

void Player::lightAttack(Plant* plant) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 20) {
        int damage = shovel.getAP();
        plant -> takeDamage(damage);
        std::cout << "\nYou hit for " << damage << " HP\n";
        std::cin.get();
    } else {
        std::cout << "\nYou missed!\n";
        std::cin.get();
    }

}

void Player::normalAttack(Plant* plant) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
    if (luck > 40) {
        int damage = shovel.getAP() * 15 / 10;
        plant -> takeDamage(damage);
        std::cout << "\nYou hit for " << damage << " HP\n";
        std::cin.get();
    } else {
        std::cout << "\nYou missed!\n";
        std::cin.get();
    }

}

void Player::heavyAttack(Plant* plant) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(1,100);
    int luck = dist(gen);
        if (luck > 60) {
            int damage = shovel.getAP() * 2;
            plant -> takeDamage(damage);
            std::cout << "\nYou hit for " << damage << " HP\n";
            std::cin.get();
        } else {
            std::cout << "\nYou missed!\n";
            std::cin.get();
        }
}

bool Player::initiateFight(int plotIdx) {
    Plant* plant = plots[plotIdx] -> getPlantPtr();
    std::cout << "A mutated " << plant -> plantType() << " is attacking you! Put it back in the dirt!";
    std::cin.get();
    std::cout << "\n";

    while (HP && plant -> getHP()) {
        std::cout << " 1 - Light Attack\n";
        std::cout << " 2 - Normal Attack\n";
        std::cout << " 3 - Heavy Attack\n";
        std::cout << " 4 - Use Medkit\n";
        std::cout << "\n Choose action: ";
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
        switch (option) {
            case 1: {
                lightAttack(plant);
                break;
            }
            case 2: {
                normalAttack(plant);
                break;
            }
            case 3: {
                heavyAttack(plant);
                break;
            }
            case 4: {
                if (medkits) {
                    HP = 100;
                    medkits--;
                } else {
                    std::cout << "\nYou ran out of medkits!\n";
                    std::cin.get();
                }
                break;
            }
            default: {
                std::cout << "Invalid option";
                std::cin.get();
            }
        }

        if (!plant -> getHP()) {
            std::cout << "You defeated the plant!";
            std::cin.get();
            return true;
        }

        plant -> plantAttack(this);

        if (!HP) {
            std::cout << "You were eaten!\n";
            return false;
        }
    }
    return true;
}

void Player::updateTaxes(int amount) {
    static std::random_device seed;
    static std::mt19937 gen(seed());
    std::uniform_int_distribution<> dist(-15, 20);

    taxes = currentWeek * 20 + amount;
    if (taxes < 0) taxes = 0;
}

void Player::payTaxes() {
    if (taxes == 0) {
        std::cout << "Taxes already paid!";
        std::cin.get();
        return;
    }
    if (coins < taxes) {
        std::cout << "Insufficient funds!";
        std::cin.get();
    } else {
        coins -=taxes;
        taxes = 0;
        std::cout << "Taxes paid!";
        std::cin.get();
    }
}

void Player::save(const std::string& farmer) const {
    std::ofstream file(farmer);
    if (!file.is_open()) throw std::runtime_error("Could not open save file!");

    file << name << '\n';
    file << currentWeek << ' ' << HP << ' ' << medkits <<  ' ' << coins << '\n';
    file << potatoSeeds << ' ' << tomatoSeeds << ' '
         << potatoCrates << ' ' << tomatoCrates << ' '
         << fertilizer << ' ' << atomicFertilizer << ' '
         << attackEvent << '\n';
    file << taxes << ' ' << offenses << '\n';
    file << shovel.getType() << ' ' << shovel.getAP() << ' ' << shovel.getDurability() << '\n';
    file << tank.getSize() << ' ' << tank.getWaterVolume() << '\n';
    file << plots.size() << '\n';
    for (Plot* p : plots) {
        file << p -> getWaterLevel() << ' ' << p -> getFertilization() << ' ' << p -> getRadioactivity() << '\n';
        file << p -> getPlant() << '\n';
        if (p -> getPlant() != "none") {
            Plant* plant = p ->getPlantPtr();
            file << plant -> getGrowth() << ' ' << plant -> getHP() << ' ' << plant -> getAP() << ' ' << plant -> getToughness() << '\n';
        }
    }
    file.close();
}

Player* Player::load(const std::string& farmer) {
    std::ifstream file(farmer);
    if (!file.is_open()) throw std::runtime_error("Could not open save file!");

    std::string name;
    int currentWeek, HP, medkits, coins;
    int potatoSeeds, tomatoSeeds,
        potatoCrates, tomatoCrates,
        fertilizer, atomicFertilizer;
    int taxes, offenses;
    bool attackEvent;
    int shovelType, shovelAP, shovelDurability;
    int tankSize, tankWaterVolume;
    int plotCnt;

    std::getline(file, name);
    file >> currentWeek >> HP >> medkits >> coins;
    file >> potatoSeeds >> tomatoSeeds
         >> potatoCrates >> tomatoCrates
         >> fertilizer >> atomicFertilizer
         >> attackEvent;
    file >> taxes >> offenses;
    file >> shovelType >> shovelAP >> shovelDurability;
    file >> tankSize >> tankWaterVolume;
    file >> plotCnt;
    file.ignore();

    Player* player = new Player(name, currentWeek, HP, medkits, coins,
                                potatoSeeds,tomatoSeeds, potatoCrates,
                                tomatoCrates, fertilizer, atomicFertilizer,
                                attackEvent,taxes,offenses);

    for (int i = 0; i < plotCnt; i++) {
        int waterLevel, fertilization, radioactivity;
        std::string plantType;
        file >> waterLevel >> fertilization >> radioactivity;
        file.ignore();
        std::getline(file, plantType);

        Plot* plot = new Plot(waterLevel, fertilization, radioactivity);

        if (plantType != "none") {
            int growth, plantHP, plantAP, plantToughness;
            file >> growth >> plantHP >> plantAP >> plantToughness;
            file.ignore();
            if (plantType == "potato") plot -> assignPlant(1);
            else plot -> assignPlant(2);
            Plant* plant = plot -> getPlantPtr();
            plant -> setGrowth(growth);
            plant -> setHP(plantHP);
            plant -> setAP(plantAP);
            plant -> setToughness(plantToughness);
        }
        player -> plots.push_back(plot);
    }

    player -> shovel.setType(shovelType);
    player -> shovel.setAP(shovelAP);
    player -> shovel.setDurability(shovelDurability);
    player -> tank.setSize(tankSize);
    player -> tank.setWaterVolume(tankWaterVolume);

    file.close();
    return player;
}

std::istream& operator>>(std::istream& in, Player& obj) {
    std::cout << "Choose name: ";
    in >> obj.name;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Player& obj) {
    out << obj.name;
    return out;
}


