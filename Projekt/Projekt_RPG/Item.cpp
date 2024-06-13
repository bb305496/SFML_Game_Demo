#include "stdafx.h"
#include "Item.h"


Item::Item(unsigned level, unsigned value)
{
    this->level = level;
    this->value = value;
    this->type = ItemTypes::IT_DEFAULT;
}

Item::~Item()
{

}
