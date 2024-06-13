#ifndef ITEM_H
#define ITEM_H

enum ItemTypes {IT_DEFAULT = 0, IT_RANGEDWEAPON, IT_MELEEWEAPON};
enum ItemRarutues { COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC };

class Item
{
private:

protected:
    short unsigned type;
    unsigned level;
    unsigned value;

public:

    Item(unsigned level, unsigned value);
    virtual ~Item();

    virtual Item* clone() = 0;
    virtual unsigned getType() const = 0;
    virtual unsigned getLevel() const = 0;
    virtual unsigned getValue() const = 0;
};
#endif
