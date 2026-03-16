#include "Input.h"
#include <iostream>
#include <limits>

int Input::readInt(const std::string& prompt, int minValue, int maxValue)
{
    int value;

    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < minValue || value > maxValue)
        {
            std::cout << "Please enter a number between " << minValue << " and " << maxValue << ".\n";
            continue;
        }

        return value;
    }
}

std::string Input::readLine(const std::string& prompt)
{
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void Input::pause()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}
