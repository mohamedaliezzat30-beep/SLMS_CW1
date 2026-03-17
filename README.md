# Smart Library Management System (SLMS)

## Overview

The Smart Library Management System (SLMS) is a console-based application developed in **C++ using Object-Oriented Programming (OOP)** principles.

The system simulates a real library environment where users can borrow, return, and reserve books, while administrators can monitor and manage system operations.

---

## Key Features

### Member Features

| Feature | Description |
|--------|-------------|
| Create Account | Register a new member |
| Login | Access system features |
| View Books | Browse library catalogue |
| Borrow Book | Borrow available books |
| Return Book | Return borrowed books |
| Reserve Book | Reserve unavailable books |
| View Borrowed Books | Track borrowed items |

---

### Administrator Features

| Feature | Description |
|--------|-------------|
| Admin Login | Access admin panel |
| View Catalogue | Monitor all books |
| Advance Time | Simulate system days |
| Overdue Detection | Identify late returns |
| System Report | Generate summary |
| Reset System | Restore initial state |

---

## System Rules

| Rule | Description |
|-----|-------------|
| Borrow Limit | Max 5 books per member |
| No Duplicate Borrowing | Same book cannot be borrowed twice |
| Reservation Queue | FIFO reservation system |
| Borrow Tracking | Tracks borrow date |

---

## OOP Concepts Used

| Concept | Implementation |
|--------|---------------|
| Encapsulation | Each class manages its own data |
| Inheritance | `Member` and `Admin` inherit from `User` |
| Polymorphism | `getRole()` behaves differently |

---

## Important Files & Quick Access

| File | Description |
|------|------------|
| [ Architecture](./docs/architecture.md) | System structure |
| [ Class Design](./docs/class-design.md) | Class explanations |
| [ Requirements](./docs/requirements.md) | System requirements |
| [ Testing](./docs/testing.md) | Test cases |
| [ Traceability](./docs/traceability.md) | Requirement mapping |
| [ Pseudocode](./docs/pseudocode.md) | Algorithms |
| [ Screenshots](./docs/screenshots.md) | System evidence |

---

## Quick Navigation (Magic Links)

- [ View Screenshots](./docs/screenshots.md)
- [ Architecture](./docs/architecture.md)
- [ Class Design](./docs/class-design.md)
- [ Testing](./docs/testing.md)
- [ Requirements](./docs/requirements.md)

---

## System Preview

| Feature | Preview |
|--------|--------|
| Main Menu | ![](./docs/main-menu.png) |
| Member Menu | ![](./docs/member-menu.png) |
| Borrow Book | ![](./docs/borrow-book.png) |

---

## How to Run

1. Open project in **Visual Studio**
2. Open `SLMS_CPP4.vcxproj`
3. Build the solution
4. Run using **Local Windows Debugger**

---

## Testing Summary

The system has been tested for:

- Borrowing and returning books  
- Duplicate borrow prevention  
- Borrow limit enforcement  
- Reservation system  
- Overdue detection  
- Admin system controls  

---

## Evidence

Full system screenshots are available here:

**[View All Screenshots](./docs/screenshots.md)**

---

## Project Structure
