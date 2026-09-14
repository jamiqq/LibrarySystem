#include "ItemCollection.h"
#include <iostream>

ItemCollection::ItemCollection(){
    currentCount = 0;
    capacity = 4;
    items = new Item*[capacity];
}

ItemCollection::~ItemCollection(){
    for(int i = 0; i < currentCount; i++){
        delete items[i];
    }

    delete[] items;
}

void ItemCollection::resize(){
    capacity = capacity * 2;
    Item **newItems = new Item*[capacity];
    for (int i = 0; i < currentCount; i++)
    {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
}

void ItemCollection::addItem(Item *item){
    for(int i = 0; i < currentCount; i++){
        if(items[i]->getId() == item->getId()){
            std::cerr << "such item already exists\n";
            return;
        };
    }
    if (currentCount == (capacity))
    {
        resize();
    }
    items[currentCount] = item;
    currentCount++;
}

void ItemCollection::removeItem(int id){
    
    int foundIndex = -1;
    for(int i = 0; i < currentCount; i++){
        if (items[i]->getId() == id)
        {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1)
    {
        std::cerr << "No item with such id found\n";
        return;
    }

    delete items[foundIndex];
    for(int i = foundIndex; i < currentCount - 1; i++){
        items[i] = items[i + 1];
    }
    currentCount--;
}

Item* ItemCollection::findItem(int id) const{
    for(int i = 0; i < currentCount; i++){
        if (items[i]->getId() == id)
        {
            return items[i];
        }
    }
    return nullptr;
}

void ItemCollection::printCatalog() const{
    for(int i = 0; i < currentCount; i++){
        items[i]->display();
        std::cout << "\n";
    }
}