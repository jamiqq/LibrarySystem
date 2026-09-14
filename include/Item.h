#pragma once
#include <string>


class Item{
    protected:
    std::string title;
    std::string author;
    int id;
    bool available;
    static int nextId;

    public:
    Item(const std::string& title, const std::string& author);
    virtual ~Item();

    virtual void display() const;
    bool isAvailable() const;
    void setAvailable(bool status);
    int getId() const;
    int produceID();
};