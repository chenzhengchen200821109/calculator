#ifndef _COMMANDPARSER_H
#define _COMMANDPARSER_H

#include "calculator.h"
#include "scanner.h"
#include "parser.h"

class CommandParser
{
    enum ECommand
    {
        comSave,
        comLoad,
        comQuit,
        comError
    };
    public:
        CommandParser(Scanner& scanner, Calculator& calc);
        Status Execute();
    private:
        Status Load(std::string const& fileName);
        Status Save(std::string const& fileName);
        Scanner& _scanner;
        Calculator& _calc;
        ECommand _command;
};

#endif
