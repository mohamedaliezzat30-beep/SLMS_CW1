#include "Member.h"
#include <sstream>
#include <vector>
#include <algorithm>

namespace
{
    std::vector<std::string> splitMember(const std::string& text, char delimiter)
    {
        std::vector<std::string> parts;
        std::stringstream ss(text);
        std::string item;

        while (std::getline(ss, item, delimiter))
        {
            parts.push_back(item);
        }

        return parts;
    }

    std::string joinInts(const std::vector<int>& items, char delimiter)
    {
        std::ostringstream oss;

        for (size_t i = 0; i < items.size(); ++i)
        {
            oss << items[i];
            if (i + 1 < items.size())
            {
                oss << delimiter;
            }
        }

        return oss.str();
    }
}

Member::Member()
    : User()
{
}

Member::Member(const std::string& username, const std::string& password, const std::string& fullName)
    : User(username, password, fullName)
{
}

std::string Member::getRole() const
{
    return "Member";
}

const std::vector<int>& Member::getBorrowedBookIds() const
{
    return borrowedBookIds;
}

bool Member::hasBorrowedBook(int bookId) const
{
    for (int id : borrowedBookIds)
    {
        if (id == bookId)
        {
            return true;
        }
    }
    return false;
}

void Member::borrowBook(int bookId)
{
    if (!hasBorrowedBook(bookId))
    {
        borrowedBookIds.push_back(bookId);
    }
}

void Member::returnBook(int bookId)
{
    borrowedBookIds.erase(
        std::remove(borrowedBookIds.begin(), borrowedBookIds.end(), bookId),
        borrowedBookIds.end()
    );
}

void Member::clearBorrowedBooks()
{
    borrowedBookIds.clear();
}

std::string Member::serialize() const
{
    std::ostringstream oss;
    oss << username << "|"
        << password << "|"
        << fullName << "|"
        << joinInts(borrowedBookIds, ',');
    return oss.str();
}

Member Member::deserialize(const std::string& line)
{
    std::vector<std::string> parts = splitMember(line, '|');
    Member member;

    if (parts.size() >= 4)
    {
        member.username = parts[0];
        member.password = parts[1];
        member.fullName = parts[2];

        if (!parts[3].empty())
        {
            std::vector<std::string> ids = splitMember(parts[3], ',');
            for (const std::string& idText : ids)
            {
                member.borrowedBookIds.push_back(std::stoi(idText));
            }
        }
    }

    return member;
}
