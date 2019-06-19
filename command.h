#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <regex>

using namespace std;

class Command
{
public:
    static const basic_regex<char> symbolRegex;
    static const basic_regex<char> valueRegex;

    Command();
    Command(const string &command);

    enum class CommandType
    {
        A_COMMAND,
        C_COMMAND,
        L_COMMAND
    };

    CommandType getCommandType() const;
    string getCommand() const;

    string symbol() const;
    string dest() const;
    string comp() const;
    string jump() const;

    bool isEmpty() const;

private:
    string removeWhitespaceAndComment(const string &string) const;
    void parseACommand(const string &command);
    void parseLCommand(const string &command);
    void parseCCommand(const string &command);

    bool isACommandSuitableFirstChar(const char character) const;
    bool isCCommandSuitableFirstChar(const char character) const;
    bool isLCommandSuitableFirstChar(const char character) const;
    bool isACommandValue(const string &string) const;
    bool isACommandSymbol(const string &string) const;
    void checkLCommandParenthesisConformance(const string &command) const;
    bool cCommandHasAssignment(const string &command) const;
    bool cCommandHasJump(const string &command) const;
    bool isSuitableCCommandLhs(const string &lhs) const;
    bool isSuitableCCommandRhs(const string &rhs) const;
    bool isSuitableJumpStatement(const string &jumpStatement) const;
    string isolateCCommandLhs(const string &command) const;
    string isolateCCommandRhs(const string &command) const; //FIXME!
    string isolateJumpStatement(const string &command) const;
    void validateCCommandJumpStatement(const string &command) const;

    string command;
    CommandType commandType;
};

#endif // COMMAND_H
