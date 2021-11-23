#include <iostream>
#include <cstdlib>
#include <string>
#define NUMBERS 10

class Number
{
private:
    uint64_t value;
    std::string word;
public:
    Number(const uint64_t& value, const std::string& word = "Undefined")
        : value(value), word(word) {}
    uint64_t getValue() const { return value; }
    std::string getWord() const { return word; }
};

std::ostream& operator<<(std::ostream& out, const Number& number)
{
    out << number.getValue() << ", " << number.getWord();
    return out;
}

Number data[NUMBERS] = {
    {0, "zero"}, {1, "one"}, {2, "two"},
    {3, "three"}, {4, "four"}, {5, "five"},
    {6, "six"}, {7, "seven"}, {8, "eight"},
    {9, "nine"}
};

int main()
{
    for (int i = 0; i < NUMBERS; i++)
    {
        std::cout << data[i] << std::endl;
    }
    system("pause");
    return 0;
}
