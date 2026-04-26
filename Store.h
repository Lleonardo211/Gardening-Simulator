#ifndef GARDENINGSIMULATOR_STORE_H
#define GARDENINGSIMULATOR_STORE_H



class Store {
    bool knowledge;
    int ragebait;
    int potatoPrice;
    int tomatoPrice;
    int shovelPrice;
    int tankPrice;
    int medkitPrice;
    int fertilizerPrice;
    int atomicFerPrice;
    int plotPrice;

    int potatoPayment;
    int tomatoPayment;

public:
    Store();
    ~Store() {}

    int barter(int coins, int price) const;
    void increaseRagebait(int coins, int price);
    void resetRagebait() { ragebait = 0; }
    bool ragebaitCheck() const;
    void resetPrices();

    bool getKnowledge() const { return knowledge; }
    int getPotatoPrice() const { return potatoPrice; }
    int getTomatoPrice() const { return tomatoPrice; }
    int getShovelPrice() const { return shovelPrice; }
    int getTankPrice() const { return tankPrice; }
    int getMedkitPrice() const { return medkitPrice; }
    int getFerPrice() const { return fertilizerPrice; }
    int getAtomicFerPrice() const { return atomicFerPrice; }
    int getPlotPrice() const { return plotPrice; }
    int getPotatoPayment() const { return potatoPayment; }
    int getTomatoPayment() const { return tomatoPayment; }

    void setShovelPrice(int aux) { shovelPrice = aux; }
    void setTankPrice(int aux) { tankPrice = aux; }

    void setKnowledge(bool aux) { knowledge = aux; }
};



#endif //GARDENINGSIMULATOR_STORE_H
