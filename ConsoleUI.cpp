#include "ConsoleUI.h"
#include "Input.h"
#include <iostream>

ConsoleUI::ConsoleUI()
    : library("library_state.txt"), userStore("members.txt"), actionStore("actions.txt")
{
    userStore.load();
    library.load();
}

void ConsoleUI::run()
{
    bool running = true;

    while (running)
    {
        showMainMenu();
        int choice = Input::readInt("Select an option: ", 1, 4);

        switch (choice)
        {
        case 1:
            memberLogin();
            break;
        case 2:
            createMemberAccount();
            break;
        case 3:
            adminLogin();
            break;
        case 4:
            running = false;
            std::cout << "Exiting system. Goodbye.\n";
            break;
        }
    }
}

void ConsoleUI::showMainMenu()
{
    std::cout << "\n========== SMART LIBRARY MANAGEMENT SYSTEM ==========\n";
    std::cout << "1. Member Login\n";
    std::cout << "2. Create Member Account\n";
    std::cout << "3. Admin Login\n";
    std::cout << "4. Exit\n";
    std::cout << "====================================================\n";
}

void ConsoleUI::memberLogin()
{
    std::cout << "\n--- Member Login ---\n";
    std::string username = Input::readLine("Username: ");
    std::string password = Input::readLine("Password: ");

    Member* member = userStore.authenticateMember(username, password);
    if (member == nullptr)
    {
        std::cout << "Invalid member credentials.\n";
        Input::pause();
        return;
    }

    actionStore.logAction("Member logged in: " + member->getUsername());
    memberMenu(*member);
}

void ConsoleUI::createMemberAccount()
{
    std::cout << "\n--- Create Member Account ---\n";
    std::string fullName = Input::readLine("Full Name: ");
    std::string username = Input::readLine("Username: ");
    std::string password = Input::readLine("Password: ");

    if (fullName.empty() || username.empty() || password.empty())
    {
        std::cout << "All fields are required.\n";
        Input::pause();
        return;
    }

    Member member(username, password, fullName);
    if (userStore.addMember(member))
    {
        std::cout << "Account created successfully.\n";
        actionStore.logAction("New member account created: " + username);
    }
    else
    {
        std::cout << "Username already exists.\n";
    }

    Input::pause();
}

void ConsoleUI::adminLogin()
{
    std::cout << "\n--- Admin Login ---\n";
    std::string username = Input::readLine("Username: ");
    std::string password = Input::readLine("Password: ");

    Admin admin = userStore.authenticateAdmin(username, password);
    if (admin.getUsername().empty())
    {
        std::cout << "Invalid admin credentials.\n";
        Input::pause();
        return;
    }

    actionStore.logAction("Admin logged in: " + admin.getUsername());
    adminMenu(admin);
}

void ConsoleUI::memberMenu(Member& member)
{
    bool loggedIn = true;

    while (loggedIn)
    {
        std::cout << "\n========== MEMBER MENU ==========\n";
        std::cout << "Welcome, " << member.getFullName() << "\n";
        std::cout << "1. View Books\n";
        std::cout << "2. Borrow Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Reserve Book\n";
        std::cout << "5. View My Borrowed Books\n";
        std::cout << "6. Logout\n";
        std::cout << "=================================\n";

        int choice = Input::readInt("Select an option: ", 1, 6);

        switch (choice)
        {
        case 1:
            viewBooksForMember(member);
            break;
        case 2:
            borrowBook(member);
            break;
        case 3:
            returnBook(member);
            break;
        case 4:
            reserveBook(member);
            break;
        case 5:
            viewMemberBorrowedBooks(member);
            break;
        case 6:
            loggedIn = false;
            actionStore.logAction("Member logged out: " + member.getUsername());
            std::cout << "Logged out successfully.\n";
            break;
        }
    }
}

void ConsoleUI::adminMenu(const Admin& admin)
{
    bool loggedIn = true;

    while (loggedIn)
    {
        std::cout << "\n========== ADMIN MENU ==========\n";
        std::cout << "Welcome, " << admin.getFullName() << "\n";
        std::cout << "1. View Catalogue\n";
        std::cout << "2. View Overdue Books\n";
        std::cout << "3. Advance System Time\n";
        std::cout << "4. Generate System Report\n";
        std::cout << "5. Reset System Data\n";
        std::cout << "6. Logout\n";
        std::cout << "================================\n";

        int choice = Input::readInt("Select an option: ", 1, 6);

        switch (choice)
        {
        case 1:
            viewBooks();
            break;
        case 2:
            viewOverdueBooks();
            break;
        case 3:
            advanceSystemTime();
            break;
        case 4:
            generateSystemReport();
            break;
        case 5:
            resetSystemData();
            break;
        case 6:
            loggedIn = false;
            actionStore.logAction("Admin logged out: " + admin.getUsername());
            std::cout << "Logged out successfully.\n";
            break;
        }
    }
}

void ConsoleUI::viewBooks() const
{
    std::cout << "\n========== LIBRARY CATALOGUE ==========\n";
    for (const Book& book : library.getBooks())
    {
        std::cout << book.getId() << ". "
            << book.getTitle() << " - " << book.getAuthor();

        if (book.isBorrowed())
        {
            std::cout << " [Borrowed by: " << book.getBorrowedBy() << "]";
        }
        else
        {
            std::cout << " [Available]";
        }

        if (book.hasReservations())
        {
            std::cout << " [Reserved]";
        }

        std::cout << "\n";
    }
    std::cout << "Current System Day: " << library.getCurrentDay() << "\n";
    std::cout << "=======================================\n";
    Input::pause();
}

void ConsoleUI::viewBooksForMember(const Member& member) const
{
    std::cout << "\n========== BOOK CATALOGUE ==========\n";
    for (const Book& book : library.getBooks())
    {
        std::cout << book.getId() << ". "
            << book.getTitle() << " - " << book.getAuthor();

        if (book.isBorrowed())
        {
            if (book.getBorrowedBy() == member.getUsername())
            {
                std::cout << " [Borrowed by you]";
            }
            else
            {
                std::cout << " [Unavailable]";
            }
        }
        else
        {
            std::cout << " [Available]";
        }

        if (book.isReservedBy(member.getUsername()))
        {
            std::cout << " [Reserved by you]";
        }

        std::cout << "\n";
    }
    std::cout << "====================================\n";
    Input::pause();
}

void ConsoleUI::borrowBook(Member& member)
{
    viewBooksForMember(member);
    int bookId = Input::readInt("Enter Book ID to borrow: ", 1, 10);

    std::string message;
    if (library.borrowBook(member, bookId, message))
    {
        library.save();
        userStore.save();

        const Book* book = library.findBookById(bookId);
        if (book != nullptr)
        {
            actionStore.logAction("Borrowed book: " + member.getUsername() + " -> " + book->getTitle());
        }
    }

    std::cout << message << "\n";
    Input::pause();
}

void ConsoleUI::returnBook(Member& member)
{
    viewMemberBorrowedBooks(member);
    int bookId = Input::readInt("Enter Book ID to return: ", 1, 10);

    std::string message;
    if (library.returnBook(member, bookId, message, userStore))
    {
        library.save();
        userStore.save();

        const Book* book = library.findBookById(bookId);
        if (book != nullptr)
        {
            actionStore.logAction("Returned book: " + member.getUsername() + " -> " + book->getTitle());
        }
    }

    std::cout << message << "\n";
    Input::pause();
}

void ConsoleUI::reserveBook(Member& member)
{
    viewBooksForMember(member);
    int bookId = Input::readInt("Enter Book ID to reserve: ", 1, 10);

    std::string message;
    if (library.reserveBook(member, bookId, message))
    {
        library.save();
        const Book* book = library.findBookById(bookId);
        if (book != nullptr)
        {
            actionStore.logAction("Reserved book: " + member.getUsername() + " -> " + book->getTitle());
        }
    }

    std::cout << message << "\n";
    Input::pause();
}

void ConsoleUI::viewMemberBorrowedBooks(const Member& member) const
{
    std::cout << "\n========== MY BORROWED BOOKS ==========\n";

    if (member.getBorrowedBookIds().empty())
    {
        std::cout << "You have not borrowed any books.\n";
    }
    else
    {
        for (int bookId : member.getBorrowedBookIds())
        {
            const Book* book = library.findBookById(bookId);
            if (book != nullptr)
            {
                int daysBorrowed = library.getCurrentDay() - book->getBorrowedDay();
                std::cout << book->getId() << ". "
                    << book->getTitle() << " - " << book->getAuthor()
                    << " [Borrowed for " << daysBorrowed << " day(s)]\n";
            }
        }
    }

    std::cout << "=======================================\n";
    Input::pause();
}

void ConsoleUI::viewOverdueBooks() const
{
    std::vector<Book> overdueBooks = library.getOverdueBooks();

    std::cout << "\n========== OVERDUE BOOKS ==========\n";
    if (overdueBooks.empty())
    {
        std::cout << "No overdue books found.\n";
    }
    else
    {
        for (const Book& book : overdueBooks)
        {
            int daysBorrowed = library.getCurrentDay() - book.getBorrowedDay();
            std::cout << book.getId() << ". "
                << book.getTitle() << " - " << book.getAuthor()
                << " [Borrowed by: " << book.getBorrowedBy() << "]"
                << " [Days borrowed: " << daysBorrowed << "]\n";
        }
    }
    std::cout << "===================================\n";
    Input::pause();
}

void ConsoleUI::advanceSystemTime()
{
    int days = Input::readInt("Enter number of days to advance: ", 1, 365);
    library.advanceSystemTime(days);
    library.save();

    actionStore.logAction("System time advanced by " + std::to_string(days) + " day(s)");
    std::cout << "System time advanced successfully. Current day: " << library.getCurrentDay() << "\n";
    Input::pause();
}

void ConsoleUI::generateSystemReport() const
{
    std::cout << "\n" << library.generateSystemReport(userStore);
    Input::pause();
}

void ConsoleUI::resetSystemData()
{
    std::string confirm = Input::readLine("Are you sure you want to reset all data? Type YES to confirm: ");

    if (confirm == "YES")
    {
        library.reset(userStore);
        actionStore.clear();
        actionStore.logAction("System data reset by admin");
        std::cout << "System data has been reset.\n";
    }
    else
    {
        std::cout << "Reset cancelled.\n";
    }

    Input::pause();
}