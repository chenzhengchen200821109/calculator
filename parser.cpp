#include "parser.h"
#include <iostream>

Parser::Parser(Scanner& scanner, Calculator& calc) : _scanner(scanner), _calc(calc), _status(stOk)
{
    //std::cout << "Parser created\n";
}

double Parser::Calculate()
{
    assert(_status == stOk);
    assert(_pTree.get() != 0);
    return _pTree->Calc();
}

//Parser::~Parser()
//{
//    delete _pTree;
//}

Status Parser::Parse()
{
    _pTree = Expr();
    // seems to never get here
    if (!_scanner.IsDone()) {
        _status = stError;
    }
    return _status;
}

//Node* Parser::Expr()
std::unique_ptr<Node> Parser::Expr()
{
    //Node* pNode = Term();
    std::unique_ptr<Node> pNode = Term();
    if (pNode.get() == 0)
        return pNode;

    EToken token = _scanner.Token();
    // Expr := Term {('+' | '-')Term}
    if (token == tPlus || token == tMinus) {
        //MultiNode* pMultiNode = new SumNode(pNode);
        std::unique_ptr<MultiNode> pMultiNode(new SumNode(std::move(pNode)));
        do {
            _scanner.Accept();
            //Node* pRight = Term();
            std::unique_ptr<Node> pRight = Term();
            if (pRight.get() == 0)
                return pNode;
            pMultiNode->AddChild(std::move(pRight), (token == tPlus));
            token = _scanner.Token();
        } while (token == tPlus || token == tMinus);
        pNode = std::move(pMultiNode);
    } else if (token == tAssign) {
        _scanner.Accept();
        // Expr := Term = Expr
        std::unique_ptr<Node> pRight = Expr();
        if (pNode->IsLvalue()) {
            pNode = std::unique_ptr<Node>(new AssignNode(std::move(pNode), std::move(pRight)));
        } else {
            _status = stError;
            //delete pNode;
            pNode = Expr();
        }
    }
    return pNode;
}

std::unique_ptr<Node> Parser::Term()
{
    std::unique_ptr<Node> pNode = Factor();
    EToken token = _scanner.Token();
    if (token == tMult || token == tDivide) {
        // Term := Factor {('*' | '/')Factor}
        std::unique_ptr<MultiNode> pMultiNode(new ProductNode(std::move(pNode)));
        do {
            _scanner.Accept();
            std::unique_ptr<Node> pRight = Term();
            pMultiNode->AddChild(std::move(pRight), (token == tMult));
            token = _scanner.Token();
        } while (token == tMult || token == tDivide);
        pNode = std::move(pMultiNode);
    }  
    return pNode;
}

std::unique_ptr<Node> Parser::Factor()
{
    std::unique_ptr<Node> pNode;
    EToken token = _scanner.Token();

    if (token == tLParen) { // "("
        _scanner.Accept();
        pNode = Expr();
        if (_scanner.Token() != tRParen)
            _status = stError;
        else
            _scanner.Accept();
    } else if (token == tNumber) { // "898"
        pNode = std::unique_ptr<Node>((new NumNode(_scanner.Number())));
        _scanner.Accept();
    } else if (token == tIdent) { // "xy"
        std::string strSymbol = _scanner.GetSymbolName();
        std::cout << "symbol = " << strSymbol << std::endl;
        size_t id = _calc.FindSymbol(strSymbol);
        _scanner.Accept();
        // built-in functions
        if (_scanner.Token() == tLParen) {
            _scanner.Accept();
            pNode = Expr();
            if (_scanner.Token() == tRParen)
                _scanner.Accept();
            else
                _status = stError;
            if (id != SymbolTable::idNotFound && _calc.IsFunction(id)) {
                pNode = std::unique_ptr<Node>(new FunNode(_calc.GetFun(id), std::move(pNode)));
            } else {
                std::cout << "Unknow function " << strSymbol << std::endl;
            }
        } else {
            std::cout << "id = " << id << std::endl;
            if (id == SymbolTable::idNotFound) {
                id = _calc.AddSymbol(strSymbol);
            }
            assert(id != SymbolTable::idNotFound);
            pNode = std::unique_ptr<Node>(new VarNode(id, _calc.GetStore()));
            //_scanner.Accept();
        }
    } else if (token == tMinus) {
        _scanner.Accept();
        pNode = std::unique_ptr<Node>(Factor());
    }
    else {
        _scanner.Accept();
        _status = stError;
        //pNode = 0;
    }
    return pNode;
}

