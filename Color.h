#include <string>

class Color {
public:
    static const std::string BBLACK;
    static const std::string BRED;
    static const std::string BGREEN;
    static const std::string BYELLOW;
    static const std::string BBLUE;
    static const std::string BMAGENTA;
    static const std::string BCYAN;
    static const std::string BWHITE;

    static const std::string RESET;

private:
    Color() {}
};

const std::string Color::BBLACK = "\033[90m";
const std::string Color::BRED = "\033[91m";
const std::string Color::BGREEN = "\033[92m";
const std::string Color::BYELLOW = "\033[93m";
const std::string Color::BBLUE = "\033[94m";
const std::string Color::BMAGENTA = "\033[95m";
const std::string Color::BCYAN = "\033[96m";
const std::string Color::BWHITE = "\033[97m";

const std::string Color::RESET = "\033[0m";
