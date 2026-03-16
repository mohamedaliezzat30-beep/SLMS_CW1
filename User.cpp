#include "User.h"

User::User() : username(""), password(""), fullName("")
{
}

User::User(const std::string& username, const std::string& password, const std::string& fullName)
    : username(username), password(password), fullName(fullName)
{
}

User::~User()
{
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPassword() const
{
    return password;
}

std::string User::getFullName() const
{
    return fullName;
}
