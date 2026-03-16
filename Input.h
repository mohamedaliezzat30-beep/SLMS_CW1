#ifndef INPUT_H
#define INPUT_H

#include <string>

class Input
{
public:
    static int readInt(const std::string& prompt, int minValue, int maxValue);
    static std::string readLine(const std::string& prompt);
    static void pause();
};

#endif
