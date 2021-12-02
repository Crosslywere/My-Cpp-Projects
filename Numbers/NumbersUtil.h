/**
 * This file contains the functions needed to get numbers as words or as integers
 * using loosely defined values.
 * These values are all values that are uniquely spelled in a single word. These are
 * 0 to 20 then it goes in tens to 100 and finally defines 1000.
 * These are all defined in the NumberData.txt text file.
 * Any extra data that you want to define can be added by using the loadExtraData fuction
 * after using the initData function.
 * 
 * Key Words:
 * Segment: this is a none repeatable part of a number eg thousand, million, etc
 * 
 * 
 */
#pragma once
#ifndef NUMBERS_UTIL_H
#define NUMBERS_UTIL_H

/* Includes */

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cmath>


/* Defines and Constants */

#define DATAFILE "NumberData.txt"
#define STREAM_SIZE 30
#define INIT_DATA_SIZE 30


/* Declearations */

// Struct for Number data
struct Number;
// For loading the inital definitions of numbers form a predetermined file
// (called before any other function)
void initData(std::vector<Number>&);  
// Loads extra Number data into a vector from a text file
void loadExtraData(std::string&&, std::vector<Number>&);
// Extracting struct Number from a single line string
Number extractData(std::string);
// Returns true if an unsigned long long can be extracted
bool convToVal(std::string, uint64_t&);
// Function for getting the value representation of a string of words from a data set
uint64_t genValue(std::string, const std::vector<Number>&);
// Function for getting the word represtentation of an integer from a data set
std::string genWord(uint64_t, const std::vector<Number>&);

std::vector<Number>* numberData;


/* Typedefs and Usings */

typedef std::vector<Number> NumberArray;
using Word = std::string;
using Value = unsigned long long;


/* Definitions */

struct Number
{
    unsigned long long value;
    std::string word;
};

void initData(NumberArray& data)
{
    char stream[STREAM_SIZE];
    std::ifstream dataFile;
    dataFile.open(DATAFILE);
    while(dataFile.good())
    {
        dataFile.getline(stream, STREAM_SIZE, '\n');
        if(std::string(stream).empty())
            continue;
        data.emplace_back(extractData(std::string(stream)));
    }
    dataFile.close();
    numberData = &data;
}

Number extractData(std::string stream)
{
    Number result;
    std::stringstream ss(stream);
    while(ss.good())
    {
        std::string str;
        ss >> str;
        if (!convToVal(str, result.value))
            result.word = str;
    }
    return result;
}

bool convToVal(const Word str, Value& value)
{
    uint64_t temp = 0;
    for(char c : str)
    {
        if(c < '0' || c > '9')
        {
            return false;
        }
        else
        {
            temp *= 10;
            temp += c - '0';
        }
    }
    value = temp;
    return true;
}

void loadExtraData(std::string&& file, NumberArray& data = *numberData)
{
    if (data.size() == INIT_DATA_SIZE) // TODO: Poor safeguard(Should probably have a static variable to check)
    {
        char stream[STREAM_SIZE];
        std::ifstream extraData;
        extraData.open(file);
        while(extraData.good())
        {
            extraData.getline(stream, STREAM_SIZE, '\n');
            if(std::string(stream).empty() || stream[0] == '#')
                continue;
            data.emplace_back(extractData(std::string(stream)));
        }
        extraData.close();
    }
}

// Other useful functions

// Extract right most segment
unsigned short extractRMS(Value& value)
{
    unsigned short right = value % 1000;
    value /= 1000;
    return right;
}

// Divides the value into segments and returns it as a vector of values
std::vector<Value> segment(Value value)
{
    std::vector<Value> result;
    while(value > 0)
    {
        result.emplace_back(0);
        result.back() += extractRMS(value);
    }
    return result;
}

Word genWord(Value value, NumberArray data = *numberData)
{
    if(value == 0)
    {
        return "zero";
    }
    // If the number is greater than or equal to 1000 it has segments so it should be segmented
    if(value >= 1000)
    {
        std::vector<Value> segments = segment(value);
        Word words = "";
        for(int i = segments.size() - 1; i >= 0; i--)
        {
            // Recursively concatonate each segment
            words += genWord(segments[i]) + (i == 0 ? "" : " " + data[data.size() - i].word + " ");
        }
        return words;
    }
    // When the smallest segment is passed and can be identified immediately ie numbers between 0 and 90
    for(int i = 1; i < INIT_DATA_SIZE - 2; i++)
    {
        if(value == data[i].value)
            return data[i].word;
    }
    // Gets to this point if the number is not immediately identified
    if(value > 0)
    {
        // Getting the hundred value and storing it in temp
        short temp = value / 100;
        value %= 100;
        // If the temp holds a hundred value
        if(temp > 0)
        {
            // Returns the hundred value and concatonates the next value
            return genWord(temp) + " hundred " + (value > 0 ? genWord(value) : ""); // The ternary operation prevents zero from coming at the end of the word
        }
        else // If the value doesn't have a hundred value
        {
            // Gets the unit
            temp = value % 10;
            return genWord(value - temp) + (temp == 0 ? "" : " " + genWord(temp));
        }
    }
    else
    {
        return "";
    }
    // If all else fails returns Unknown
    return "Unknown";
}

Value genValue(Word word, NumberArray data = *numberData)
{
    std::stringstream words(word);
    std::vector<Value> values;
    values.emplace_back(0);
    while(words.good())
    {
        Word temp;
        words >> temp;
        for(int i = 0; i < INIT_DATA_SIZE - 2; i++)
        {
            if(temp == data[i].word)
            {
                // result *= 10;
                values.back() += data[i].value;
                temp = "";
                break;
            }
        }
        if(temp == data[INIT_DATA_SIZE - 2].word)
        {
            values.back() *= 100;
        }
        for(int i = INIT_DATA_SIZE - 1; i < data.size(); i++)
        {
            if(temp.empty())
                break;
            if(temp == data[i].word)
            {
                values.back() *= data[i].value;
                values.emplace_back(0);
                break;
            }
        }
    }
    Value result = 0;
    for(Value v : values)
    {
        result += v;
    }
    return result;
}


/* Other */

#if defined(_GLIBCXX_IOSTREAM) || defined(_IOSTREAM_) // _GLIBCXX_IOSTREAM for MingW and _IOSTREAM_ for MSVC
// Printing the struct Number using the default basic_ostream
std::ostream& operator<<(std::ostream& out, Number number)
{
    out << number.value << " " << number.word;
    return out;
}
#endif

#endif // NUMBERS_UTIL_H