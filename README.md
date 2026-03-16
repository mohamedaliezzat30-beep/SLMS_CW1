# Smart Library Management System (SLMS)

## Overview

The Smart Library Management System (SLMS) is a console-based application developed in C++ using Object-Oriented Programming principles. The system simulates a small digital library where members can manage books and borrowing activities while administrators can monitor the system.

The system allows members to browse books, borrow books, return borrowed books, and reserve books that are currently unavailable. Administrators have additional privileges such as monitoring the library catalogue, detecting overdue books, generating reports, advancing the system time, and resetting the system data.

This project demonstrates the use of Object-Oriented Programming concepts including inheritance, encapsulation, and polymorphism.

---

## Features

### Member Features
Members can:
- Create a new account
- Login to the system
- View the library book catalogue
- Borrow available books
- Return borrowed books
- Reserve books that are currently borrowed by another member
- View their borrowed books

### Borrowing Rules
The system enforces the following rules:
- Members can borrow a maximum of five books
- Members cannot borrow the same book twice
- Borrowed books track the day they were borrowed
- Reserved books are assigned to the next user when returned

### Administrator Features
Administrators can:
- Login as admin
- View the full library catalogue
- Detect overdue books
- Advance the system time
- Generate system reports
- Reset system data

---

## Object-Oriented Programming Concepts

### Inheritance
The system implements inheritance using a base class called User. Both Member and Admin inherit from this class and reuse common attributes such as username, password, and full name.

### Encapsulation
Encapsulation is implemented by ensuring that classes manage their own internal data and logic. For example, the Library class manages book borrowing rules internally rather than allowing other classes to directly modify book status.

### Polymorphism
Polymorphism is demonstrated through virtual functions such as getRole(), where different user types return different role names while sharing the same base class interface.

---

## Project Structure

The system consists of multiple classes responsible for different parts of the application:

- ConsoleUI – handles user interaction and menus
- Library – contains the main logic for borrowing, returning, and reserving books
- Book – represents individual books in the library catalogue
- User – base class for all users
- Member – derived class representing library members
- Admin – derived class representing administrators
- UserStore – manages user authentication and storage
- ActionStore – records system actions
- Input – handles user input validation

---

## How to Run

1. Open the project in Visual Studio.
2. Open the .vcxproj project file.
3. Build the solution.
4. Run the program using Local Windows Debugger or Ctrl + F5.
5. Follow the menu instructions displayed in the console.

---

## Testing

The system has been tested using multiple scenarios including:

- Borrowing available books
- Preventing duplicate borrowing
- Enforcing the borrowing limit
- Reserving unavailable books
- Detecting overdue books
- Admin system monitoring

Detailed testing scenarios are provided in the documentation folder.

---

## Author

Coursework project developed for an Object-Oriented Programming module.
