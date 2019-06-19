#ifndef CODE_H
#define CODE_H

#include <string>
#include <vector>

using namespace std;

class Code
{
public:
    Code();
    static vector<unsigned char> dest(const string &mnemonic);
    static vector<unsigned char> comp(const string &mnemonic);
    static vector<unsigned char> jump(const string &mnemonic);
};

#endif // CODE_H
