#include "Book.h"
#include <sstream>
#include <vector>
#include <stdexcept>

namespace
{
    std::vector<std::string> split(const std::string& text, char delimiter)
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

    std::string join(const std::vector<std::string>& items, char delimiter)
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

Book::Book()
    : id(0), title(""), author(""), borrowed(false), borrowedBy(""), borrowedDay(-1)
{
}

Book::Book(int id, const std::string& title, const std::string& author)
    : id(id), title(title), author(author), borrowed(false), borrowedBy(""), borrowedDay(-1)
{
}

int Book::getId() const
{
    return id;
}

std::string Book::getTitle() const
{
    return title;
}

std::string Book::getAuthor() const
{
    return author;
}

bool Book::isBorrowed() const
{
    return borrowed;
}

std::string Book::getBorrowedBy() const
{
    return borrowedBy;
}

int Book::getBorrowedDay() const
{
    return borrowedDay;
}

const std::vector<std::string>& Book::getReservationQueue() const
{
    return reservationQueue;
}

void Book::setBorrowed(bool value)
{
    borrowed = value;
}

void Book::setBorrowedBy(const std::string& username)
{
    borrowedBy = username;
}

void Book::setBorrowedDay(int day)
{
    borrowedDay = day;
}

bool Book::isReservedBy(const std::string& username) const
{
    for (const std::string& reservedUser : reservationQueue)
    {
        if (reservedUser == username)
        {
            return true;
        }
    }
    return false;
}

bool Book::hasReservations() const
{
    return !reservationQueue.empty();
}

void Book::addReservation(const std::string& username)
{
    if (!isReservedBy(username))
    {
        reservationQueue.push_back(username);
    }
}

bool Book::removeReservation(const std::string& username)
{
    for (auto it = reservationQueue.begin(); it != reservationQueue.end(); ++it)
    {
        if (*it == username)
        {
            reservationQueue.erase(it);
            return true;
        }
    }
    return false;
}

std::string Book::popNextReservation()
{
    if (reservationQueue.empty())
    {
        return "";
    }

    std::string next = reservationQueue.front();
    reservationQueue.erase(reservationQueue.begin());
    return next;
}

void Book::clearReservations()
{
    reservationQueue.clear();
}

std::string Book::serialize() const
{
    std::ostringstream oss;
    oss << id << "|"
        << title << "|"
        << author << "|"
        << (borrowed ? 1 : 0) << "|"
        << borrowedBy << "|"
        << borrowedDay << "|"
        << join(reservationQueue, ',');
    return oss.str();
}

Book Book::deserialize(const std::string& line)
{
    std::vector<std::string> parts = split(line, '|');

    if (parts.size() < 7)
    {
        throw std::runtime_error("Invalid book record format.");
    }

    Book book;
    book.id = std::stoi(parts[0]);
    book.title = parts[1];
    book.author = parts[2];
    book.borrowed = (parts[3] == "1");
    book.borrowedBy = parts[4];
    book.borrowedDay = std::stoi(parts[5]);

    if (!parts[6].empty())
    {
        book.reservationQueue = split(parts[6], ',');
    }

    return book;
}