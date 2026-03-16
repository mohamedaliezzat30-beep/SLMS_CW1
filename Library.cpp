#include "Library.h"
#include <fstream>
#include <sstream>
#include <iostream>

Library::Library(const std::string& libraryFile)
    : currentDay(0), libraryFile(libraryFile)
{
}

void Library::loadDefaultBooks()
{
    books.clear();

    books.push_back(Book(1, "The Great Gatsby", "F. Scott Fitzgerald"));
    books.push_back(Book(2, "1984", "George Orwell"));
    books.push_back(Book(3, "To Kill a Mockingbird", "Harper Lee"));
    books.push_back(Book(4, "Pride and Prejudice", "Jane Austen"));
    books.push_back(Book(5, "The Hobbit", "J.R.R. Tolkien"));
    books.push_back(Book(6, "The Catcher in the Rye", "J.D. Salinger"));
    books.push_back(Book(7, "Moby Dick", "Herman Melville"));
    books.push_back(Book(8, "War and Peace", "Leo Tolstoy"));
    books.push_back(Book(9, "Crime and Punishment", "Fyodor Dostoevsky"));
    books.push_back(Book(10, "The Lord of the Rings", "J.R.R. Tolkien"));
}

void Library::load()
{
    books.clear();
    currentDay = 0;

    std::ifstream file(libraryFile);

    if (!file.is_open())
    {
        loadDefaultBooks();
        save();
        return;
    }

    std::string line;

    if (std::getline(file, line))
    {
        try
        {
            currentDay = std::stoi(line);
        }
        catch (...)
        {
            currentDay = 0;
        }
    }

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        try
        {
            Book book = Book::deserialize(line);

            if (book.getId() > 0 &&
                !book.getTitle().empty() &&
                !book.getAuthor().empty())
            {
                books.push_back(book);
            }
        }
        catch (...)
        {
            // ignore invalid/corrupted line
        }
    }

    file.close();

    if (books.size() != 10)
    {
        loadDefaultBooks();
        save();
    }
}

void Library::save() const
{
    std::ofstream file(libraryFile, std::ios::trunc);
    file << currentDay << "\n";

    for (const Book& book : books)
    {
        file << book.serialize() << "\n";
    }

    file.close();
}

void Library::reset(UserStore& userStore)
{
    currentDay = 0;
    loadDefaultBooks();
    save();

    for (Member& member : userStore.getMembers())
    {
        member.clearBorrowedBooks();
    }

    userStore.clearAllMembers();
}

std::vector<Book>& Library::getBooks()
{
    return books;
}

const std::vector<Book>& Library::getBooks() const
{
    return books;
}

Book* Library::findBookById(int id)
{
    for (Book& book : books)
    {
        if (book.getId() == id)
        {
            return &book;
        }
    }
    return nullptr;
}

const Book* Library::findBookById(int id) const
{
    for (const Book& book : books)
    {
        if (book.getId() == id)
        {
            return &book;
        }
    }
    return nullptr;
}

int Library::getCurrentDay() const
{
    return currentDay;
}

void Library::advanceSystemTime(int days)
{
    if (days > 0)
    {
        currentDay += days;
    }
}

bool Library::borrowBook(Member& member, int bookId, std::string& message)
{
    Book* book = findBookById(bookId);

    if (book == nullptr)
    {
        message = "Book not found.";
        return false;
    }

    if (member.getBorrowedBookIds().size() >= MAX_BORROW_LIMIT)
    {
        message = "You cannot borrow more than 5 books.";
        return false;
    }

    if (member.hasBorrowedBook(bookId))
    {
        message = "You have already borrowed this book.";
        return false;
    }

    if (book->isBorrowed())
    {
        message = "Book is currently unavailable.";
        return false;
    }

    if (book->hasReservations())
    {
        const std::vector<std::string>& queue = book->getReservationQueue();

        if (!queue.empty() && queue.front() != member.getUsername())
        {
            message = "This book is reserved for another member.";
            return false;
        }
        else if (!queue.empty() && queue.front() == member.getUsername())
        {
            book->popNextReservation();
        }
    }

    book->setBorrowed(true);
    book->setBorrowedBy(member.getUsername());
    book->setBorrowedDay(currentDay);
    member.borrowBook(bookId);

    message = "Book borrowed successfully.";
    return true;
}

bool Library::returnBook(Member& member, int bookId, std::string& message, UserStore& userStore)
{
    Book* book = findBookById(bookId);

    if (book == nullptr)
    {
        message = "Book not found.";
        return false;
    }

    if (!member.hasBorrowedBook(bookId))
    {
        message = "You have not borrowed this book.";
        return false;
    }

    book->setBorrowed(false);
    book->setBorrowedBy("");
    book->setBorrowedDay(-1);
    member.returnBook(bookId);

    if (book->hasReservations())
    {
        const std::vector<std::string>& queue = book->getReservationQueue();

        if (!queue.empty())
        {
            Member* nextMember = userStore.findMemberByUsername(queue.front());

            if (nextMember != nullptr)
            {
                message = "Book returned successfully. It is now reserved for: " + queue.front();
            }
            else
            {
                book->popNextReservation();
                message = "Book returned successfully.";
            }
        }
        else
        {
            message = "Book returned successfully.";
        }
    }
    else
    {
        message = "Book returned successfully.";
    }

    return true;
}

bool Library::reserveBook(Member& member, int bookId, std::string& message)
{
    Book* book = findBookById(bookId);

    if (book == nullptr)
    {
        message = "Book not found.";
        return false;
    }

    if (!book->isBorrowed())
    {
        message = "This book is available. You can borrow it instead of reserving it.";
        return false;
    }

    if (book->getBorrowedBy() == member.getUsername())
    {
        message = "You already borrowed this book.";
        return false;
    }

    if (book->isReservedBy(member.getUsername()))
    {
        message = "You have already reserved this book.";
        return false;
    }

    book->addReservation(member.getUsername());
    message = "Book reserved successfully.";
    return true;
}

std::vector<Book> Library::getOverdueBooks() const
{
    std::vector<Book> overdueBooks;

    for (const Book& book : books)
    {
        if (book.isBorrowed())
        {
            int daysBorrowed = currentDay - book.getBorrowedDay();

            if (daysBorrowed > LOAN_PERIOD_DAYS)
            {
                overdueBooks.push_back(book);
            }
        }
    }

    return overdueBooks;
}

std::string Library::generateSystemReport(const UserStore& userStore) const
{
    int borrowedCount = 0;
    int availableCount = 0;
    int reservedCount = 0;

    for (const Book& book : books)
    {
        if (book.isBorrowed())
        {
            borrowedCount++;
        }
        else
        {
            availableCount++;
        }

        if (book.hasReservations())
        {
            reservedCount++;
        }
    }

    std::vector<Book> overdue = getOverdueBooks();

    std::ostringstream report;
    report << "========== SYSTEM REPORT ==========\n";
    report << "Current System Day: " << currentDay << "\n";
    report << "Total Members: " << userStore.getMembers().size() << "\n";
    report << "Total Books: " << books.size() << "\n";
    report << "Available Books: " << availableCount << "\n";
    report << "Borrowed Books: " << borrowedCount << "\n";
    report << "Books With Reservations: " << reservedCount << "\n";
    report << "Overdue Books: " << overdue.size() << "\n";
    report << "===================================\n";

    return report.str();
}