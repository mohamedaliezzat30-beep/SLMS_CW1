# Class Design

The system is implemented using several classes representing system entities.

---

## User Class

| Attribute | Description |
|----------|-------------|
| username | Unique identifier for user |
| password | Login password |
| fullName | Name of user |

Methods

- getUsername()
- getPassword()
- getFullName()
- getRole()

---

## Member Class

Derived from User.

| Attribute | Description |
|----------|-------------|
| borrowedBookIds | List of borrowed books |

Methods

- borrowBook()
- returnBook()
- hasBorrowedBook()

---

## Admin Class

Derived from User.

| Method | Description |
|-------|-------------|
| getRole() | Returns admin role |

---

## Book Class

| Attribute | Description |
|----------|-------------|
| id | Book identifier |
| title | Book title |
| author | Author name |
| borrowedBy | Username of borrower |
| borrowedDay | Day book was borrowed |

---

## Library Class

Responsible for system rules.

| Method | Description |
|-------|-------------|
| borrowBook() | Allows member to borrow book |
| returnBook() | Handles returning book |
| reserveBook() | Adds reservation |
| getOverdueBooks() | Detects overdue books |
| generateSystemReport() | Creates system report |
