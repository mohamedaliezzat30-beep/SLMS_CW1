# Smart Library Management System (SLMS)

## Overview

The Smart Library Management System (SLMS) is a console-based application developed in C++ using Object-Oriented Programming (OOP). The system simulates a small digital library where members can browse books, borrow books, return books, and reserve unavailable books. Administrators can monitor the system, detect overdue books, and generate system reports.

The main goal of the system is to demonstrate object-oriented programming concepts while implementing a functional library system.

---

## System Users

| User Type | Description |
|-----------|-------------|
| Member | A library user who can borrow, return, and reserve books |
| Admin | A system administrator who monitors and manages the system |

---

## Member Features

| Feature | Description |
|-------|-------------|
| Create Account | Members can create new accounts |
| Login | Members can login to the system |
| View Catalogue | Members can see all available books |
| Borrow Book | Members can borrow available books |
| Return Book | Members can return books they borrowed |
| Reserve Book | Members can reserve books that are already borrowed |
| View Borrowed Books | Members can see the books they currently borrowed |

---

## Administrator Features

| Feature | Description |
|--------|-------------|
| Admin Login | Access administrator functions |
| View Catalogue | View all books in the library |
| View Overdue Books | Detect books borrowed beyond allowed time |
| Advance System Time | Simulate passing days in the system |
| Generate Report | Generate a summary of system activity |
| Reset System | Restore system to initial state |

---

## Borrowing Rules

| Rule | Description |
|------|-------------|
| Borrow Limit | Maximum 5 books per member |
| Duplicate Borrowing | A member cannot borrow the same book twice |
| Reservation Queue | Reserved books are assigned in order |
| Borrow Tracking | Each book stores the day it was borrowed |

---

## Object-Oriented Programming Concepts

| Concept | Implementation |
|-------|----------------|
| Inheritance | Member and Admin inherit from the User class |
| Encapsulation | Classes manage their own data and behaviour |
| Polymorphism | The getRole() function behaves differently depending on user type |

---

## Project Structure

| Component | Responsibility |
|-----------|---------------|
| ConsoleUI | Handles menus and user interaction |
| Library | Manages book catalogue and borrowing logic |
| Book | Represents book data |
| User | Base class for users |
| Member | Library member class |
| Admin | Administrator class |
| UserStore | Handles user authentication |
| ActionStore | Logs system actions |
| Input | Handles user input validation |

---

## How to Run

1. Open the project in Visual Studio
2. Open the `.vcxproj` project file
3. Build the solution
4. Run using **Local Windows Debugger**

---

## Testing

The system was tested using multiple scenarios including:

- Borrowing available books
- Preventing duplicate borrowing
- Enforcing borrowing limits
- Reserving unavailable books
- Detecting overdue books
