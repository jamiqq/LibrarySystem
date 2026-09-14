#pragma once
#include <string>
#include <Item.h>


class Book : public Item{

    private:
    std::string ISBN;
    std::string genre;
    int pageCount;

    public:
    Book(const std::string& title, const std::string& author, const std::string& ISBN, const std::string& genre, int pageCount);
    ~Book() override;

    void display() const override;
};