#include <iostream>

//#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "parser.h"
#include "code.h"
#include <regex>
#include <math.h>
#include "symboltable.h"

using namespace std;

#ifndef CATCH_CONFIG_MAIN

template <class T>
void vectorAppend(vector<T> &vec1, const vector<T> &vec2)
{
    for(const auto &elem : vec2)
    {
        vec1.push_back(elem);
    }
}

//Utils
ostream &operator <<(ostream &stream, const vector<unsigned char> &vec);
bool symbolIsValue(const string &symbol);
vector<unsigned char> valueTo15Bit(const unsigned int val);
vector<unsigned char> valueTo15Bit(const string &valueString);
string generateOutputFilePath(const string &inFilePath);

//Sub routines
bool validateFileInput(const string &filePath);
void firstPass(SymbolTable &symbolTable, const string &inFilePath);
void secondPass(SymbolTable &symbolTable, const string &inFilePath, ofstream &outputFile);

int main(int argc, const char *argv[])
{
    const string inFilePath = argv[1];
    if(!validateFileInput(inFilePath))
    {
        return 0;
    }

    try
    {
        ofstream outputFile(generateOutputFilePath(inFilePath));
        SymbolTable symbolTable;
        firstPass(symbolTable, inFilePath);
        secondPass(symbolTable, inFilePath, outputFile);
    }
    catch(const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
    cout << "File written successfully!" << endl;
}

//Definitions

ostream &operator <<(ostream &stream, const vector<unsigned char> &vec)
{
    for(const auto e : vec)
    {
        stream << static_cast<unsigned int>(e);
    }
    return stream;
}

bool symbolIsValue(const string &symbol)
{
    return regex_match(symbol.begin(), symbol.end(), Command::valueRegex);
}

vector<unsigned char> valueTo15Bit(const unsigned int val)
{
    unsigned int value = val;
    const unsigned int maxValue = 32767;
    if(value > maxValue)
    {
        throw invalid_argument("\"" + to_string(value) + "\" is greater than the max possible value (32767)!");
    }

    vector<unsigned char> vec;
    vec.resize(15);
    for(unsigned int index = 0; index < 15; index++)
    {
        const unsigned int exp = 14 - index;
        vec[index] = value / pow(2, exp);
        value = value % static_cast<unsigned int>(pow(2, exp)); //NOTE This may be unsafe
    }
    return vec;
}

vector<unsigned char> valueTo15Bit(const string &valueString)
{
    //Converts value to 15 bit vector
    unsigned int value = stoi(valueString);
    return valueTo15Bit(value);
}

string generateOutputFilePath(const string &inFilePath)
{
    return inFilePath.substr(0, inFilePath.size() - 3) + "hack";
}

bool validateFileInput(const string &filePath)
{
    basic_regex<char> asmRegex(".+\\.asm");
    if(!regex_match(filePath.begin(), filePath.end(), asmRegex))
    {
        cerr << "File must have \".asm\" format!" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

void firstPass(SymbolTable &symbolTable, const string &inFilePath)
{
    //Register L-Commands symbols in the symbol table
    unsigned int lineCounter = 0;
    Parser parser(inFilePath);

    while(parser.hasMoreCommands())
    {
        parser.advance();

        if(parser.isEmpty())
        {
            continue;
        }
        else if(parser.commandType() == Command::CommandType::L_COMMAND)
        {
            const string symbol = parser.symbol();
            symbolTable.addEntry(symbol, lineCounter);
        }
        else
        {
            lineCounter++; //Increments only when line does not consist of a comment alone or a L-Command
        }
    }
}

void secondPass(SymbolTable &symbolTable, const string &inFilePath, ofstream &outputFile)
{
    unsigned int addressCounter = 1024;
    Parser parser(inFilePath);
    while(parser.hasMoreCommands())
    {
        vector<unsigned char> binaryCode;
        parser.advance();

        if(parser.isEmpty())
        {
            continue;
        }

        if(parser.commandType() == Command::CommandType::A_COMMAND)
        {
            binaryCode.push_back(0);
            const string symbol = parser.symbol();
            if(symbolIsValue(symbol))
            {
                vectorAppend(binaryCode, valueTo15Bit(symbol));
            }
            else
            {
                if(!symbolTable.contains(symbol))
                {
                    symbolTable.addEntry(symbol, addressCounter);
                    addressCounter++;
                }
                vectorAppend(binaryCode, valueTo15Bit(symbolTable.getAddress(symbol)));
            }
        }
        else if(parser.commandType() == Command::CommandType::L_COMMAND)
        {
            continue; //Bypasses line output
        }
        else if(parser.commandType() == Command::CommandType::C_COMMAND)
        {
            binaryCode.push_back(1);
            binaryCode.push_back(1);
            binaryCode.push_back(1);
            vectorAppend(binaryCode, Code::comp(parser.comp()));
            vectorAppend(binaryCode, Code::dest(parser.dest()));
            vectorAppend(binaryCode, Code::jump(parser.jump()));
        }
        outputFile << binaryCode << endl;
    }
}

#endif
