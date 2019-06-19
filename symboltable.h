#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>

using namespace std;

class SymbolTable
{
public:
    SymbolTable();
    void addEntry(const string &symbol, const unsigned int address);
    bool contains(const string &symbol) const;
    unsigned int getAddress(const string &symbol) const;

private:
    unordered_map<string, unsigned int> table;
};

#endif // SYMBOLTABLE_H
