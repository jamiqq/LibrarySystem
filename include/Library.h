#pragma once
#include "ItemCollection.h"
#include "Member.h"
#include "BorrowRecord.h"
#include <vector>
#include <string>


class Library{

    ItemCollection catalog;
    std::vector<Member*> members;
    std::vector<BorrowRecord> borrowRecords;

    public:
    ~Library();
    void addItem(Item *item);
    bool removeItem(int id);
    Member* registerMember(const std::string &name);
    bool borrowItem(int itemId, int memberId);
    bool returnItem(int itemId);
    void printCatalog() const;

private:
    Member* findMember(int id) const;
};