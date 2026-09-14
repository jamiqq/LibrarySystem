#pragma once
#include <string>
#include <Item.h>
#include <vector>

class Member{

    private:
    std::string name;
    int id;
    static int nextId;
    std::vector<Item*> borrowedItems;
    static const int borrowingLimit = 3;
    Member(const std::string& name);
    
    public:
    ~Member();
    static Member* registerMember(const std::string& name);
    bool checkIsWithinLimit() const;
    int getId() const;
    void addBorrowedItem(Item *item);
    void removeBorrowedItem(Item *item);
    std::string getName() const;
};