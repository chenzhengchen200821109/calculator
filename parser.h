#if !defined _PARSER_H
#define _PARSER_H

#include "scanner.h"
#include "tree.h"
#include "Calculator.h"
#include "functionTable.h"

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
        std::unique_ptr<Node> Expr();
        std::unique_ptr<Node> Term();
        std::unique_ptr<Node> Factor();
        std::unique_ptr<Node> _pTree;
        Scanner& _scanner;
        Calculator& _calc;
        Status _status;
};

#endif


