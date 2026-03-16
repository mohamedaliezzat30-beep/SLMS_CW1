#ifndef USER_H
#define USER_H

#include <string>

class User
{
protected:
    std::string username;
    std::string password;
    std::string fullName;

public:
    User();
    User(const std::string& username, const std::string& password, const std::string& fullName);
    virtual ~User();

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;

    virtual std::string getRole() const = 0;
};

#endif
