#include "command.h"

#include <stdexcept>

const basic_regex<char> Command::symbolRegex("([A-z]|:|_|\\.|\\$)+([A-z]|[0-9]|:|_|\\.|\\$)*");
const basic_regex<char> Command::valueRegex("[0-9]+");

Command::Command()
{

}

Command::Command(const string &command)
{
    string formattedString = removeWhitespaceAndComment(command);
    if(formattedString.empty())
    {
        return;
    }

    const char firstCharacter = formattedString.front();
    if(isACommandSuitableFirstChar(firstCharacter))
    {
        parseACommand(formattedString);
    }
    else if(isCCommandSuitableFirstChar(firstCharacter))
    {
        parseCCommand(formattedString);
    }
    else if(isLCommandSuitableFirstChar(firstCharacter))
    {
        parseLCommand(formattedString);
    }
    else
    {
        throw invalid_argument("\"" + command + "\" is not a valid command!");
    }
}

Command::CommandType Command::getCommandType() const
{
    return commandType;
}

string Command::getCommand() const
{
    return command;
}

string Command::removeWhitespaceAndComment(const string &command) const
{
    string formattedString;
    for(auto character = command.begin(); character != command.end(); character++)
    {
        if(*character == ' ') //Ignores whitespace
        {
            continue;
        }
        else
        {
            if(*character == '/') //One '/' triggers the comment check
            {
                character++;
                if(character != command.end() && *character == '/') //Two '/' in a row means it is a comment and it should ignore the rest of the sentence
                {
                    return formattedString;
                }
                else
                {
                    character--;
                }
            }
            else
            {
                formattedString.push_back(*character);
            }
        }
    }

    return formattedString;
}

string Command::symbol() const
{
    if(commandType == Command::CommandType::A_COMMAND)
    {
        return command.substr(1);
    }
    else if(commandType == Command::CommandType::L_COMMAND)
    {
        return command.substr(1, command.size() - 2);
    }
    else
    {
        throw invalid_argument("\"symbol\" method may only be called when the current command is an A-Command or an L-Command)");
    }
}

string Command::dest() const
{
    if(commandType == Command::CommandType::C_COMMAND)
    {
        if(cCommandHasAssignment(command))
        {
            return isolateCCommandLhs(command);
        }
        else
        {
            return "";
        }
    }
    else
    {
        throw invalid_argument("\"dest\" method may only be called when the current command is a C-Command and it has an assignment operator!");
    }
}

string Command::comp() const
{
    if(commandType == Command::CommandType::C_COMMAND)
    {
        if(cCommandHasAssignment(command))
        {
            return isolateCCommandRhs(command);
        }
        else //if(cCommandHasJump(command) && !cCommandHasAssignment(command))
        {
            return command.substr(0, 1);
        }
    }
    else
    {
        throw invalid_argument("\"comp\" method may only be called when the current command is a C-Command!");
    }
}

string Command::jump() const
{
    if(commandType == Command::CommandType::C_COMMAND)
    {
        if(cCommandHasJump(command))
        {
            return isolateJumpStatement(command);
        }
        else
        {
            return "";
        }
    }
    else
    {
        throw invalid_argument("\"jump\" method may only be called when the current command is a C-Command and it has a jump statement!");
    }
}

bool Command::isEmpty() const
{
    return command.empty();
}

bool Command::isCCommandSuitableFirstChar(const char character) const
{
    return character == 'A' ||
           character == 'D' ||
           character == 'M' ||
           character == '0' ||
           character == '1' ||
           character == '!' ||
           character == '-';
}

bool Command::isLCommandSuitableFirstChar(const char character) const
{
    return character == '(';
}

bool Command::isACommandValue(const string &string) const
{
    const unsigned int atCharacterIndexCompensation = 1;
    return regex_match(string.begin() + atCharacterIndexCompensation, string.end(), valueRegex);
}

bool Command::isACommandSymbol(const string &string) const
{
    const unsigned int atCharacterIndexCompensation = 1;
    return regex_match(string.begin() + atCharacterIndexCompensation, string.end(), symbolRegex);
}

void Command::parseACommand(const string &command)
{
    if(!isACommandValue(command) && !isACommandSymbol(command))
    {
        throw invalid_argument("\"" + command + "\" is not a valid A-Command!");
    }
    commandType = Command::CommandType::A_COMMAND;
    this->command = command;
}

void Command::parseLCommand(const string &command)
{
    checkLCommandParenthesisConformance(command);
    commandType = Command::CommandType::L_COMMAND;
    this->command = command;
}

void Command::parseCCommand(const string &command)
{
    //Validation
    if(command.size() < 2)
    {
        throw invalid_argument("\"" + command + "\" should have at least size 2!");
    }

    if(cCommandHasAssignment(command))
    {
        string lhs = isolateCCommandLhs(command);
        if(!isSuitableCCommandLhs(lhs))
        {
            throw invalid_argument("\"" + lhs + "\" is not a suitable lhs for assignment operator!");
        }

        string rhs = isolateCCommandRhs(command);
        if(!isSuitableCCommandRhs(rhs))
        {
            throw invalid_argument("\"" + rhs + "\" is not a suitable rhs for assignment operator!");
        }

        validateCCommandJumpStatement(command);
    }
    else
    {
        validateCCommandJumpStatement(command);
    }

    commandType = Command::CommandType::C_COMMAND;
    this->command = command;
}

bool Command::isACommandSuitableFirstChar(const char character) const
{
    return character == '@';
}

void Command::checkLCommandParenthesisConformance(const string &command) const
{
    if(command.back() != ')')
    {
        throw invalid_argument("First and last characters of an L-Command must be a left and right parenthesis respectively!");
    }

    if(!regex_match(command.begin() + 1, command.end() - 1, symbolRegex))
    {
        throw invalid_argument("\"" + command + "\" is not a valid L-Command!");
    }
}

bool Command::cCommandHasAssignment(const string &command) const
{
    return any_of(command.begin(), command.end(), [](const char &c)
    {
        return c == '=';
    });
}

bool Command::cCommandHasJump(const string &command) const
{
    return any_of(command.begin(), command.end(), [](const char character)
    {
        return character == ';';
    });
}

bool Command::isSuitableCCommandLhs(const string &lhs) const
{
    return lhs == "M" ||
           lhs == "D" ||
           lhs == "MD" ||
           lhs == "A" ||
           lhs == "A" ||
           lhs == "AM" ||
           lhs == "AD" ||
           lhs == "AMD";
}

bool Command::isSuitableCCommandRhs(const string &rhs) const
{
    return rhs == "0" ||
           rhs == "1" ||
           rhs == "-1" ||
           rhs == "D" ||
           rhs == "A" ||
           rhs == "!D" ||
           rhs == "!A" ||
           rhs == "-D" ||
           rhs == "-A" ||
           rhs == "D+1" ||
           rhs == "A+1" ||
           rhs == "A-1" ||
           rhs == "D-1" ||
           rhs == "A-1" ||
           rhs == "D+A" ||
           rhs == "D-A" ||
           rhs == "A-D" ||
           rhs == "D&A" ||
           rhs == "D|A" ||
           rhs == "M" ||
           rhs == "!M" ||
           rhs == "-M" ||
           rhs == "M+1" ||
           rhs == "M-1" ||
           rhs == "D+M" ||
           rhs == "D-M" ||
           rhs == "M-D" ||
           rhs == "D&M" ||
           rhs == "D|M";
}

bool Command::isSuitableJumpStatement(const string &jumpStatement) const
{
    return jumpStatement == "JGT" ||
           jumpStatement == "JEQ" ||
           jumpStatement == "JGE" ||
           jumpStatement == "JLT" ||
           jumpStatement == "JNE" ||
           jumpStatement == "JLE" ||
           jumpStatement == "JMP";
}

string Command::isolateCCommandLhs(const string &command) const
{
    string lhs;
    auto iter = command.begin();
    while(iter != command.end() && *iter != '=')
    {
        lhs += *iter;
        iter++;
    }
    return lhs;
}

string Command::isolateCCommandRhs(const string &command) const
{
    string rhs;
    string::const_iterator iter = command.begin();
    if(cCommandHasAssignment(command))
    {
        while(*iter != '=')
        {
            iter++;
        }
        iter++;
    }

    while(iter != command.end() && *iter != ';')
    {
        rhs += *iter;
        iter++;
    }
    return rhs;
}

string Command::isolateJumpStatement(const string &command) const
{
    string jumpStatement;
    auto iter = command.begin();
    //Find jump statement begin
    while(iter != command.end() && *iter != ';')
    {
        iter++;
    }
    iter++;
    //Isolate jump statement
    while(iter != command.end())
    {
        jumpStatement += *iter;
        iter++;
    }

    return jumpStatement;
}

void Command::validateCCommandJumpStatement(const string &command) const
{
    if(cCommandHasJump(command))
    {
        string jumpStatement = isolateJumpStatement(command);
        if(!isSuitableJumpStatement(jumpStatement))
        {
            throw invalid_argument("\"" + jumpStatement + "\" is not a suitable jump statement!");
        }
    }
}
