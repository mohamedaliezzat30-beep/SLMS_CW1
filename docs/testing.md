# Testing

## Test Case Table

| Test Case | Action | Expected Result |
|----------|-------|----------------|
| Borrow Book | Member borrows available book | Book becomes unavailable |
| Duplicate Borrow | Member borrows same book again | System prevents borrowing |
| Borrow Limit | Member borrows 6th book | System blocks borrowing |
| Reserve Book | Member reserves borrowed book | Reservation added |
| Return Book | Member returns book | Book becomes available |
| Overdue Detection | Admin advances time | Overdue books detected |
