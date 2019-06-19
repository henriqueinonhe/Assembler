#include "code.h"
#include <stdexcept>

Code::Code()
{

}

vector<unsigned char> Code::dest(const string &mnemonic)
{
    if(mnemonic.empty())
    {
        return vector<unsigned char>({0, 0, 0});
    }
    else if(mnemonic == "M")
    {
        return vector<unsigned char>({0, 0, 1});
    }
    else if(mnemonic == "D")
    {
        return vector<unsigned char>({0, 1, 0});
    }
    else if(mnemonic == "MD")
    {
        return vector<unsigned char>({0, 1, 1});
    }
    else if(mnemonic == "A")
    {
        return vector< unsigned char>({1, 0, 0});
    }
    else if(mnemonic == "AM")
    {
        return vector<unsigned char>({1, 0, 1});
    }
    else if(mnemonic == "AD")
    {
        return vector<unsigned char>({1, 1, 0});
    }
    else if(mnemonic == "AMD")
    {
        return vector< unsigned char>({1, 1, 1});
    }
    else
    {
        throw invalid_argument("\"" + mnemonic + "\" is not a valid dest mnemonic!");
    }
}

vector<unsigned char> Code::comp(const string &mnemonic)
{
    if(mnemonic == "0")
    {
        return vector<unsigned char>({0, 1, 0, 1, 0, 1, 0});
    }
    else if(mnemonic == "1")
    {
        return vector<unsigned char>({0, 1, 1, 1, 1, 1, 1});
    }
    else if(mnemonic == "-1")
    {
        return vector<unsigned char>({0, 1, 1, 1, 0, 1, 0});
    }
    else if(mnemonic == "D")
    {
        return vector<unsigned char>({0, 0, 0, 1, 1, 0, 0});
    }
    else if(mnemonic == "A")
    {
        return vector<unsigned char>({0, 1, 1, 0, 0, 0, 0});
    }
    else if(mnemonic == "!D")
    {
        return vector<unsigned char>({0, 0, 0, 1, 1, 0, 1});
    }
    else if(mnemonic == "!A")
    {
        return vector<unsigned char>({0, 1, 1, 0, 0, 0, 1});
    }
    else if(mnemonic == "-D")
    {
        return vector<unsigned char>({0, 0, 0, 1, 1, 1, 1});
    }
    else if(mnemonic == "-A")
    {
        return vector<unsigned char>({0, 1, 1, 0, 0, 1, 1});
    }
    else if(mnemonic == "D+1")
    {
        return vector<unsigned char>({0, 0, 1, 1, 1, 1, 1});
    }
    else if(mnemonic == "A+1")
    {
        return vector<unsigned char>({0, 1, 1, 0, 1, 1, 1});
    }
    else if(mnemonic == "D-1")
    {
        return vector<unsigned char>({0, 0, 0, 1, 1, 1, 0});
    }
    else if(mnemonic == "A-1")
    {
        return vector<unsigned char>({0, 1, 1, 0, 0, 1, 0});
    }
    else if(mnemonic == "D+A")
    {
        return vector<unsigned char>({0, 0, 0, 0, 0, 1, 0});
    }
    else if(mnemonic == "D-A")
    {
        return vector<unsigned char>({0, 0, 1, 0, 0, 1, 1});
    }
    else if(mnemonic == "A-D")
    {
        return vector<unsigned char>({0, 0, 0, 0, 1, 1, 1});
    }
    else if(mnemonic == "D&A")
    {
        return vector<unsigned char>({0, 0, 0, 0, 0, 0, 0});
    }
    else if(mnemonic == "D|A")
    {
        return vector<unsigned char>({0, 0, 1, 0, 1, 0, 1});
    }
    else if(mnemonic == "M")
    {
        return vector<unsigned char>({1, 1, 1, 0, 0, 0, 0});
    }
    else if(mnemonic == "!M")
    {
        return vector<unsigned char>({1, 1, 1, 0, 0, 0, 1});
    }
    else if(mnemonic == "-M")
    {
        return vector<unsigned char>({1, 1, 1, 0, 0, 1, 1});
    }
    else if(mnemonic == "M+1")
    {
        return vector<unsigned char>({1, 1, 1, 0, 1, 1, 1});
    }
    else if(mnemonic == "M-1")
    {
        return vector<unsigned char>({1, 1, 1, 0, 0, 1, 0});
    }
    else if(mnemonic == "D+M")
    {
        return vector<unsigned char>({1, 0, 0, 0, 0, 1, 0});
    }
    else if(mnemonic == "D-M")
    {
        return vector<unsigned char>({1, 0, 1, 0, 0, 1, 1});
    }
    else if(mnemonic == "M-D")
    {
        return vector<unsigned char>({1, 0, 0, 0, 1, 1, 1});
    }
    else if(mnemonic == "D&M")
    {
        return vector<unsigned char>({1, 0, 0, 0, 0, 0, 0});
    }
    else if(mnemonic == "D|M")
    {
        return vector<unsigned char>({1, 0, 1, 0, 1, 0, 1});
    }
    else
    {
        throw invalid_argument("\"" + mnemonic + "\" is not a valid comp mnemonic!");
    }
}

vector<unsigned char> Code::jump(const string &mnemonic)
{
    if(mnemonic.empty())
    {
        return vector<unsigned char>({0, 0, 0});
    }
    else if(mnemonic == "JGT")
    {
        return vector<unsigned char>({0, 0, 1});
    }
    else if(mnemonic == "JEQ")
    {
        return vector<unsigned char>({0, 1, 0});
    }
    else if(mnemonic == "JGE")
    {
        return vector<unsigned char>({0, 1, 1});
    }
    else if(mnemonic == "JLT")
    {
        return vector<unsigned char>({1, 0, 0});
    }
    else if(mnemonic == "JNE")
    {
        return vector<unsigned char>({1, 0, 1});
    }
    else if(mnemonic == "JLE")
    {
        return vector<unsigned char>({1, 1, 0});
    }
    else if(mnemonic == "JMP")
    {
        return vector<unsigned char>({1, 1, 1});
    }
    else
    {
        throw invalid_argument("\"" + mnemonic + "\" is not a valid jump mnemonic!");
    }

}
