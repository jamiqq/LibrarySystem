#pragma once
#include "Item.h"

class ItemCollection{
    Item **items;
    int currentCount;
    int capacity;

    public:
    ItemCollection();

    ItemCollection(const ItemCollection&) = delete;
    ItemCollection& operator=(const ItemCollection&) = delete;

    ~ItemCollection();
    
    Item* findItem(int id) const;
    void printCatalog() const;
    void removeItem(int id);
    void addItem(Item *item);

    private:
    void resize();

    
};