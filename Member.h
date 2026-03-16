#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <vector>
#include <string>

class Member : public User
{
private:
    std::vector<int> borrowedBookIds;

public:
    Member();
    Member(const std::string& username, const std::string& password, const std::string& fullName);

    std::string getRole() const override;

    const std::vector<int>& getBorrowedBookIds() const;
    bool hasBorrowedBook(int bookId) const;
    void borrowBook(int bookId);
    void returnBook(int bookId);
    void clearBorrowedBooks();

    std::string serialize() const;
    static Member deserialize(const std::string& line);
};

#endif
