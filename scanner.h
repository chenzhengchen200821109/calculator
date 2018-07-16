#if !defined scanner_h
#define scanner_h

#include <cassert>
#include <iostream>
#include <cstring>

enum EToken
{
    tCommand,
    tEnd,
    tError,
    tNumber,
    tPlus,
    tMult,
    tMinus,
    tDivide,
    tLParen,
    tRParen,
    tAssign,
    tIdent
};

class Scanner
{
    public:
        explicit Scanner(std::istream & in);
        EToken Token() const { return _token; }
        void Accept();
        double Number() const { return _number; }
        std::string GetSymbolName() const { return _symbol; };
        bool IsDone() const { return _token == tEnd; }
        bool IsEmpty() const { return _isEmpty; }
        void AcceptCommand()
        {
            ReadChar();
            _symbol.erase();
            while (!std::isspace(_look))
            {
                _symbol += _look;
                _look = _in.get();
            }
        }
        void ReadChar();
        bool IsCommand() { return _token == tCommand; }
    private:
        std::istream & _in;
        int _look;
        bool _isEmpty;
        EToken _token;
        double _number;
        std::string _symbol;
};

#endif
