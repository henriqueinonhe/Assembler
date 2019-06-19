#include "parser.h"

Parser::Parser(const string &filePath) :
    stream(filePath)
{
    if(!stream.is_open())
    {
        throw invalid_argument("File \"" + filePath + "\" couldn't be opened!");
    }
}

bool Parser::hasMoreCommands() const
{
    return !stream.eof();
}

void Parser::advance()
{
    if(!hasMoreCommands())
    {
        //Maybe add exception here!
        return;
    }


    string command;
    getline(stream, command);
    currentCommand = Command(command);
}

Command::CommandType Parser::commandType() const
{
    return currentCommand.getCommandType();
}

string Parser::symbol() const
{
    return currentCommand.symbol();
}

string Parser::dest() const
{
    return currentCommand.dest();
}

string Parser::comp() const
{
    return currentCommand.comp();
}

string Parser::jump() const
{
    return currentCommand.jump();
}

bool Parser::isEmpty() const
{
    return currentCommand.isEmpty();
}

void Parser::reset()
{
    stream.seekg(0);
}

