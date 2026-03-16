#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Member.h"
#include "UserStore.h"
#include <vector>
#include <string>

class Library
{
private:
    std::vector<Book> books;
    int currentDay;
    std::string libraryFile;
    static const int MAX_BORROW_LIMIT = 5;
    static const int LOAN_PERIOD_DAYS = 14;

    void loadDefaultBooks();

public:
    Library(const std::string& libraryFile = "library_state.txt");

    void load();
    void save() const;
    void reset(UserStore& userStore);

    std::vector<Book>& getBooks();
    const std::vector<Book>& getBooks() const;

    Book* findBookById(int id);
    const Book* findBookById(int id) const;

    int getCurrentDay() const;
    void advanceSystemTime(int days);

    bool borrowBook(Member& member, int bookId, std::string& message);
    bool returnBook(Member& member, int bookId, std::string& message, UserStore& userStore);
    bool reserveBook(Member& member, int bookId, std::string& message);

    std::vector<Book> getOverdueBooks() const;
    std::string generateSystemReport(const UserStore& userStore) const;
};

#endif
