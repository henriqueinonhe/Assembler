#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "command.h"

using namespace std;

class Parser
{
public:
    Parser(const string &filePath);

    bool hasMoreCommands() const;
    void advance();
    Command::CommandType commandType() const;
    string symbol() const;
    string dest() const;
    string comp() const;
    string jump() const;
    bool isEmpty() const;
    void reset();

private:
    fstream stream;
    Command currentCommand;
};

#endif // PARSER_H
