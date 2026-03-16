#include "UserStore.h"
#include <fstream>

UserStore::UserStore(const std::string& membersFile)
    : membersFile(membersFile)
{
}

void UserStore::load()
{
    members.clear();

    std::ifstream file(membersFile);
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            members.push_back(Member::deserialize(line));
        }
    }

    file.close();
}

void UserStore::save() const
{
    std::ofstream file(membersFile, std::ios::trunc);
    for (const Member& member : members)
    {
        file << member.serialize() << "\n";
    }
    file.close();
}

bool UserStore::usernameExists(const std::string& username) const
{
    for (const Member& member : members)
    {
        if (member.getUsername() == username)
        {
            return true;
        }
    }

    if (username == "admin")
    {
        return true;
    }

    return false;
}

bool UserStore::addMember(const Member& member)
{
    if (usernameExists(member.getUsername()))
    {
        return false;
    }

    members.push_back(member);
    save();
    return true;
}

Member* UserStore::authenticateMember(const std::string& username, const std::string& password)
{
    for (Member& member : members)
    {
        if (member.getUsername() == username && member.getPassword() == password)
        {
            return &member;
        }
    }
    return nullptr;
}

Admin UserStore::authenticateAdmin(const std::string& username, const std::string& password) const
{
    if (username == "admin" && password == "admin123")
    {
        return Admin("admin", "admin123", "System Administrator");
    }

    return Admin("", "", "");
}

std::vector<Member>& UserStore::getMembers()
{
    return members;
}

const std::vector<Member>& UserStore::getMembers() const
{
    return members;
}

Member* UserStore::findMemberByUsername(const std::string& username)
{
    for (Member& member : members)
    {
        if (member.getUsername() == username)
        {
            return &member;
        }
    }
    return nullptr;
}

void UserStore::clearAllMembers()
{
    members.clear();
    save();
}