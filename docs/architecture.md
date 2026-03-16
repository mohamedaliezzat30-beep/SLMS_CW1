# System Architecture

The Smart Library Management System uses a modular object-oriented architecture. The system separates user interaction, system logic, and data storage into different classes.

---

## Architecture Components

| Component | Responsibility |
|----------|---------------|
| ConsoleUI | Displays menus and handles user input |
| Library | Implements borrowing, returning, reserving books |
| UserStore | Manages member accounts and authentication |
| Book | Represents book objects |
| Member | Represents library members |
| Admin | Represents administrators |

---

## System Workflow

1. The program starts in main.cpp
2. ConsoleUI displays the main menu
3. Users select actions through the interface
4. ConsoleUI calls Library and UserStore functions
5. Library processes book operations

---

## Architecture Diagram (Conceptual)

User → ConsoleUI → Library → Book Data

ConsoleUI communicates with:
- Library
- UserStore
- ActionStore

This layered architecture separates responsibilities and improves maintainability.
