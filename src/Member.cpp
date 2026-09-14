#include <Member.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>

int Member::nextId = 1;
Member::Member(const std::string& name)
    : name(name), id(nextId) 
    {
        nextId++;
    }

Member::~Member() {};

Member* Member::registerMember(const std::string& name){
    if (name.empty())
    {
        throw std::invalid_argument("Member name can't be empty\n");
    }
   return new Member(name);
}

bool Member::checkIsWithinLimit() const{
    return static_cast<int>(borrowedItems.size()) < borrowingLimit;
}

int Member::getId() const{
    return id;
}

void Member::addBorrowedItem(Item *item){
    borrowedItems.push_back(item);
}

void Member::removeBorrowedItem(Item *item)
{
    auto found = std::find(
        borrowedItems.begin(),
        borrowedItems.end(),
        item);

    if (found != borrowedItems.end())
    {
        borrowedItems.erase(found);
    }
}

std::string Member::getName() const {
    return name;
}