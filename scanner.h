#if !defined scanner_h
#define scanner_h

#include <cassert>
#include <iostream>
#include <cstring>
#include <string>

enum EToken
{
    tCommand, // commands like !q
    tEnd,
    tError,
    tNumber, // literal number
    tPlus, // +
    tMult, // *
    tMinus, // -
    tDivide, // /
    tLParen, // (
    tRParen, // )
    tAssign, // = 
    tIdent   // identification
};

class Scanner
{
    public:
        explicit Scanner(std::string& str);
        EToken Token() const { return _token; }
        void Accept();
        double Number() const { return _number; }
        std::string GetSymbolName() const { return _symbol; }
        bool IsDone() const { return _token == tEnd; } // it comes to end
        bool IsEmpty() const { return _isEmpty; } // it is an empty line
        void AcceptCommand()
        {
            ReadChar();
            _symbol.erase();
            for ( ; _index < _str.size(); ++_index) {
                _ch = _str[_index];
                if (std::isspace(_ch))
                    break;
                else {
                    _symbol += _ch;
                }
            }
        }
        void ReadChar();
        bool IsCommand() { return _token == tCommand; }
    private:
        std::string& _str;
        char _ch;
        int _index;
        bool _isEmpty;
        EToken _token;
        double _number;
        std::string _symbol;
};

#endif
