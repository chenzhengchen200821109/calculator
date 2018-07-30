#if !defined _TREE_H
#define _TREE_H

#include "functionTable.h"
#include "store.h"
#include <vector>
#include <memory>
#include <iterator>

// abstract class
class Node 
{
    public:
        virtual ~Node() {}
        virtual double Calc() const = 0; // pure virtual function
        virtual bool IsLvalue() const
        {
            return false;
        }
        virtual void Assign(double) {}
};

class MultiNode : public Node
{
    public:
        MultiNode(std::unique_ptr<Node> pNode)
        {
            AddChild(std::move(pNode), true);
        }
        ~MultiNode();
        void AddChild(std::unique_ptr<Node> pNode, bool isPositive)
        {
            _aChild.push_back(std::move(pNode));
            _aIsPositive.push_back(isPositive);
        }
    protected:
        std::vector<std::unique_ptr<Node>> _aChild;
        std::vector<bool> _aIsPositive;
};

class SumNode : public MultiNode
{
    public:
        SumNode(std::unique_ptr<Node> pNode) : MultiNode(std::move(pNode)) {};
        double Calc() const;
};

class ProductNode : public MultiNode
{
    public:
        ProductNode(std::unique_ptr<Node> pNode) : MultiNode(std::move(pNode)) {};
        double Calc() const;
};

class BinNode : public Node
{
    public:
        BinNode(std::unique_ptr<Node> pLeft, std::unique_ptr<Node> pRight) : _pLeft(std::move(pLeft)), _pRight(std::move(pRight)) {}
    protected:
        std::unique_ptr<Node> _pLeft;
        std::unique_ptr<Node> _pRight;
};

class UniNode : public Node
{
    public:
        UniNode(std::unique_ptr<Node> pNode) : _pNode(std::move(pNode)) {}
    protected:
        std::unique_ptr<Node> _pNode;
};

class FunNode : public UniNode
{
    public:
        FunNode(PtrFun pFun, std::unique_ptr<Node> pNode) : UniNode(std::move(pNode)), _pFun(pFun) {};
        double Calc() const
        {
            assert(_pFun != 0);
            return (*_pFun)(_pNode->Calc());
        }
    private:
        PtrFun _pFun;
};

class UMinusNode : public UniNode
{
    public:
        UMinusNode(std::unique_ptr<Node> pNode) : UniNode(std::move(pNode)) {}
        double Calc() const
        {
            return (-1.0) * (_pNode->Calc());
        }
};

class NumNode: public Node
{
    public:
        NumNode(double num): _num(num) {}
        double Calc() const;
    private:
        const double _num;
};

// variables and functions
class VarNode : public Node
{
    public:
        VarNode(int id, Store& store) : _id(id), _store(store) {}
        double Calc() const;
        bool IsLvalue() const;
        void Assign(double val); 
    private:
        const int _id;
        Store& _store;
};

class AddNode : public BinNode
{
    public:
        AddNode(std::unique_ptr<Node> pLeft, std::unique_ptr<Node> pRight) : BinNode(std::move(pLeft), std::move(pRight)) {}
        double Calc() const;
};

class MultNode : public BinNode
{
    public:
        MultNode(std::unique_ptr<Node> pLeft, std::unique_ptr<Node> pRight) : BinNode(std::move(pLeft), std::move(pRight)) {}
        double Calc() const;
};

class SubNode : public BinNode
{
    public:
        SubNode(std::unique_ptr<Node> pLeft, std::unique_ptr<Node> pRight) : BinNode(std::move(pLeft), std::move(pRight)) {}
        double Calc() const;
};

class DivideNode : public BinNode
{
    public:
        DivideNode(std::unique_ptr<Node> pLeft, std::unique_ptr<Node> pRight) : BinNode(std::move(pLeft), std::move(pRight)) {}
        double Calc() const;
};

class AssignNode : public BinNode
{
    public:
        AssignNode(std::unique_ptr<Node> pLeft, std::unique_ptr<Node> pRight) : BinNode(std::move(pLeft), std::move(pRight))
        {
            assert(_pLeft->IsLvalue());
        }
        double Calc() const;
};


#endif
