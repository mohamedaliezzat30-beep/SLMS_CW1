# Pseudocode

Borrow Book Algorithm  

IF member borrowed books < 5  
    FIND book by ID  
    IF book exists AND available  
        mark book borrowed  
        record borrow day  
        add book to member borrowed list  
    ELSE  
        display error message  
ELSE  
    display borrow limit reached  


Return Book Algorithm  

FIND book by ID  
IF book belongs to member  
    mark book available  
    remove book from borrowed list  


IF reservation exists  
        assign book to next user
    
Reserve Book Algorithm  

FIND book by ID  
IF book is borrowed  
    add member to reservation queue  
ELSE  
    notify book is available  
