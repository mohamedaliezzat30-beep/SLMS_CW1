#include "Admin.h"

Admin::Admin()
    : User()
{
}

Admin::Admin(const std::string& username, const std::string& password, const std::string& fullName)
    : User(username, password, fullName)
{
}

std::string Admin::getRole() const
{
    return "Admin";
}
