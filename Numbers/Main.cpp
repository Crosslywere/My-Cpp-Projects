#include <iostream>
#include <cstdlib>
#include <string>
#define NUMBERS 11

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
    {9, "nine"}, {10, "ten"}
};

bool isNum(std::string str)
{
    for(char n : str)
    {
        if((n < '0' || n > '9') && n != ',')
            return false;
    }
    return true;
}

uint64_t toNum(std::string str)
{
    uint64_t result = 0;
    for(char n : str)
    {
        if(n == ',')
            continue;
        result *= 10;
        result += n - '0';
    }
    return result;
}

uint64_t getValue(std::string word)
{
    for(int i = 0; i < NUMBERS; i++)
    {
        if(data[i].getWord() == word)
            return data[i].getValue();
    }
    return Number(0).getValue();
}

std::string getWord(std::string value)
{
    uint64_t val = toNum(value);
    for(int i = 0; i < NUMBERS; i++)
    {
        if(data[i].getValue() == val)
            return data[i].getWord();
    }
    return Number(0).getWord();
}

int main()
{
    std::string input;
    std::cout << "Enter a number as word or as a value: ";
    std::getline(std::cin, input);
    if (!isNum(input))
    {
        std::cout << input << " is " << getValue(input.) << std::endl;
    }
    else
    {
        std::cout << input << " is " << getWord(input) << std::endl;
    }
    system("pause");
    return 0;
}
