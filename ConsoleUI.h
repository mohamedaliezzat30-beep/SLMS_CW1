#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include "Library.h"
#include "UserStore.h"
#include "ActionStore.h"
#include "Admin.h"
#include "Member.h"

class ConsoleUI
{
private:
    Library library;
    UserStore userStore;
    ActionStore actionStore;

    void showMainMenu();
    void memberLogin();
    void createMemberAccount();
    void adminLogin();

    void memberMenu(Member& member);
    void adminMenu(const Admin& admin);

    void viewBooks() const;
    void viewBooksForMember(const Member& member) const;
    void borrowBook(Member& member);
    void returnBook(Member& member);
    void reserveBook(Member& member);
    void viewMemberBorrowedBooks(const Member& member) const;

    void viewOverdueBooks() const;
    void advanceSystemTime();
    void generateSystemReport() const;
    void resetSystemData();

public:
    ConsoleUI();
    void run();
};

#endif
