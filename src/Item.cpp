#include <Item.h>
#include <iostream>

int Item::nextId = 1;

Item::Item(const std::string& title, const std::string& author):
    title(title), author(author), id(nextId), available(true)
    {
        nextId++;
    }

Item::~Item() {}

void Item::display() const {
    std::cout << title << " by " << author << " (ID: " << id << ")\n";
}

bool Item::isAvailable() const{
    return available;
}

void Item::setAvailable(bool status){
    available = status;
}

int Item::getId() const{
    return id;
}
