#include <Book.h>
#include <iostream>

Book::Book(const std::string &title, const std::string &author, const std::string &ISBN, const std::string &genre, int pageCount)
    : Item(title, author),
      ISBN(ISBN), 
      genre(genre), 
      pageCount(pageCount) 
      {}

Book::~Book() {}

void Book::display() const
{   
    if (available)
    {
        std::cout << "[AVAILABLE] " << title << " by " << author << ".\nGenre: " << genre << ", ISBN: " << ISBN << ". Number of pages " << pageCount << " (ID: "
                  << id << ")\n";
    }else{
        std::cout << "[BORROWED] " << title << " by " << author << ".\nGenre: " << genre << ", ISBN: " << ISBN << ". Number of pages " << pageCount << " (ID: "
                  << id << ")\n";
    }
    
    
}
