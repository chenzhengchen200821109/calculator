#include "parser.h"
#include <iostream>

Parser::Parser(Scanner& scanner, Calculator& calc) : _scanner(scanner), _calc(calc), _status(stOk)
{
    std::cout << "Parser created\n";
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
std::auto_ptr<Node> Parser::Expr()
{
    //Node* pNode = Term();
    std::auto_ptr<Node> pNode = Term();
    if (pNode.get() == 0)
        return pNode;

    EToken token = _scanner.Token();
    // Expr := Term {('+' | '-')Term}
    if (token == tPlus || token == tMinus) {
        //MultiNode* pMultiNode = new SumNode(pNode);
        std::auto_ptr<MultiNode> pMultiNode(new SumNode(pNode));
        do {
            _scanner.Accept();
            //Node* pRight = Term();
            std::auto_ptr<Node> pRight = Term();
            if (pRight.get() == 0)
                return pNode;
            pMultiNode->AddChild(pRight, (token == tPlus));
            token = _scanner.Token();
        } while (token == tPlus || token == tMinus);
        pNode = pMultiNode;
    } else if (token == tAssign) {
        _scanner.Accept();
        // Expr := Term = Expr
        std::auto_ptr<Node> pRight = Expr();
        if (pNode->IsLvalue()) {
            pNode = std::auto_ptr<Node>(new AssignNode(pNode, pRight));
        } else {
            _status = stError;
            //delete pNode;
            pNode = Expr();
        }
    }
    return pNode;
}

std::auto_ptr<Node> Parser::Term()
{
    std::auto_ptr<Node> pNode = Factor();
    EToken token = _scanner.Token();
    if (token == tMult || token == tDivide) {
        // Term := Factor {('*' | '/')Factor}
        std::auto_ptr<MultiNode> pMultiNode(new ProductNode(pNode));
        do {
            _scanner.Accept();
            std::auto_ptr<Node> pRight = Term();
            pMultiNode->AddChild(pRight, (token == tMult));
            token = _scanner.Token();
        } while (token == tMult || token == tDivide);
        pNode = pMultiNode;
    }  
    return pNode;
}

std::auto_ptr<Node> Parser::Factor()
{
    std::auto_ptr<Node> pNode;
    EToken token = _scanner.Token();

    if (token == tLParen) {
        _scanner.Accept();
        pNode = Expr();
        if (_scanner.Token() != tRParen)
            _status = stError;
        else
            _scanner.Accept();
    } else if (token == tNumber) {
        pNode = std::auto_ptr<Node>((new NumNode(_scanner.Number())));
        _scanner.Accept();
    } else if (token == tIdent) {
        std::string strSymbol = _scanner.GetSymbolName();
        std::cout << "symbol = " << strSymbol << std::endl;
        int id = _calc.FindSymbol(strSymbol);
        std::cout << "id = " << id << std::endl;
        if (id == SymbolTable::idNotFound) {
            id = _calc.AddSymbol(strSymbol);
        }
        assert(id != SymbolTable::idNotFound);
        pNode = std::auto_ptr<Node>(new VarNode(id, _calc.GetStore()));
        _scanner.Accept();
    } else {
        _scanner.Accept();
        _status = stError;
        //pNode = 0;
    }
    return pNode;
}

