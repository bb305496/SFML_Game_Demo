#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"


class Inventory
{
private:
    Item** itemArray;
    unsigned nrOfItems;
    unsigned capacity;

    void initialize();
    void nullify(const unsigned from = 0);
    void freeMemory();

public:
    Inventory(unsigned capacity);
    virtual ~Inventory();

    const unsigned& size() const;
    const unsigned& maxSize() const;


    void clear();
    const bool empty() const; 

    const bool add(Item* item);
    const bool remove(const unsigned index);

    const bool saveToFile(const std::string fileName);
    const bool loadFromFile(const std::string fileName);
};

#endif

