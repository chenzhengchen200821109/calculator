#if !defined _PARSER_H
#define _PARSER_H

#include "scanner.h"
#include "tree.h"
#include "Calculator.h"

enum Status
{
    stOk,
    stQuit,
    stError
};

class Parser
{
    public:
        Parser(Scanner& scanner, Calculator& calc);
        double Calculate();
        Status Parse();
    private:
        std::auto_ptr<Node> Expr();
        std::auto_ptr<Node> Term();
        std::auto_ptr<Node> Factor();
        Scanner& _scanner;
        std::auto_ptr<Node> _pTree;
        Status _status;
        Calculator& _calc;
};

#endif


