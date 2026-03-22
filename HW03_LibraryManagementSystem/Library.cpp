#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include<ranges>
#include<iostream>
#include "Book.cpp"
class Library { 
    private: 
    std::vector<Book> books; 
    public:
    void add_book(const Book& book){
        books.push_back(book); 
    }
    void remove_book(const std::string& title) {
    books.erase(
        std::remove_if(books.begin(), books.end(),
            [&](const Book& b) {
                return b.getTitle() == title;
            }),
        books.end()
    ); 
}
    Book& find_book(const std::string& title) { 
        auto it = std::find_if(books.begin(), books.end(),
            [&](const Book& b) {
                return b.getTitle() == title;
            });
        if (it != books.end()) {
            return *it; 
        } else {
            throw std::runtime_error("Book not found");
        }
    }

    std::vector<Book> get_books_by_author(const std::string& author){
        std::vector<Book> result;

        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getAuthor() == author) {
                result.push_back(*it);
            }
        }
        return result;
    }
    std::vector<Book> get_books_by_genre(const std::string& genre){
        std::vector<Book> result; 

        for(auto it = books.begin(); it!= books.end(); ++it){
            if(it->getGenre() == genre){
                result.push_back(*it);
            }
        }
        return result;
    }

    std::vector<Book> get_books_after_year(int year) {
    std::vector<Book> result;

    auto view = books | std::ranges::views::filter([&](const Book& b) {
        return b.getYear() > year;
    });

    for (const auto& b : view) {
        result.push_back(b);
    }

    return result;
}

    void sort_by_year_ascending() {
        std::ranges::sort(books, [](const Book& a, const Book& b) {
            return a.getYear() < b.getYear();
        });
    }

    void sort_by_year_descending() {
        std::ranges::sort(books, [](const Book& a, const Book& b) {
            return a.getYear() > b.getYear();
        });
    }

    void display_books() {
        for (std::vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
            std::cout << it->getBookInfo() << "\n";
        }
    }
};