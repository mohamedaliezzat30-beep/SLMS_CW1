#include "ActionStore.h"
#include <fstream>

ActionStore::ActionStore(const std::string& actionsFile)
    : actionsFile(actionsFile)
{
}

void ActionStore::logAction(const std::string& action) const
{
    std::ofstream file(actionsFile, std::ios::app);
    if (file.is_open())
    {
        file << action << "\n";
        file.close();
    }
}

std::vector<std::string> ActionStore::getAllActions() const
{
    std::vector<std::string> actions;
    std::ifstream file(actionsFile);

    if (!file.is_open())
    {
        return actions;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            actions.push_back(line);
        }
    }

    file.close();
    return actions;
}

void ActionStore::clear() const
{
    std::ofstream file(actionsFile, std::ios::trunc);
    file.close();
}
