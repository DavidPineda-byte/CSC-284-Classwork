#include <string>
class Book{

private: 
std::string title; 
std::string author;
int publicationYear;
std::string genre;
int not_needed;
public:
Book(std::string t, std::string a, int pY, std::string g) : title(t), author(a), publicationYear(pY), genre(g) {}
std::string getBookInfo(){
    return title + " by " + author + " (" + std::to_string(publicationYear) + ") [" + genre + "]";
}
std::string getTitle() const { 
            return title; 
        }
std::string getAuthor() const { 
            return author; 
        }
std::string getGenre() const{
    return genre; 
}
int getYear() const{
    return publicationYear; 
}
};