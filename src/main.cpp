#include "Library.h"
#include "Book.h"
#include <iostream>

int main()
{
    Library lib;

    Book *b1 = new Book("The Hobbit", "J.R.R. Tolkien", "978-0547928227", "Fantasy", 310);
    Book *b2 = new Book("1984", "George Orwell", "978-0451524935", "Dystopian", 328);
    Book *b3 = new Book("Dune", "Frank Herbert", "978-0441172719", "Sci-Fi", 412);
    Book *b4 = new Book("Lord of the Flies", "William Golding", "796-2228659003", "Fiction", 270);
    Book *b5 = new Book("Fahrenheit 451", "Ray Bradbury", "966-1231234400", "Dystopian", 202);
    lib.addItem(b1);
    lib.addItem(b2);
    lib.addItem(b3);
    lib.addItem(b4);
    lib.addItem(b5);

    Member *mem1 = lib.registerMember("Scott");
    Member *mem2 = lib.registerMember("Alice");
    
    lib.borrowItem(b1->getId(), mem2->getId());
    lib.borrowItem(b2->getId(), mem1->getId());
    lib.borrowItem(b3->getId(), mem1->getId());
    lib.borrowItem(b4->getId(), mem1->getId());

    lib.printCatalog();

    lib.returnItem(b1->getId());
    lib.returnItem(b1->getId());
    
    lib.returnItem(b5->getId());

    lib.removeItem(b2->getId());

    lib.returnItem(b2->getId());
    lib.removeItem(b2->getId());

    lib.printCatalog();

    return 0;
}