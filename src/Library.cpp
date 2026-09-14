#include "Library.h"
#include <iostream>

Library::~Library(){
    for(size_t i = 0; i < members.size(); i++){
        delete members[i];
    }
}

void Library::addItem(Item *item){
    catalog.addItem(item);
    std::cout << item->getId() << " added successfully\n";
}

bool Library::removeItem(int id){
    Item *found = catalog.findItem(id);
    if (found)
    {
        if (!found->isAvailable())
        {
            std::cerr << "The item is not yet returned\n";
            return false;
        }else{
            int foundId = found->getId();
            catalog.removeItem(found->getId());
            std::cout << foundId << " removed successfully\n";
            return true;
        }
        
    }else{
        std::cerr << "The item is not found\n";
        return false;
    }
}

Member* Library::registerMember(const std::string &name){
    Member *m = Member::registerMember(name);
    members.push_back(m);
    return m;
}

Member* Library::findMember(int id) const{
    for(auto *m : members){
        if(m->getId() == id){
            return m;
        }
    }
    return nullptr;
}

bool Library::borrowItem(int itemId, int memberId){
    Item *foundItem = catalog.findItem(itemId);
    if (foundItem)
    {
        if (!foundItem->isAvailable())
        {
            std::cerr << "The item is unavailable for borrowing\n";
            return false;
        }
    }else{
        std::cerr << "The item is not found\n";
        return false;
    }

    Member *foundMember = findMember(memberId);
    if (foundMember)
    {
        if (!foundMember->checkIsWithinLimit())
        {
            std::cerr << "The member has reached the limit of borrowings\n";
            return false;
        }
    }else{
        std::cerr << "The member is not found\n";
        return false;
    }
    
    borrowRecords.push_back(BorrowRecord(foundItem->getId(), foundMember->getId()));
    foundMember->addBorrowedItem(foundItem);
    foundItem->setAvailable(false);
    return true;
}

bool Library::returnItem(int itemId){
    Item *foundItem = catalog.findItem(itemId);
    if (foundItem)
    {  
       if (foundItem->isAvailable())
       {
            std::cerr << "The item is not borrowed\n";
            return false;
       }
        
    }else{
        std::cerr << "Item not found\n";
        return false;
    }
    for(auto &borrowing : borrowRecords){
        if (itemId == borrowing.itemId && !borrowing.checkIsReturned())
        {
            borrowing.returned = true;
            Member *mem = findMember(borrowing.memberId);
            if (!mem)
            {
                std::cerr << "Member not found for this record\n";
                return false;
            }
            mem->removeBorrowedItem(foundItem);
            foundItem->setAvailable(true);
            return true;
        }
    }
    std::cerr << "Something went wrong...\n";
    return false;
}

void Library::printCatalog() const{
    catalog.printCatalog();
}