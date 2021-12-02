#include <iostream>
#include <cstdlib>
#include "NumbersUtil.h"

int main()
{
    NumberArray numData;
    initData(numData);
    Number input;
    std::cout << "Enter a number between 0 and 999,999 as a value or in words: ";
    std::getline(std::cin, input.word);
    if(convToVal(input.word, input.value))
    {
        std::cout << input.value << " is " << genWord(input.value) << std::endl;
    }
    else
    {
        std::cout << input.word << " is " << genValue(input.word) << std::endl;
    }
    system("pause");
    return 0;
}