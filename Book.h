#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book
{
private:
    int id;
    std::string title;
    std::string author;
    bool borrowed;
    std::string borrowedBy;
    int borrowedDay;
    std::vector<std::string> reservationQueue;

public:
    Book();
    Book(int id, const std::string& title, const std::string& author);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    bool isBorrowed() const;
    std::string getBorrowedBy() const;
    int getBorrowedDay() const;
    const std::vector<std::string>& getReservationQueue() const;

    void setBorrowed(bool value);
    void setBorrowedBy(const std::string& username);
    void setBorrowedDay(int day);

    bool isReservedBy(const std::string& username) const;
    bool hasReservations() const;
    void addReservation(const std::string& username);
    bool removeReservation(const std::string& username);
    std::string popNextReservation();
    void clearReservations();

    std::string serialize() const;
    static Book deserialize(const std::string& line);
};

#endif
