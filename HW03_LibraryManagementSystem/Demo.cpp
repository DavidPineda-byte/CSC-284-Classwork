

#include <iostream>
#include "Library.cpp"

int main() {
    Library lib;

    // Add three books by Charles Dickens
    lib.add_book(Book("Great Expectations", "Charles Dickens", 1861, "Classic"));
    lib.add_book(Book("Oliver Twist", "Charles Dickens", 1838, "Classic"));
    lib.add_book(Book("A Tale of Two Cities", "Charles Dickens", 1859, "Historical"));

    std::cout << "All books:\n";
    lib.display_books();

    // Remove a book (uses erase + remove_if internally)
    lib.remove_book("Oliver Twist");

    std::cout << "\nAfter removal:\n";
    lib.display_books();

    // Sort ascending
    lib.sort_by_year_ascending();
    std::cout << "\nSorted ascending by year:\n";
    lib.display_books();

    // Sort descending
    lib.sort_by_year_descending();
    std::cout << "\nSorted descending by year:\n";
    lib.display_books();

    // Demonstrate find_if via find_book
    try {
        Book& found = lib.find_book("Great Expectations");
        std::cout << "\nFound book: " << found.getBookInfo() << "\n";
    } catch (...) {
        std::cout << "Book not found\n";
    }

    return 0;
}