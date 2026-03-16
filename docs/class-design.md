# Class Design

Main classes in the system:

User
- username
- password
- fullName
- getRole()

Member (inherits User)
- borrowedBookIds
- borrowBook()
- returnBook()

Admin (inherits User)
- administrative functions

Library
- borrowBook()
- returnBook()
- reserveBook()
- getOverdueBooks()

Book
- id
- title
- author
- borrowedBy
