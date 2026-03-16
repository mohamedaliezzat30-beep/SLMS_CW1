#ifndef ACTIONSTORE_H
#define ACTIONSTORE_H

#include <string>
#include <vector>

class ActionStore
{
private:
    std::string actionsFile;

public:
    ActionStore(const std::string& actionsFile = "actions.txt");

    void logAction(const std::string& action) const;
    std::vector<std::string> getAllActions() const;
    void clear() const;
};

#endif
