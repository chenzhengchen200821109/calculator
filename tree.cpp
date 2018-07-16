#include <iostream>
#include <cmath>
#include "tree.h"

//BinNode::~BinNode()
//{
//    delete _pLeft;
//    delete _pRight;
//}

double NumNode::Calc() const
{
    std::cout << "Number node " << _num << std::endl;
    return _num;
}

bool VarNode::IsLvalue() const
{
    return true;
}

void VarNode::Assign(double val)
{
    _store.SetValue(_id, val);    
}

double VarNode::Calc() const
{
    std::cout << "Variable node " << std::endl;
    double x = 0.0;
    if (_store.IsInit(_id))
        x = _store.Value(_id);
    else
        std::cout << "Use of uninitialized variable\n";
    return x;
}

double AddNode::Calc() const
{
    std::cout << "Adding\n";
    return _pLeft->Calc() + _pRight->Calc();
}

double MultNode::Calc() const
{
    std::cout << "Multiplying\n";
    return (_pLeft->Calc()) * (_pRight->Calc());
}

double SubNode::Calc() const
{
    std::cout << "Substracting\n";
    return _pLeft->Calc() - _pRight->Calc();
}

double DivideNode::Calc() const
{
    std::cout << "Dividing\n";
    return _pLeft->Calc() / _pRight->Calc();
}

double AssignNode::Calc() const
{
    double x = _pRight->Calc();
    _pLeft->Assign(x);
    return x;
}

MultiNode::~MultiNode()
{
    typedef std::vector<Node *>::iterator NodeIter;
    for (NodeIter it = _aChild.begin(); it != _aChild.end(); ++it)
        delete *it;
}

double SumNode::Calc() const
{
    double sum = 0.0;
    for (std::size_t i = 0; i < _aChild.size(); ++i) {
        double val = _aChild[i]->Calc();
        if (_aIsPositive[i])
            sum += val;
        else
            sum -= val;
    }
    return sum;
}

double ProductNode::Calc() const
{
    double prod = 1.0;
    for (std::size_t i = 0; i < _aChild.size(); ++i) {
        double val = _aChild[i]->Calc();
        if (_aIsPositive[i])
            prod *= val;
        else if (val != 0.0)
            prod /= val;
        else {
            std::cerr << "Error: division by zero\n";
            return HUGE_VAL;
        }
    }
    return prod;
}




