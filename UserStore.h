#ifndef USERSTORE_H
#define USERSTORE_H

#include "Member.h"
#include "Admin.h"
#include <vector>
#include <string>

class UserStore
{
private:
    std::vector<Member> members;
    std::string membersFile;

public:
    UserStore(const std::string& membersFile = "members.txt");

    void load();
    void save() const;

    bool usernameExists(const std::string& username) const;
    bool addMember(const Member& member);

    Member* authenticateMember(const std::string& username, const std::string& password);
    Admin authenticateAdmin(const std::string& username, const std::string& password) const;

    std::vector<Member>& getMembers();
    const std::vector<Member>& getMembers() const;

    Member* findMemberByUsername(const std::string& username);

    void clearAllMembers();
};

#endif
