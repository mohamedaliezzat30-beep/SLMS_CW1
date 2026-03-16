#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

class Admin : public User
{
public:
    Admin();
    Admin(const std::string& username, const std::string& password, const std::string& fullName);

    std::string getRole() const override;
};

#endif
