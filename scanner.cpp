#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "scanner.h"

// We get first token from Scanner constructor
Scanner::Scanner(std::string& str) : _str(str), _index(0)
{
    Accept();
    _isEmpty = (Token() == tEnd);
}

void Scanner::Accept()
{
    // we come to the end of expression, no need to continue
    if (_index == _str.size()) {
        _token = tEnd;
        return;
    }
    ReadChar(); // skip blank spaces and get current character
    switch(_ch)
    {
        case '+':
            _token = tPlus;
            ++_index;
            break;
        case '-':
            _token = tMinus;
            ++_index;
            break;
        case '*':
            _token = tMult;
            ++_index;
            break;
        case '/':
            _token = tDivide;
            ++_index;
            break;
        case '(':
            _token = tLParen;
            ++_index;
            break;
        case ')':
            _token = tRParen;
            ++_index;
            break;
        case '=':
            _token = tAssign;
            ++_index;
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.': 
        {
            _token = tNumber;
            _symbol.erase();
            do {
                _symbol += _ch;
                ++_index;
                _ch = _str[_index];
            } while (std::isdigit(_ch) || _ch == '.');
            _number = std::stod(_symbol);
            break;
        }
        case '!':
            _token = tCommand;
            ++_index;
            break;
        default:
            if (std::isalpha(_ch) || _ch == '_')
            {
                _token = tIdent;
                _symbol.erase();
                do {
                    _symbol += _ch;
                    _index++;
                    _ch = _str[_index];
                } while (std::isalnum(_ch));
            } else
                _token = tError; // invalid identification
            break;
    }
}

void Scanner::ReadChar()
{
    for ( ; _index < _str.size(); ++_index) {
        _ch = _str[_index]; // we get current character here
        if (_ch == ' ' || _ch == '\t')
            continue;
        else
            break;
    }
}
